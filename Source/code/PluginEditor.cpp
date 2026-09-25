#include "PluginProcessor.hpp"
#include "PluginEditor.hpp"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    
	float minWidth = 10.f;
	float maxWidth = 980.f;
	float minHeight = 120.f;
	float maxHeight = 570.f;
    this->cornerSizeEffectArea = 20.f;
    this->effectArea = {minWidth, minHeight, maxWidth, maxHeight};

    this->selectorInit();
    this->reverbInit();
    this->distortionInit();
    this->delayInit();
    this->chorusInit();
    this->eqInit();

    this->drawMoveChainObject = false;
    this->currentSelected = EffectIndex::ADD;

    setSize(1000, 800);
    resized();
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {
    for (auto& it : this->eqSliders)
        it.reset();
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll(juce::Colour::fromRGB(35, 35, 35));

    float startX = 200;
    g.setColour(juce::Colours::white);
    juce::Path seperatorChain;
    for (std::size_t i = 0; (i + 1) < this->activeChain.size(); i++) {
        seperatorChain.addRectangle(startX + (i * 200), 20, 5, 60);    
        g.fillPath(seperatorChain);
    }

    juce::Path seperatorChainSelector;
    seperatorChainSelector.addRectangle(0, 100, 1000, 10);
    g.setColour(juce::Colours::black);
	g.fillPath(seperatorChainSelector);

    juce::Path seperatorSelectorMain;
    seperatorSelectorMain.addRectangle(0, 700, 1000, 10);
	g.fillPath(seperatorSelectorMain);

    if (this->drawMoveChainObject) {
        g.setColour(juce::Colours::white);
        juce::Path path;
        path.addRectangle(this->moveRectangle.getBounds());
        juce::PathStrokeType pathStrokType(1.0);
        float dashedLengh[2];
        dashedLengh[0]=4;
        dashedLengh[1]=4;
        pathStrokType.createDashedStroke(path, path, dashedLengh, 2);
        g.strokePath(path, pathStrokType);
    }

    switch (this->currentSelected)
    {
    case EffectIndex::REVERB:
        this->reverbPaint(g);
        break ;
    case EffectIndex::DISTORTION:
        this->distortionPaint(g);
        break ;
    case EffectIndex::DELAY:
        this->delayPaint(g);
        break ;
    case EffectIndex::CHORUS:
        this->chorusPaint(g);
        break;
    case EffectIndex::EQ:
        this->eqPaint(g);
        break;
    case EffectIndex::ADD:
        this->selectorPaint(g);
        break;
    default:
        this->selectorPaint(g);
        break;
    }
}

void AudioPluginAudioProcessorEditor::resized() {
    int spacing = 200;
    int startX = 15;
    int chainBoxY = 10;
    int chainBoxWidth = 170;
    int chainBoxHeight = 80;

    for (std::size_t i = 0; i < this->activeChain.size(); i++) {
        this->activeChain[i]->setBounds(startX + (i * spacing), chainBoxY, chainBoxWidth, chainBoxHeight);
    }

    switch (this->currentSelected)
    {
    case EffectIndex::REVERB:
        this->reverbResized();
        break ;
    case EffectIndex::DISTORTION:
        this->distortionResized();
        break ;
    case EffectIndex::DELAY:
        this->delayResized();
        break ;
    case EffectIndex::CHORUS:
        this->chorusResized();
        break;
    case EffectIndex::EQ:
        this->eqResized();
        break;
    case EffectIndex::ADD:
        this->selectorResized();
        break;
    default:
        this->selectorResized();
        break;
    }

}

void AudioPluginAudioProcessorEditor::computeView(EffectIndex effect) {
    switch (this->currentSelected)
    {
    case EffectIndex::REVERB:
        this->reverbHide();
        break ;
    case EffectIndex::DISTORTION:
        this->distortionHide();
        break ;
    case EffectIndex::DELAY:
        this->delayHide();
        break ;
    case EffectIndex::CHORUS:
        this->chorusHide();
        break;
    case EffectIndex::EQ:
        this->eqHide();
        break;
    case EffectIndex::ADD:
        this->selectorHide();
        break;
    default:
        this->selectorHide();
        break;
    }

    this->currentSelected = effect;
    resized();
    repaint();
}


void AudioPluginAudioProcessorEditor::selectorClicked(EffectIndex effect) {
    auto target = &this->chainEffectBox[effect];

    if (std::find(this->activeChain.begin(), this->activeChain.end(), target) != this->activeChain.end())
        return;

    if (!this->activeChain.empty() && this->activeChain.back() == this->adder) {
        this->adder->setVisible(false);
        this->activeChain.pop_back();
    }

    this->selectEffectBox[effect].setActive(true);
    this->activeChain.push_back(target);
    target->setVisible(true);

    if (this->activeChain.size() < 5) {
        this->adder->setVisible(true);
        this->activeChain.push_back(this->adder);
    }

    this->computeView(effect);
}

void AudioPluginAudioProcessorEditor::removeFromChain(EffectIndex effect) {
    auto target = &this->chainEffectBox[effect];

    auto it = std::find(this->activeChain.begin(), this->activeChain.end(), target);
    if (it == this->activeChain.end())
        return;
    target->setVisible(false);
    this->selectEffectBox[effect].setActive(false);


    this->activeChain.erase(it);

    if (std::find(this->activeChain.begin(), this->activeChain.end(), this->adder) == this->activeChain.end()) {
        this->adder->setVisible(true);
        this->activeChain.push_back(this->adder);
    }

    if (this->currentSelected == effect || this->activeChain.size() == 1) {
        this->computeView(EffectIndex::ADD);
        return ;
    }
    this->computeView(this->currentSelected);
}

void AudioPluginAudioProcessorEditor::dragChainObject(EffectIndex effect, const juce::MouseEvent& event) {
    this->drawMoveChainObject = true;

    float rectangleY      = 5.f;
    float rectangleWidth  = 180.f;
    float rectangleHeight = 90.f;
    int   slotWidth       = 200;
    int   firstSlotX      = 10;

    int xPos = event.getEventRelativeTo(this).getPosition().x;

    int slot = (xPos - firstSlotX) / slotWidth;
    slot = juce::jlimit(0, (int)this->activeChain.size() - 1, slot);

    float rectangleX = (float)firstSlotX + slot * slotWidth;

    this->moveRectangle.clear();
    this->moveRectangle.addRectangle<float>({rectangleX, rectangleY, rectangleWidth, rectangleHeight});

    this->computeView(this->currentSelected);
}

void AudioPluginAudioProcessorEditor::swapChainObjects(EffectIndex effect, const juce::MouseEvent& event) {

    int xPos = event.getEventRelativeTo(this).getPosition().x;
    int slotWidth = 200;
    int firstSlotX = 10;
    int slot = (xPos - firstSlotX) / slotWidth;
    slot = juce::jlimit(0, (int)this->activeChain.size(), slot);

    int startSlot = event.getEventRelativeTo(this).getMouseDownPosition().getX() / slotWidth;
    startSlot = juce::jlimit(0, (int)this->activeChain.size() - 1, startSlot);

    auto it = this->activeChain.begin() + slot;
    if ((*it)->getEffectBoxType() == EffectBoxType::ADDER) {
        this->drawMoveChainObject = false;
        this->computeView(this->currentSelected);
        return ;
    }

    std::iter_swap(this->activeChain.begin() + startSlot, this->activeChain.begin() + slot);

    this->drawMoveChainObject = false;
    this->computeView(this->currentSelected);
}

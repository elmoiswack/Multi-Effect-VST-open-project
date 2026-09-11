#include "PluginProcessor.hpp"
#include "PluginEditor.hpp"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    this->selectEffectBox.reserve(5);
    this->chainEffectBox.reserve(6);
    this->activeChain.reserve(5);
    initEffectBoxes();
    auto& adderBox = this->chainEffectBox.emplace_back(
        "Adder",
        ColorsScheme::eqPrimary,
        EffectBoxType::ADDER,
        EffectIndex::ADD
    );

    adderBox.onLeftClickAdd = [this](EffectIndex effect) {
        // return to selector overview
    };

    addAndMakeVisible(adderBox);

    this->adder = &adderBox;
    this->activeChain.push_back(this->adder);

    setSize(1000, 800);
    resized();
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {

}

void AudioPluginAudioProcessorEditor::initEffectBoxes() {
    this->initEffectObject("Reverb", ColorsScheme::reverbPrimary, EffectIndex::REVERB);
    this->initEffectObject("Distortion", ColorsScheme::distortionPrimary, EffectIndex::DISTORTION);
    this->initEffectObject("Delay", ColorsScheme::delayPrimary, EffectIndex::DELAY);
    this->initEffectObject("Chorus", ColorsScheme::chorusPrimary, EffectIndex::CHORUS);
    this->initEffectObject("EQ", ColorsScheme::eqPrimary, EffectIndex::EQ);
}

void AudioPluginAudioProcessorEditor::initEffectObject(juce::String name, const juce::uint8* color, EffectIndex index) {
    auto& objectSelector = this->selectEffectBox.emplace_back(
        name,
        color,
        EffectBoxType::SELECTOR,
        index
    );
    objectSelector.onLeftClickAdd = [this](EffectIndex effect) {
        selectorClicked(effect);
    };
    addAndMakeVisible(objectSelector);
    
    auto& objectChain = this->chainEffectBox.emplace_back(
        name,
        color,
        EffectBoxType::CHAIN,
        index
    );
    objectChain.onLeftClickRemove = [this](EffectIndex effect) {
        removeFromChain(effect);
    };
    addAndMakeVisible(objectChain);
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
}

void AudioPluginAudioProcessorEditor::resized() {
    auto height = getHeight();
    auto width = getWidth();

    auto widthBox = 150;
    auto heigthBox = 125;

    this->selectEffectBox[EffectIndex::REVERB].setBounds(
        width / 4 - (width / 8), 
        height / 4,
        widthBox,
        heigthBox);

   this->selectEffectBox[EffectIndex::DISTORTION].setBounds(
        width / 4 * 3 - (width / 8), 
        height / 4, 
        widthBox, 
        heigthBox);

    this->selectEffectBox[EffectIndex::DELAY].setBounds(
        width / 4 - (width / 8), 
        height / 4 * 2, 
        widthBox, 
        heigthBox);

    this->selectEffectBox[EffectIndex::CHORUS].setBounds(
        width / 4 * 3 - (width / 8), 
        height / 4 * 2, 
        widthBox, 
        heigthBox);

    this->selectEffectBox[EffectIndex::EQ].setBounds(
        width / 2 - (width / 8), 
        height / 4 * 2, 
        widthBox,
        heigthBox);

    int spacing = 200;
    int startX = 15;
    int chainBoxY = 10;
    int chainBoxWidth = 170;
    int chainBoxHeight = 80;

    std::cout << "Size chain active: " << this->activeChain.size() << std::endl;
    for (std::size_t i = 0; i < this->activeChain.size(); i++) {
		if (i == 5)
			break ;
        this->activeChain[i]->setBounds(startX + (i * spacing), chainBoxY, chainBoxWidth, chainBoxHeight);
    }
}

void AudioPluginAudioProcessorEditor::selectorClicked(EffectIndex effect) {
    auto target = &this->chainEffectBox[effect];

    if (std::find(this->activeChain.begin(), this->activeChain.end(), target) != this->activeChain.end())
        return;

    std::cout << "SIZE ACTIVE: " << std::endl;
    std::cout << this->activeChain.size() << std::endl;

    if (!this->activeChain.empty() && this->activeChain.back() == this->adder) {
        std::cout << "POP" << std::endl;
        this->adder->setVisible(false);
        this->activeChain.pop_back();
    }

    std::cout << this->activeChain.size() << std::endl;


    this->activeChain.push_back(target);

    std::cout << this->activeChain.size() << std::endl;

    target->setVisible(true);
    if (this->activeChain.size() < 5) {
        std::cout << "PUSH" << std::endl;
        this->adder->setVisible(true);
        this->activeChain.push_back(this->adder);
    }
    std::cout << this->activeChain.size() << std::endl;

    resized();
    repaint();
}

void AudioPluginAudioProcessorEditor::removeFromChain(EffectIndex effect) {
    auto target = &this->chainEffectBox[effect];

    auto it = std::find(this->activeChain.begin(), this->activeChain.end(), target);
    if (it == this->activeChain.end())
        return;
    target->setVisible(false);

    this->activeChain.erase(it);

    if (std::find(this->activeChain.begin(), this->activeChain.end(), this->adder) == this->activeChain.end()) {
        this->adder->setVisible(true);
        this->activeChain.push_back(this->adder);
    }

    resized();
    repaint();
}


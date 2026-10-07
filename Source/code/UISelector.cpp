#include "PluginEditor.hpp"

void AudioPluginAudioProcessorEditor::selectorInit() {
    this->selectEffectBox.reserve(5);
    this->chainEffectBox.reserve(6);
    this->activeChain.reserve(5);
   
    this->initEffectObject("Reverb", ColorsScheme::reverbPrimary, EffectIndex::REVERB);
    this->initEffectObject("Distortion", ColorsScheme::distortionPrimary, EffectIndex::DISTORTION);
    this->initEffectObject("Delay", ColorsScheme::delayPrimary, EffectIndex::DELAY);
    this->initEffectObject("Chorus", ColorsScheme::chorusPrimary, EffectIndex::CHORUS);
    this->initEffectObject("EQ", ColorsScheme::eqPrimary, EffectIndex::EQ);

    auto& adderBox = this->chainEffectBox.emplace_back(
        "Adder",
        ColorsScheme::eqPrimary,
        EffectBoxType::ADDER,
        EffectIndex::ADD
    );

    adderBox.onLeftClickShowEffect = [this](EffectIndex effect) {
        this->computeView(EffectIndex::ADD);
    };

    addAndMakeVisible(adderBox);

    this->adder = &adderBox;
    this->activeChain.push_back(this->adder);
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

    objectChain.onLeftClickDragEffect = [this](EffectIndex effect, const juce::MouseEvent& event) {
        if (this->activeChain.size() == 2) {
            return ;
        }
        this->dragChainObject(effect, event);
    };
    objectChain.onLeftClickReplaceAfterDrag = [this](EffectIndex effect, const juce::MouseEvent& event) {
        this->swapChainObjects(effect, event);
    };
    objectChain.onLeftClickShowEffect = [this](EffectIndex effect) {
        this->computeView(effect);
    };
    objectChain.onLeftClickRemove = [this](EffectIndex effect) {
        this->removeFromChain(effect);
    };

    addAndMakeVisible(objectChain);
}

void AudioPluginAudioProcessorEditor::selectorPaint(juce::Graphics& g) {
	g.setColour(juce::Colour::fromRGB(ColorsScheme::addBackground[0], ColorsScheme::addBackground[1], ColorsScheme::addBackground[2]));
	g.fillRoundedRectangle(this->effectArea, this->cornerSizeEffectArea);
	g.drawRoundedRectangle(this->effectArea, this->cornerSizeEffectArea, 5.0f);
}

void AudioPluginAudioProcessorEditor::selectorResized() {
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

    for (auto& it : this->selectEffectBox) {
	    it.setVisible(true);
	}
}
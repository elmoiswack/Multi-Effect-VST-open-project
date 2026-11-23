#include "PluginEditor.hpp"

void AudioPluginAudioProcessorEditor::selectorInit() {
    this->selectCustomEffectBox.reserve(5);
    this->chainCustomEffectBox.reserve(6);
    this->activeChain.reserve(5);
   
    this->initEffectObject("Reverb", ColorsScheme::reverbPrimary, EffectIndex::REVERB);
    this->initEffectObject("Distortion", ColorsScheme::distortionPrimary, EffectIndex::DISTORTION);
    this->initEffectObject("Delay", ColorsScheme::delayPrimary, EffectIndex::DELAY);
    this->initEffectObject("Chorus", ColorsScheme::chorusPrimary, EffectIndex::CHORUS);
    this->initEffectObject("EQ", ColorsScheme::eqPrimary, EffectIndex::EQ);

    auto& adderBox = this->chainCustomEffectBox.emplace_back(
        "Adder",
        ColorsScheme::eqPrimary,
        CustomEffectBoxType::ADDER,
        EffectIndex::ADD
    );

    adderBox.onLeftClickShowEffect = [this](EffectIndex effect) {
        juce::ignoreUnused(effect);
        this->computeView(EffectIndex::ADD);
    };

    addAndMakeVisible(adderBox);

    this->adder = &adderBox;
    this->activeChain.push_back(this->adder);
}

void AudioPluginAudioProcessorEditor::initEffectObject(juce::String name, const juce::uint8* color, EffectIndex index) {
    auto& objectSelector = this->selectCustomEffectBox.emplace_back(
        name,
        color,
        CustomEffectBoxType::SELECTOR,
        index
    );
    objectSelector.onLeftClickAdd = [this](EffectIndex effect) {
        selectorClicked(effect);
    };
    addAndMakeVisible(objectSelector);
    
    auto& objectChain = this->chainCustomEffectBox.emplace_back(
        name,
        color,
        CustomEffectBoxType::CHAIN,
        index
    );

    objectChain.onLeftClickDragEffect = [this](const juce::MouseEvent& event) {
        if (this->activeChain.size() == 2) {
            return ;
        }
        this->dragChainObject(event);
    };
    objectChain.onLeftClickReplaceAfterDrag = [this](const juce::MouseEvent& event) {
        this->swapChainObjects(event);
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
    auto widthBox = 150;
    auto heigthBox = 125;

	this->selectCustomEffectBox[EffectIndex::REVERB].setBounds(
        (WindowWidth / 4) - (widthBox / 2), 
        (WindowHeight / 4),
        widthBox,
        heigthBox);

    this->selectCustomEffectBox[EffectIndex::DELAY].setBounds(
        (WindowWidth / 4) - (widthBox / 2), 
        (WindowHeight / 2), 
        widthBox, 
        heigthBox);

    this->selectCustomEffectBox[EffectIndex::EQ].setBounds(
        (WindowWidth / 2) - (widthBox / 2), 
        (WindowHeight / 2) - (heigthBox / 2), 
        widthBox,
        heigthBox);
    
   this->selectCustomEffectBox[EffectIndex::DISTORTION].setBounds(
        (WindowWidth / 4) * 3 - (widthBox / 2), 
        (WindowHeight / 4), 
        widthBox, 
        heigthBox);

    this->selectCustomEffectBox[EffectIndex::CHORUS].setBounds(
        (WindowWidth / 4) * 3 - (widthBox / 2), 
        (WindowHeight / 2), 
        widthBox, 
        heigthBox);

    for (auto& it : this->selectCustomEffectBox) {
	    it.setVisible(true);
	}
}
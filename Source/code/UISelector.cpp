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
	float minWidth = 10.f;
	float maxWidth = 980.f;
	float minHeight = 120.f;
	float maxHeight = 570.f;
	float cornerSize = 20.f;

	auto& bgColor = ColorsScheme::addBackground;

	g.setColour(juce::Colour::fromRGB(bgColor[0], bgColor[1], bgColor[2]));
	g.fillRoundedRectangle(minWidth, minHeight, maxWidth, maxHeight, cornerSize);
	g.drawRoundedRectangle(minWidth, minHeight, maxWidth, maxHeight, cornerSize, 5.0f);
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

	for (std::size_t i = 0; i < this->selectEffectBox.size(); i++) {
		this->selectEffectBox[i].setVisible(true);
	}
}

void AudioPluginAudioProcessorEditor::selectorHide() {
	for (std::size_t i = 0; i < this->selectEffectBox.size(); i++) {
		this->selectEffectBox[i].setVisible(false);
	}
}
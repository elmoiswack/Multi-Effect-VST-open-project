#include "PluginEditor.hpp"

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
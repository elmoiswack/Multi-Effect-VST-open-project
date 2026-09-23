#include "PluginEditor.hpp"

enum eqIndex {
	LOWFREQ,
	LOWGAIN,
	LOWQ,
};

void AudioPluginAudioProcessorEditor::eqInit() {
	this->eqSliders.reserve(3);
	this->eqSliders.emplace_back("Frequency", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary);
	addAndMakeVisible(this->eqSliders[LOWFREQ]);

		this->eqSliders.emplace_back("Gain", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary);
	addAndMakeVisible(this->eqSliders[LOWGAIN]);

		this->eqSliders.emplace_back("Quality", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary);
	addAndMakeVisible(this->eqSliders[LOWQ]);

}

void AudioPluginAudioProcessorEditor::eqPaint(juce::Graphics& g) {
	auto& bgColor = ColorsScheme::eqBackground;

	g.setColour(juce::Colour::fromRGB(bgColor[0], bgColor[1], bgColor[2]));
	g.fillRoundedRectangle(this->effectArea, this->cornerSizeEffectArea);
	g.drawRoundedRectangle(this->effectArea, this->cornerSizeEffectArea, 5.0f);
}

void AudioPluginAudioProcessorEditor::eqResized() {
	auto x = this->effectArea.getX();
	auto y = this->effectArea.getY();
	auto width = this->effectArea.getWidth();
	auto height = this->effectArea.getHeight();
	
	int sliderWidth = 90;
	int sliderHeigth = 90;
	
	int lowX = x + (width / 4) - sliderWidth;
	int lowY = y + (height / 2.5f);
	int yOffset = 110;

	this->eqSliders[LOWFREQ].setBounds(
		lowX,
		lowY,
		sliderWidth,
		sliderHeigth
	);

	this->eqSliders[LOWGAIN].setBounds(
		lowX,
		lowY + yOffset,
		sliderWidth,
		sliderHeigth
	);

	this->eqSliders[LOWQ].setBounds(
		lowX,
		lowY + (yOffset * 2),
		sliderWidth,
		sliderHeigth
	);

	for (std::size_t i = 0; i < this->eqSliders.size(); i++) {
		this->eqSliders[i].setVisible(true);
	}
}

void AudioPluginAudioProcessorEditor::eqHide() {
	for (std::size_t i = 0; i < this->eqSliders.size(); i++) {
		this->eqSliders[i].setVisible(false);
	}
}

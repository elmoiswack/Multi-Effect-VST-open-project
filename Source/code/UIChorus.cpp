#include "PluginEditor.hpp"

enum ChorusIndex {
	CHORUSDELAY,
	RATE,
	DEPTH,
	WIDTH,
	FEEDBACK,
	HIGHCUT,
	MIX
};

void AudioPluginAudioProcessorEditor::chorusInit() {
	this->chorusSliders.reserve(7);

	this->chorusSliders.emplace_back(std::make_unique<CustomSlider>("Delay", ColorsScheme::chorusPrimary, ColorsScheme::chorusSecondary, CHORUSDELAY));
	addAndMakeVisible(*this->chorusSliders[CHORUSDELAY]);

	this->chorusSliders.emplace_back(std::make_unique<CustomSlider>("Rate", ColorsScheme::chorusPrimary, ColorsScheme::chorusSecondary, RATE));
	addAndMakeVisible(*this->chorusSliders[RATE]);
	
	this->chorusSliders.emplace_back(std::make_unique<CustomSlider>("Depth", ColorsScheme::chorusPrimary, ColorsScheme::chorusSecondary, DEPTH));
	addAndMakeVisible(*this->chorusSliders[DEPTH]);
	
	this->chorusSliders.emplace_back(std::make_unique<CustomSlider>("Width", ColorsScheme::chorusPrimary, ColorsScheme::chorusSecondary, WIDTH));
	addAndMakeVisible(*this->chorusSliders[WIDTH]);
	
	this->chorusSliders.emplace_back(std::make_unique<CustomSlider>("Feedback", ColorsScheme::chorusPrimary, ColorsScheme::chorusSecondary, FEEDBACK));
	addAndMakeVisible(*this->chorusSliders[FEEDBACK]);
	
	this->chorusSliders.emplace_back(std::make_unique<CustomSlider>("HighCut", ColorsScheme::chorusPrimary, ColorsScheme::chorusSecondary, HIGHCUT));
	addAndMakeVisible(*this->chorusSliders[HIGHCUT]);
	
	this->chorusSliders.emplace_back(std::make_unique<CustomSlider>("Mix", ColorsScheme::chorusPrimary, ColorsScheme::chorusSecondary, MIX));
	addAndMakeVisible(*this->chorusSliders[MIX]);

	for (auto& slider : this->chorusSliders) {
        slider->onValueChange = [this](int index, float value) {
			//TODO: update index with value
            repaint();
        };
    }
}

void AudioPluginAudioProcessorEditor::chorusPaint(juce::Graphics& g) {
	g.setColour(juce::Colour::fromRGB(ColorsScheme::chorusBackground[0], ColorsScheme::chorusBackground[1], ColorsScheme::chorusBackground[2]));
	g.fillRoundedRectangle(this->effectArea, this->cornerSizeEffectArea);
	g.drawRoundedRectangle(this->effectArea, this->cornerSizeEffectArea, 5.0f);

	auto x = this->effectArea.getX();
    auto y = this->effectArea.getY();
    auto width = this->effectArea.getWidth();
	int sliderWidth = 100;
    int sliderHeight = 100;
	int textWidth = 150;
	int textHeight = 20;
	int textOffestX = 25;

	int startX = x + (sliderWidth * 1.5) - textOffestX;
	int startY = y + sliderHeight;

	juce::Rectangle<int> textArea = {startX, startY, textWidth, textHeight};
	
	g.setColour(juce::Colours::white);
	g.setFont(25.f);

	textArea.setX(this->effectArea.getWidth() - sliderWidth - 20 - textOffestX);
	textArea.setY(this->effectArea.getHeight() - textHeight);
	g.drawText(this->chorusSliders[MIX]->getName(), textArea, juce::Justification::centred, true);
}

void AudioPluginAudioProcessorEditor::chorusResized() {
    auto x = this->effectArea.getX();
    auto y = this->effectArea.getY();
    auto width = this->effectArea.getWidth();
    auto height = this->effectArea.getHeight();
	int sliderWidth = 100;
    int sliderHeight = 100;
	int boxWidth = 120;
	int boxHeight = 70;
	int boxX = (width / 2) - (boxWidth / 2);
	int boxY = (getLocalBounds().getHeight() / 2) - (boxHeight * 1.5); 

	this->chorusSliders[MIX]->setBounds(width - sliderWidth - 20, height, sliderWidth, sliderHeight);

	this->setSlidersVisable(this->chorusSliders, true);
}


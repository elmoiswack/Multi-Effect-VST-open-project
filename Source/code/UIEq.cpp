#include "PluginEditor.hpp"

enum eqIndex {
	LOWFREQ,
	LOWGAIN,
	LOWQ,
};

void AudioPluginAudioProcessorEditor::eqInit() {
	this->eqSliders.reserve(3);
	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Frequency", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, LOWFREQ));
	addAndMakeVisible(*this->eqSliders[LOWFREQ]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Gain", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, LOWGAIN));
	addAndMakeVisible(*this->eqSliders[LOWGAIN]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Quality", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, LOWQ));
	addAndMakeVisible(*this->eqSliders[LOWQ]);

  	for (auto& slider : eqSliders) {
        slider->moveSlider = [this](const juce::MouseEvent& event, int index) {
            int xPos = event.getEventRelativeTo(this).getPosition().x;
            this->eqSliders[index]->setSliderPos((float)xPos);
        };
    }
}

void AudioPluginAudioProcessorEditor::eqPaint(juce::Graphics& g) {
	auto& bgColor = ColorsScheme::eqBackground;

	g.setColour(juce::Colour::fromRGB(bgColor[0], bgColor[1], bgColor[2]));
	g.fillRoundedRectangle(this->effectArea, this->cornerSizeEffectArea);
	g.drawRoundedRectangle(this->effectArea, this->cornerSizeEffectArea, 5.0f);

	auto x = this->effectArea.getX();
	auto y = this->effectArea.getY();
	auto width = this->effectArea.getWidth();
	auto height = this->effectArea.getHeight();
	
	int sliderWidth = 90;
	
	float lowX = x + (width / 4) - sliderWidth;
	float lowY = y + (height / 2.5f);
	float yOffset = 110.f;
	juce::Rectangle<float> low = {lowX, lowY - 20.f, 100.f, 20.f};


	g.setColour(juce::Colour::fromRGB(ColorsScheme::eqSecondary[0], ColorsScheme::eqSecondary[1], ColorsScheme::eqSecondary[2]));	
	g.drawText(this->eqSliders[LOWFREQ]->getName(), low, juce::Justification::centred, true);

	low.setY(lowY - 20.f + yOffset);
	g.drawText(this->eqSliders[LOWGAIN]->getName(), low, juce::Justification::centred, true);
	
	low.setY(lowY - 20.f + (yOffset * 2));
	g.drawText(this->eqSliders[LOWQ]->getName(), low, juce::Justification::centred, true);
	
}

void AudioPluginAudioProcessorEditor::eqResized() {
	auto x = this->effectArea.getX();
	auto y = this->effectArea.getY();
	auto width = this->effectArea.getWidth();
	auto height = this->effectArea.getHeight();
	
	int sliderWidth = 80;
	int sliderHeigth = 80;
	
	int lowX = x + (width / 4) - sliderWidth;
	int lowY = y + (height / 2.5f);
	int yOffset = 110;

	this->eqSliders[LOWFREQ]->setBounds(
		lowX,
		lowY,
		sliderWidth,
		sliderHeigth
	);

	this->eqSliders[LOWGAIN]->setBounds(
		lowX,
		lowY + yOffset,
		sliderWidth,
		sliderHeigth
	);

	this->eqSliders[LOWQ]->setBounds(
		lowX,
		lowY + (yOffset * 2),
		sliderWidth,
		sliderHeigth
	);

	for (std::size_t i = 0; i < this->eqSliders.size(); i++) {
		this->eqSliders[i]->setVisible(true);
	}
}

void AudioPluginAudioProcessorEditor::eqHide() {
	for (std::size_t i = 0; i < this->eqSliders.size(); i++) {
		this->eqSliders[i]->setVisible(false);
	}
}

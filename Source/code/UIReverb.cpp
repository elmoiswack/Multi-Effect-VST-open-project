#include "PluginEditor.hpp"

enum ReverbIndex {
	DECAY,
	PREDELAY,
	TONE,
	SIZE,
	HIGHCUT,
	LOWCUT
};

void AudioPluginAudioProcessorEditor::reverbInit() {
	this->reverbSliders.reserve(6);
	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("Decay", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, DECAY));
	addAndMakeVisible(*this->reverbSliders[DECAY]);

	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("PreDelay", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, PREDELAY));
	addAndMakeVisible(*this->reverbSliders[PREDELAY]);

	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("Tone", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, TONE));
	addAndMakeVisible(*this->reverbSliders[TONE]);

	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("Size", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, SIZE));
	addAndMakeVisible(*this->reverbSliders[SIZE]);

	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("HighCut", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, HIGHCUT));
	addAndMakeVisible(*this->reverbSliders[HIGHCUT]);

	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("LowCut", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, LOWCUT));
	addAndMakeVisible(*this->reverbSliders[LOWCUT]);

  	for (auto& slider : reverbSliders) {
        slider->onValueChange = [this](int index, float value) {
			//TODO: update index with value
            repaint();
        };
    }

	this->reverbLAFCB.setColors(ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary);
	this->reverbLAFCB.setFontSize(25.0f);
	this->reverbLAFCB.setCornerRadius(6.0f);

	this->reverbType.setLookAndFeel(&this->reverbLAFCB);
	addAndMakeVisible(this->reverbType);
	this->reverbType.addItem("Plate",  1);
	this->reverbType.addItem("Spring", 2);
	this->reverbType.addItem("Hall", 3);
	this->reverbType.setSelectedId(1);

}

void AudioPluginAudioProcessorEditor::reverbPaint(juce::Graphics& g) {
	g.setColour(juce::Colour::fromRGB(ColorsScheme::reverbBackground[0], ColorsScheme::reverbBackground[1], ColorsScheme::reverbBackground[2]));
	g.fillRoundedRectangle(this->effectArea, this->cornerSizeEffectArea);
	g.drawRoundedRectangle(this->effectArea, this->cornerSizeEffectArea, 5.0f);

	auto x = this->effectArea.getX();
    auto y = this->effectArea.getY();
    auto width = this->effectArea.getWidth();
	int sliderWidth = 100;
    int sliderHeight = 100;
	int textWidth = 100;
	int textHeight = 20;

	int startX = x + (sliderWidth * 1.5);
	int startY = y + sliderHeight;
	
	juce::Rectangle<int> textArea = {startX, startY, textWidth, textHeight};

	g.setColour(juce::Colours::white);	
	g.setFont(25.f);

	textArea.setY(startY - textHeight);
    g.drawText(this->reverbSliders[DECAY]->getName(), textArea, juce::Justification::centred, true);

	textArea.setY(startY + (sliderHeight * 1.5) - textHeight);
    g.drawText(this->reverbSliders[PREDELAY]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(width / 2 - (sliderWidth * 1.8));
	textArea.setY((getLocalBounds().getHeight() / 2) + (sliderHeight / 2) - textHeight);
    g.drawText(this->reverbSliders[TONE]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(width / 2 - (sliderWidth * 1.8) + (getLocalBounds().getWidth() / 4));
    g.drawText(this->reverbSliders[SIZE]->getName(), textArea, juce::Justification::centred, true);
	
	int boxWidth = 100;
	int boxHeight = 70;
	textArea.setX((width / 2) - (boxWidth / 2));
	textArea.setY((getLocalBounds().getHeight() / 2) - (boxHeight / 2) - textHeight - 10); //remove magic number
    g.drawText("Type", textArea, juce::Justification::centred, true);

	textArea.setX(width - (sliderWidth * 1.5) - sliderWidth);
	textArea.setY(startY - textHeight);
    g.drawText(this->reverbSliders[HIGHCUT]->getName(), textArea, juce::Justification::centred, true);

	textArea.setY(startY + (sliderHeight * 1.5) - textHeight);
    g.drawText(this->reverbSliders[LOWCUT]->getName(), textArea, juce::Justification::centred, true);
	
}

void AudioPluginAudioProcessorEditor::reverbResized() {
    auto x = this->effectArea.getX();
    auto y = this->effectArea.getY();
    auto width = this->effectArea.getWidth();
    auto height = this->effectArea.getHeight();
	int sliderWidth = 100;
    int sliderHeight = 100;
	int boxWidth = 100;
	int boxHeight = 70;
	int boxX = (width / 2) - (boxWidth / 2);
	int boxY = (getLocalBounds().getHeight() / 2) - (boxHeight / 2); 


	int startX = x + (sliderWidth * 1.5);
	int startY = y + sliderHeight;
	this->reverbSliders[DECAY]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->reverbSliders[PREDELAY]->setBounds(startX, startY + (sliderHeight * 1.5), sliderWidth, sliderHeight);

	startX = width / 2 - (sliderWidth * 1.8);
	startY = (getLocalBounds().getHeight() / 2) + (sliderHeight / 2);
	this->reverbSliders[TONE]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->reverbSliders[SIZE]->setBounds(startX + (getLocalBounds().getWidth() / 4), startY, sliderWidth, sliderHeight);

	startX = width - (sliderWidth * 1.5) - sliderWidth;
	startY = y + sliderHeight;
	this->reverbSliders[HIGHCUT]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->reverbSliders[LOWCUT]->setBounds(startX, startY + (sliderHeight * 1.5), sliderWidth, sliderHeight);

	for (std::size_t i = 0; i < this->reverbSliders.size(); i++) {
		this->reverbSliders[i]->setVisible(true);
	}

	this->reverbType.setBounds(boxX, boxY, boxWidth, boxHeight);
	this->reverbType.setVisible(true);
}

void AudioPluginAudioProcessorEditor::reverbHide() {
	for (std::size_t i = 0; i < this->reverbSliders.size(); i++) {
		this->reverbSliders[i]->setVisible(false);
	}

	this->reverbType.setVisible(false);
}

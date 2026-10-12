#include "PluginEditor.hpp"

enum DelayIndex {
	LEFTDELAY,
	LEFTFEEDBACK,
	RIGHTDELAY,
	RIGHTFEEDBACK,
	LOWCUT,
	HIGHCUT,
	MIX
};

void AudioPluginAudioProcessorEditor::delayInit() {
	this->delaySliders.reserve(7);

	this->delaySliders.emplace_back(std::make_unique<CustomSlider>("Left", ColorsScheme::delayPrimary, ColorsScheme::delaySecondary, LEFTDELAY));
	addAndMakeVisible(*this->delaySliders[LEFTDELAY]);

	this->delaySliders.emplace_back(std::make_unique<CustomSlider>("Feedback", ColorsScheme::delayPrimary, ColorsScheme::delaySecondary, LEFTFEEDBACK));
	addAndMakeVisible(*this->delaySliders[LEFTFEEDBACK]);

	this->delaySliders.emplace_back(std::make_unique<CustomSlider>("Right", ColorsScheme::delayPrimary, ColorsScheme::delaySecondary, RIGHTDELAY));
	addAndMakeVisible(*this->delaySliders[RIGHTDELAY]);
	
	this->delaySliders.emplace_back(std::make_unique<CustomSlider>("Feedback", ColorsScheme::delayPrimary, ColorsScheme::delaySecondary, RIGHTFEEDBACK));
	addAndMakeVisible(*this->delaySliders[RIGHTFEEDBACK]);

	this->delaySliders.emplace_back(std::make_unique<CustomSlider>("Lowcut", ColorsScheme::delayPrimary, ColorsScheme::delaySecondary, LOWCUT));
	addAndMakeVisible(*this->delaySliders[LOWCUT]);

	this->delaySliders.emplace_back(std::make_unique<CustomSlider>("Highcut", ColorsScheme::delayPrimary, ColorsScheme::delaySecondary, HIGHCUT));
	addAndMakeVisible(*this->delaySliders[HIGHCUT]);

	this->delaySliders.emplace_back(std::make_unique<CustomSlider>("Mix", ColorsScheme::delayPrimary, ColorsScheme::delaySecondary, MIX));
	addAndMakeVisible(*this->delaySliders[MIX]);

	for (auto& slider : this->chorusSliders) {
        slider->onValueChange = [this](int index, float value) {
			//TODO: update index with value
			//TODO: If index == LEFTDELAY || RIGHTDELAY en sync staat aan, update beiden.
            repaint();
        };
    }

	this->delayLAFCB.setColors(ColorsScheme::delayPrimary, ColorsScheme::delaySecondary);
	this->delayLAFCB.setFontSize(25.0f);
	this->delayLAFCB.setCornerRadius(6.0f);

	this->delayType.setLookAndFeel(&this->delayLAFCB);
	addAndMakeVisible(this->delayType);
	this->delayType.addItem("Free",  1);
	this->delayType.addItem("Sync", 2);
	this->delayType.addItem("Ping-Pong", 3);
	this->delayType.setSelectedId(1);

	this->leftTimeOption.setLookAndFeel(&this->delayLAFCB);
	addAndMakeVisible(this->leftTimeOption);
	this->leftTimeOption.addItem("Free",  1);
	this->leftTimeOption.addItem("4th Note", 2);
	this->leftTimeOption.addItem("8th Note", 3);
	this->leftTimeOption.addItem("16th Note", 4);
	this->leftTimeOption.setSelectedId(1);

	this->rightTimeOption.setLookAndFeel(&this->delayLAFCB);
	addAndMakeVisible(this->rightTimeOption);
	this->rightTimeOption.addItem("Free",  1);
	this->rightTimeOption.addItem("4th Note", 2);
	this->rightTimeOption.addItem("8th Note", 3);
	this->rightTimeOption.addItem("16th Note", 4);
	this->rightTimeOption.setSelectedId(1);

	//TODO: make an updater for all ComboBoxes
}

void AudioPluginAudioProcessorEditor::delayPaint(juce::Graphics& g) {
	g.setColour(juce::Colour::fromRGB(ColorsScheme::delayBackground[0], ColorsScheme::delayBackground[1], ColorsScheme::delayBackground[2]));
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
    g.drawText(this->delaySliders[LEFTDELAY]->getName(), textArea, juce::Justification::centred, true);

	textArea.setY(startY + (sliderHeight * 1.5) - textHeight);
    g.drawText(this->delaySliders[LEFTFEEDBACK]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(width / 2 - (sliderWidth * 1.8));
	textArea.setY((getLocalBounds().getHeight() / 2) + (sliderHeight / 2) - textHeight);
    g.drawText(this->delaySliders[RIGHTDELAY]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(width / 2 - (sliderWidth * 1.8) + (getLocalBounds().getWidth() / 4));
    g.drawText(this->delaySliders[RIGHTFEEDBACK]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(width - (sliderWidth * 1.5) - sliderWidth);
	textArea.setY(startY - textHeight);
    g.drawText(this->delaySliders[LOWCUT]->getName(), textArea, juce::Justification::centred, true);

	textArea.setY(startY + (sliderHeight * 1.5) - textHeight);
    g.drawText(this->delaySliders[HIGHCUT]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(this->effectArea.getWidth() - sliderWidth - 20);
	textArea.setY(this->effectArea.getHeight() - textHeight);
	g.drawText(this->delaySliders[MIX]->getName(), textArea, juce::Justification::centred, true);

	int boxWidth = 120;
	int boxHeight = 70;
	textArea.setX(x + (sliderWidth * 1.5));
	textArea.setY(startY + (sliderHeight * 2.5) + (boxHeight / 2) - textHeight - 7);
    g.drawText("Note", textArea, juce::Justification::centred, true);
	
	textArea.setX((width / 2) - (boxWidth / 2));
	textArea.setY((getLocalBounds().getHeight() / 2) - (boxHeight * 1.5) - textHeight - 7); //remove magic number
    g.drawText("Type", textArea, juce::Justification::centred, true);

	textArea.setX(width - (sliderWidth * 1.5) - sliderWidth);
	textArea.setY(startY + (sliderHeight * 2.5) + (boxHeight / 2) - textHeight - 7);
    g.drawText("Note", textArea, juce::Justification::centred, true);
}

void AudioPluginAudioProcessorEditor::delayResized() {
    auto x = this->effectArea.getX();
    auto y = this->effectArea.getY();
    auto width = this->effectArea.getWidth();
    auto height = this->effectArea.getHeight();
	int sliderWidth = 100;
    int sliderHeight = 100;
	int boxWidth = 120;
	int boxHeight = 70;

	int startX = x + (sliderWidth * 1.5);
	int startY = y + sliderHeight;
	this->delaySliders[LEFTDELAY]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->delaySliders[LEFTFEEDBACK]->setBounds(startX, startY + (sliderHeight * 1.5), sliderWidth, sliderHeight);

	startX = width / 2 - (sliderWidth * 1.8);
	startY = (getLocalBounds().getHeight() / 2) + (sliderHeight / 2);
	this->delaySliders[LOWCUT]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->delaySliders[HIGHCUT]->setBounds(startX + (getLocalBounds().getWidth() / 4), startY, sliderWidth, sliderHeight);

	startX = width - (sliderWidth * 1.5) - sliderWidth;
	startY = y + sliderHeight;
	this->delaySliders[RIGHTDELAY]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->delaySliders[RIGHTFEEDBACK]->setBounds(startX, startY + (sliderHeight * 1.5), sliderWidth, sliderHeight);

	this->delaySliders[MIX]->setBounds(width - sliderWidth - 20, height, sliderWidth, sliderHeight);

	int boxX = x + (sliderWidth * 1.5);
	int boxY = startY + (sliderHeight * 2.5) + (boxHeight / 2);
	this->leftTimeOption.setBounds(boxX, boxY, boxWidth, boxHeight);

	boxX = (width / 2) - (boxWidth / 2);
	boxY = (getLocalBounds().getHeight() / 2) - (boxHeight * 1.5);
	this->delayType.setBounds(boxX, boxY, boxWidth, boxHeight);
	
	boxX = width - (sliderWidth * 1.5) - sliderWidth;
	boxY = startY + (sliderHeight * 2.5) + (boxHeight / 2);
	this->rightTimeOption.setBounds(boxX, boxY, boxWidth, boxHeight);

	this->delayType.setVisible(true);
	this->leftTimeOption.setVisible(true);
	this->rightTimeOption.setVisible(true);
	this->setSlidersVisable(this->delaySliders, true);
}

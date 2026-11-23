#include "PluginEditor.hpp"
#include "EnumIndexes.hpp"

void AudioPluginAudioProcessorEditor::delayInit() {
	this->delaySliders.reserve(7);

	this->delaySliders.emplace_back(std::make_unique<CustomSlider>("delay.left.time", "Left", ColorsScheme::delayPrimary, ColorsScheme::delaySecondary, this->processorRef));
	addAndMakeVisible(*this->delaySliders[static_cast<int>(DelayIndex::LEFTDELAY)]);

	this->delaySliders.emplace_back(std::make_unique<CustomSlider>("delay.left.feedback", "Feedback", ColorsScheme::delayPrimary, ColorsScheme::delaySecondary, this->processorRef));
	addAndMakeVisible(*this->delaySliders[static_cast<int>(DelayIndex::LEFTFEEDBACK)]);

	this->delaySliders.emplace_back(std::make_unique<CustomSlider>("delay.right.time", "Right", ColorsScheme::delayPrimary, ColorsScheme::delaySecondary, this->processorRef));
	addAndMakeVisible(*this->delaySliders[static_cast<int>(DelayIndex::RIGHTDELAY)]);

	this->delaySliders.emplace_back(std::make_unique<CustomSlider>("delay.right.feedback", "Feedback", ColorsScheme::delayPrimary, ColorsScheme::delaySecondary, this->processorRef));
	addAndMakeVisible(*this->delaySliders[static_cast<int>(DelayIndex::RIGHTFEEDBACK)]);

	this->delaySliders.emplace_back(std::make_unique<CustomSlider>("delay.lowcut", "Lowcut", ColorsScheme::delayPrimary, ColorsScheme::delaySecondary, this->processorRef));
	addAndMakeVisible(*this->delaySliders[static_cast<int>(DelayIndex::LOWCUT)]);

	this->delaySliders.emplace_back(std::make_unique<CustomSlider>("delay.highcut", "Highcut", ColorsScheme::delayPrimary, ColorsScheme::delaySecondary, this->processorRef));
	addAndMakeVisible(*this->delaySliders[static_cast<int>(DelayIndex::HIGHCUT)]);

	this->delaySliders.emplace_back(std::make_unique<CustomSlider>("delay.mix", "Mix", ColorsScheme::delayPrimary, ColorsScheme::delaySecondary, this->processorRef));
	addAndMakeVisible(*this->delaySliders[static_cast<int>(DelayIndex::MIX)]);

	this->delayLAFCB.setColors(ColorsScheme::delayPrimary, ColorsScheme::delaySecondary);
	this->delayLAFCB.setFontSize(25.0f);
	this->delayLAFCB.setCornerRadius(6.0f);

	this->delayType.setLookAndFeel(&this->delayLAFCB);
	addAndMakeVisible(this->delayType);
	this->delayType.addItem("Free",  1);
	this->delayType.addItem("Sync", 2);
	this->delayType.addItem("Ping-Pong", 3);
	this->delayType.setSelectedId(1);

	for (auto* box : { &this->leftTimeOption, &this->rightTimeOption }) {
		box->setLookAndFeel(&this->delayLAFCB);
		addAndMakeVisible(box);
		box->addItem("Free",  1);
		box->addItem("4th Note", 2);
		box->addItem("8th Note", 3);
		box->addItem("16th Note", 4);
		box->setSelectedId(1);
	}

	delayHandler();
}

void AudioPluginAudioProcessorEditor::delayHandler() {
	for (auto& slider : this->delaySliders) {
        slider->onValueChange = [this](float value, juce::String id) {
			auto param = processorRef.getAPVTS().getParameter(id);
			param->setValueNotifyingHost(value);

			// if id contains .time and sync = on, update both left and right

        };
    }

	this->delayType.onChange = [this]() {
		auto param = processorRef.getAPVTS().getParameter("delay.type");
		param->setValueNotifyingHost(this->delayType.getSelectedId());
	};

	this->leftTimeOption.onChange = [this]() {
		auto param = processorRef.getAPVTS().getParameter("delay.left.option");
		param->setValueNotifyingHost(this->leftTimeOption.getSelectedId());
	};

	this->rightTimeOption.onChange = [this]() {
		auto param = processorRef.getAPVTS().getParameter("delay.right.option");
		param->setValueNotifyingHost(this->rightTimeOption.getSelectedId());
	};
}

void AudioPluginAudioProcessorEditor::delayPaint(juce::Graphics& g) {
	g.setColour(juce::Colour::fromRGB(ColorsScheme::delayBackground[0], ColorsScheme::delayBackground[1], ColorsScheme::delayBackground[2]));
	g.fillRoundedRectangle(this->effectArea, this->cornerSizeEffectArea);
	g.drawRoundedRectangle(this->effectArea, this->cornerSizeEffectArea, 5.0f);

	int x = static_cast<int>(this->effectArea.getX());
    int y = static_cast<int>(this->effectArea.getY());
    int width = static_cast<int>(this->effectArea.getWidth());
	int height = static_cast<int>(this->effectArea.getHeight());
	int sliderWidth = 100;
    int sliderHeight = 100;
	int textWidth = 100;
	int textHeight = 25;

	int sliderheightOffset = static_cast<int>(sliderHeight * 1.5);
	int sliderWidthOffset = static_cast<int>(sliderWidth * 1.5);
	int startX = x + sliderWidthOffset;
	int startY = y + sliderHeight;
	
	juce::Rectangle<int> textArea = {startX, startY, textWidth, textHeight};

	g.setColour(juce::Colours::white);	
	g.setFont(25.f);

	textArea.setY(startY - textHeight);
    g.drawText(this->delaySliders[static_cast<int>(DelayIndex::LEFTDELAY)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setY(startY + sliderheightOffset - textHeight);
    g.drawText(this->delaySliders[static_cast<int>(DelayIndex::LEFTFEEDBACK)]->getName(), textArea, juce::Justification::centred, true);

	sliderWidthOffset = static_cast<int>(sliderWidth * 1.8);
	textArea.setX(width / 2 - sliderWidthOffset);
	textArea.setY((getLocalBounds().getHeight() / 2) + (sliderHeight / 2) - textHeight);
    g.drawText(this->delaySliders[static_cast<int>(DelayIndex::LOWCUT)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(width / 2 - sliderWidthOffset + (getLocalBounds().getWidth() / 4));
    g.drawText(this->delaySliders[static_cast<int>(DelayIndex::HIGHCUT)]->getName(), textArea, juce::Justification::centred, true);

	sliderWidthOffset = static_cast<int>(sliderWidth * 1.5);
	textArea.setX(width - sliderWidthOffset - sliderWidth);
	textArea.setY(startY - textHeight);
    g.drawText(this->delaySliders[static_cast<int>(DelayIndex::RIGHTDELAY)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setY(startY + sliderheightOffset - textHeight);
    g.drawText(this->delaySliders[static_cast<int>(DelayIndex::RIGHTFEEDBACK)]->getName(), textArea, juce::Justification::centred, true);

	int textOffsetX = 20;
	textArea.setX(width - sliderWidth - textOffsetX);
	textArea.setY(height - textHeight);
	g.drawText(this->delaySliders[static_cast<int>(DelayIndex::MIX)]->getName(), textArea, juce::Justification::centred, true);

	int boxWidth = 120;
	int boxHeight = 70;
	int textOffsetY = 7;
	sliderheightOffset = static_cast<int>(sliderHeight * 2.5);
	int boxOffsetY = static_cast<int>(boxHeight * 1.5);

	textArea.setX(x + sliderWidthOffset);
	textArea.setY(startY + sliderheightOffset + (boxHeight / 2) - textHeight - textOffsetY);
    g.drawText("Note", textArea, juce::Justification::centred, true);
	
	textArea.setX((getLocalBounds().getWidth() / 2) - (boxWidth / 2));
	textArea.setY((getLocalBounds().getHeight() / 2) - boxOffsetY - textHeight - textOffsetY);
    g.drawText("Type", textArea, juce::Justification::centred, true);

	textArea.setX(width - sliderWidthOffset - sliderWidth);
	textArea.setY(startY + sliderheightOffset + (boxHeight / 2) - textHeight - textOffsetY);
    g.drawText("Note", textArea, juce::Justification::centred, true);
}

void AudioPluginAudioProcessorEditor::delayResized() {
    int x = static_cast<int>(this->effectArea.getX());
    int y = static_cast<int>(this->effectArea.getY());
    int width = static_cast<int>(this->effectArea.getWidth());
    int height = static_cast<int>(this->effectArea.getHeight());
	int sliderWidth = 100;
    int sliderHeight = 100;
	int boxWidth = 120;
	int boxHeight = 70;

	int sliderheightOffset = static_cast<int>(sliderHeight * 1.5);
	int sliderWidthOffset = static_cast<int>(sliderWidth * 1.5);
	int startX = x + sliderWidthOffset;
	int startY = y + sliderHeight;

	this->delaySliders[static_cast<int>(DelayIndex::LEFTDELAY)]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->delaySliders[static_cast<int>(DelayIndex::LEFTFEEDBACK)]->setBounds(startX, startY + sliderheightOffset, sliderWidth, sliderHeight);

	startX = width / 2 - static_cast<int>(sliderWidth * 1.8);
	startY = (getLocalBounds().getHeight() / 2) + (sliderHeight / 2);
	this->delaySliders[static_cast<int>(DelayIndex::LOWCUT)]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->delaySliders[static_cast<int>(DelayIndex::HIGHCUT)]->setBounds(startX + (getLocalBounds().getWidth() / 4), startY, sliderWidth, sliderHeight);

	startX = width - sliderWidthOffset - sliderWidth;
	startY = y + sliderHeight;
	this->delaySliders[static_cast<int>(DelayIndex::RIGHTDELAY)]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->delaySliders[static_cast<int>(DelayIndex::RIGHTFEEDBACK)]->setBounds(startX, startY + sliderheightOffset, sliderWidth, sliderHeight);

	this->delaySliders[static_cast<int>(DelayIndex::MIX)]->setBounds(width - sliderWidth - 20, height, sliderWidth, sliderHeight);

	sliderheightOffset = static_cast<int>(sliderHeight * 2.5);
	int boxX = x + sliderWidthOffset;
	int boxY = startY + sliderheightOffset + (boxHeight / 2);
	int boxOffsetY = static_cast<int>(boxHeight * 1.5);
	this->leftTimeOption.setBounds(boxX, boxY, boxWidth, boxHeight);

	boxX = (getLocalBounds().getWidth() / 2) - (boxWidth / 2);
	boxY = (getLocalBounds().getHeight() / 2) - boxOffsetY;
	this->delayType.setBounds(boxX, boxY, boxWidth, boxHeight);
	
	boxX = width - sliderWidthOffset - sliderWidth;
	boxY = startY + sliderheightOffset + (boxHeight / 2);
	this->rightTimeOption.setBounds(boxX, boxY, boxWidth, boxHeight);

	this->delayType.setVisible(true);
	this->leftTimeOption.setVisible(true);
	this->rightTimeOption.setVisible(true);
	this->setSlidersVisable(this->delaySliders, true);
}

#include "PluginEditor.hpp"
#include "EnumIndexes.hpp"

void AudioPluginAudioProcessorEditor::reverbInit() {
	this->reverbSliders.reserve(7);

	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("reverb.decay", "Decay", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, this->processorRef));
	addAndMakeVisible(*this->reverbSliders[static_cast<int>(ReverbIndex::DECAY)]);

	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("reverb.predelay", "PreDelay", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, this->processorRef));
	addAndMakeVisible(*this->reverbSliders[static_cast<int>(ReverbIndex::PREDELAY)]);

	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("reverb.tone", "Tone", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, this->processorRef));
	addAndMakeVisible(*this->reverbSliders[static_cast<int>(ReverbIndex::TONE)]);

	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("reverb.size", "Size", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, this->processorRef));
	addAndMakeVisible(*this->reverbSliders[static_cast<int>(ReverbIndex::SIZE)]);

	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("reverb.highcut", "HighCut", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, this->processorRef));
	addAndMakeVisible(*this->reverbSliders[static_cast<int>(ReverbIndex::HIGHCUT)]);

	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("reverb.lowcut", "LowCut", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, this->processorRef));
	addAndMakeVisible(*this->reverbSliders[static_cast<int>(ReverbIndex::LOWCUT)]);

	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("reverb.mix", "Mix", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, this->processorRef));
	addAndMakeVisible(*this->reverbSliders[static_cast<int>(ReverbIndex::MIX)]);

	this->reverbLAFCB.setColors(ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary);
	this->reverbLAFCB.setFontSize(25.0f);
	this->reverbLAFCB.setCornerRadius(6.0f);

	this->reverbType.setLookAndFeel(&this->reverbLAFCB);
	addAndMakeVisible(this->reverbType);
	this->reverbType.addItem("Plate",  1);
	this->reverbType.addItem("Spring", 2);
	this->reverbType.addItem("Hall", 3);
	this->reverbType.setSelectedId(1);

	reverbHandler();
}

void AudioPluginAudioProcessorEditor::reverbHandler() {
	for (auto& slider : this->reverbSliders) {
        slider->onValueChange = [this](float value, juce::String id) {
			auto param = processorRef.getAPVTS().getParameter(id);
			param->setValueNotifyingHost(value);
        };
    }

	this->reverbType.onChange = [this]() {
		auto param = processorRef.getAPVTS().getParameter("reverb.type");
		param->setValueNotifyingHost(this->reverbType.getSelectedId());
	};
}

void AudioPluginAudioProcessorEditor::reverbPaint(juce::Graphics& g) {
	g.setColour(juce::Colour::fromRGB(ColorsScheme::reverbBackground[0], ColorsScheme::reverbBackground[1], ColorsScheme::reverbBackground[2]));
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
    g.drawText(this->reverbSliders[static_cast<int>(ReverbIndex::DECAY)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setY(startY + sliderheightOffset - textHeight);
    g.drawText(this->reverbSliders[static_cast<int>(ReverbIndex::PREDELAY)]->getName(), textArea, juce::Justification::centred, true);

	sliderWidthOffset = static_cast<int>(sliderWidth * 1.8);
	textArea.setX(width / 2 - sliderWidthOffset);
	textArea.setY((getLocalBounds().getHeight() / 2) + (sliderHeight / 2) - textHeight);
    g.drawText(this->reverbSliders[static_cast<int>(ReverbIndex::TONE)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(width / 2 - sliderWidthOffset + (getLocalBounds().getWidth() / 4));
    g.drawText(this->reverbSliders[static_cast<int>(ReverbIndex::SIZE)]->getName(), textArea, juce::Justification::centred, true);
	
	sliderWidthOffset = static_cast<int>(sliderWidth * 1.5);
	int boxWidth = 120;
	int boxHeight = 70;
	int boxOffsetY = static_cast<int>(boxHeight * 1.5) + 10;
	textArea.setX((getLocalBounds().getWidth() / 2) - (boxWidth / 2));
	textArea.setY((getLocalBounds().getHeight() / 2) - boxOffsetY - textHeight);
    g.drawText("Type", textArea, juce::Justification::centred, true);

	textArea.setX(width - sliderWidthOffset - sliderWidth);
	textArea.setY(startY - textHeight);
    g.drawText(this->reverbSliders[static_cast<int>(ReverbIndex::HIGHCUT)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setY(startY + sliderheightOffset - textHeight);
    g.drawText(this->reverbSliders[static_cast<int>(ReverbIndex::LOWCUT)]->getName(), textArea, juce::Justification::centred, true);

	int textOffsetX = 20;
	textArea.setX(width - sliderWidth - textOffsetX);
	textArea.setY(height - textHeight);
	g.drawText(this->reverbSliders[static_cast<int>(ReverbIndex::MIX)]->getName(), textArea, juce::Justification::centred, true);
}

void AudioPluginAudioProcessorEditor::reverbResized() {
    int x = static_cast<int>(this->effectArea.getX());
    int y = static_cast<int>(this->effectArea.getY());
    int width = static_cast<int>(this->effectArea.getWidth());
    int height = static_cast<int>(this->effectArea.getHeight());
	int sliderWidth = 100;
    int sliderHeight = 100;

	int sliderheightOffset = static_cast<int>(sliderHeight * 1.5);
	int sliderWidthOffset = static_cast<int>(sliderWidth * 1.5);
	int startX = x + sliderWidthOffset;
	int startY = y + sliderHeight;
	this->reverbSliders[static_cast<int>(ReverbIndex::DECAY)]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->reverbSliders[static_cast<int>(ReverbIndex::PREDELAY)]->setBounds(startX, startY + sliderheightOffset, sliderWidth, sliderHeight);

	startX = width / 2 - static_cast<int>(sliderWidth * 1.8);
	startY = (getLocalBounds().getHeight() / 2) + (sliderHeight / 2);
	this->reverbSliders[static_cast<int>(ReverbIndex::TONE)]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->reverbSliders[static_cast<int>(ReverbIndex::SIZE)]->setBounds(startX + (getLocalBounds().getWidth() / 4), startY, sliderWidth, sliderHeight);

	startX = width - sliderWidthOffset - sliderWidth;
	startY = y + sliderHeight;
	this->reverbSliders[static_cast<int>(ReverbIndex::HIGHCUT)]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->reverbSliders[static_cast<int>(ReverbIndex::LOWCUT)]->setBounds(startX, startY + sliderheightOffset, sliderWidth, sliderHeight);

	int textOffsetX = 20;
	this->reverbSliders[static_cast<int>(ReverbIndex::MIX)]->setBounds(width - sliderWidth - textOffsetX, height, sliderWidth, sliderHeight);

	int boxWidth = 120;
	int boxHeight = 70;
	int boxOffsetY = static_cast<int>(boxHeight * 1.5);
	int boxX = (getLocalBounds().getWidth() / 2) - (boxWidth / 2);
	int boxY = (getLocalBounds().getHeight() / 2) - boxOffsetY;

	this->reverbType.setBounds(boxX, boxY, boxWidth, boxHeight);
	this->reverbType.setVisible(true);
	this->setSlidersVisable(this->reverbSliders, true);
}
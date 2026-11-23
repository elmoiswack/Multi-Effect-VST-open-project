#include "PluginEditor.hpp"
#include "EnumIndexes.hpp"

void AudioPluginAudioProcessorEditor::chorusInit() {
	this->chorusSliders.reserve(7);

	this->chorusSliders.emplace_back(std::make_unique<CustomSlider>("chorus.delay", "Delay", ColorsScheme::chorusPrimary, ColorsScheme::chorusSecondary, this->processorRef));
	addAndMakeVisible(*this->chorusSliders[static_cast<int>(ChorusIndex::DELAY)]);

	this->chorusSliders.emplace_back(std::make_unique<CustomSlider>("chorus.rate", "Rate", ColorsScheme::chorusPrimary, ColorsScheme::chorusSecondary, this->processorRef));
	addAndMakeVisible(*this->chorusSliders[static_cast<int>(ChorusIndex::RATE)]);	

	this->chorusSliders.emplace_back(std::make_unique<CustomSlider>("chorus.depth", "Depth", ColorsScheme::chorusPrimary, ColorsScheme::chorusSecondary, this->processorRef));
	addAndMakeVisible(*this->chorusSliders[static_cast<int>(ChorusIndex::DEPTH)]);
	
	this->chorusSliders.emplace_back(std::make_unique<CustomSlider>("chorus.width", "Width", ColorsScheme::chorusPrimary, ColorsScheme::chorusSecondary, this->processorRef));
	addAndMakeVisible(*this->chorusSliders[static_cast<int>(ChorusIndex::WIDTH)]);
	
	this->chorusSliders.emplace_back(std::make_unique<CustomSlider>("chorus.feedback", "Feedback", ColorsScheme::chorusPrimary, ColorsScheme::chorusSecondary, this->processorRef));
	addAndMakeVisible(*this->chorusSliders[static_cast<int>(ChorusIndex::FEEDBACK)]);
	
	this->chorusSliders.emplace_back(std::make_unique<CustomSlider>("chorus.highcut", "HighCut", ColorsScheme::chorusPrimary, ColorsScheme::chorusSecondary, this->processorRef));
	addAndMakeVisible(*this->chorusSliders[static_cast<int>(ChorusIndex::HIGHCUT)]);
	
	this->chorusSliders.emplace_back(std::make_unique<CustomSlider>("chorus.mix", "Mix", ColorsScheme::chorusPrimary, ColorsScheme::chorusSecondary, this->processorRef));
	addAndMakeVisible(*this->chorusSliders[static_cast<int>(ChorusIndex::MIX)]);

	chorusHandler();
}

void AudioPluginAudioProcessorEditor::chorusHandler() {
	for (auto& slider : this->chorusSliders) {
        slider->onValueChange = [this](float value, juce::String id) {
			auto param = processorRef.getAPVTS().getParameter(id);
			param->setValueNotifyingHost(value);
        };
    }
}

void AudioPluginAudioProcessorEditor::chorusPaint(juce::Graphics& g) {
	g.setColour(juce::Colour::fromRGB(ColorsScheme::chorusBackground[0], ColorsScheme::chorusBackground[1], ColorsScheme::chorusBackground[2]));
	g.fillRoundedRectangle(this->effectArea, this->cornerSizeEffectArea);
	g.drawRoundedRectangle(this->effectArea, this->cornerSizeEffectArea, 5.0f);

	int x = static_cast<int>(this->effectArea.getX());
    int y = static_cast<int>(this->effectArea.getY());
    int width = static_cast<int>(this->effectArea.getWidth());
	int sliderWidth = 100;
    int sliderHeight = 100;
	int textWidth = 150;
	int textHeight = 25;
	int textOffestX = 25;

	int sliderheightOffset = static_cast<int>(sliderHeight * 1.5);
	int sliderWidthOffset = static_cast<int>(sliderWidth * 1.5);
	int startX = x + sliderWidthOffset - textOffestX;
	int startY = y + sliderHeight;

	juce::Rectangle<int> textArea = {startX, startY, textWidth, textHeight};
	
	g.setColour(juce::Colour::fromRGB(ColorsScheme::chorusSecondary[0], ColorsScheme::chorusSecondary[1], ColorsScheme::chorusSecondary[2]));
	g.setFont(25.f);

	textArea.setY(startY - textHeight);
    g.drawText(this->chorusSliders[static_cast<int>(ChorusIndex::DELAY)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setY(startY + sliderheightOffset - textHeight);
    g.drawText(this->chorusSliders[static_cast<int>(ChorusIndex::RATE)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(width / 2 - sliderWidthOffset - textOffestX);
	textArea.setY((getLocalBounds().getHeight() / 2) + (sliderHeight / 2) - textHeight);
    g.drawText(this->chorusSliders[static_cast<int>(ChorusIndex::DEPTH)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX((width / 2) + static_cast<int>(sliderWidth * 0.5) - textOffestX);
    g.drawText(this->chorusSliders[static_cast<int>(ChorusIndex::WIDTH)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(width - sliderWidthOffset - sliderWidth - textOffestX);
	textArea.setY(startY - textHeight);
    g.drawText(this->chorusSliders[static_cast<int>(ChorusIndex::FEEDBACK)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setY(startY + sliderheightOffset - textHeight);
    g.drawText(this->chorusSliders[static_cast<int>(ChorusIndex::HIGHCUT)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(static_cast<int>(this->effectArea.getWidth()) - sliderWidth - textHeight - textOffestX);
	textArea.setY(static_cast<int>(this->effectArea.getHeight()) - textHeight);
	g.drawText(this->chorusSliders[static_cast<int>(ChorusIndex::MIX)]->getName(), textArea, juce::Justification::centred, true);
}

void AudioPluginAudioProcessorEditor::chorusResized() {
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

	this->chorusSliders[static_cast<int>(ChorusIndex::DELAY)]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->chorusSliders[static_cast<int>(ChorusIndex::RATE)]->setBounds(startX, startY + sliderheightOffset, sliderWidth, sliderHeight);

	startX = width / 2 - sliderWidthOffset;
	startY = (getLocalBounds().getHeight() / 2) + (sliderHeight / 2);
	this->chorusSliders[static_cast<int>(ChorusIndex::DEPTH)]->setBounds(startX, startY, sliderWidth, sliderHeight);
	startX = (width / 2) + static_cast<int>(sliderWidth * 0.5);
	this->chorusSliders[static_cast<int>(ChorusIndex::WIDTH)]->setBounds(startX, startY, sliderWidth, sliderHeight);

	startX = width - sliderWidthOffset - sliderWidth;
	startY = y + sliderHeight;
	this->chorusSliders[static_cast<int>(ChorusIndex::FEEDBACK)]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->chorusSliders[static_cast<int>(ChorusIndex::HIGHCUT)]->setBounds(startX, startY + sliderheightOffset, sliderWidth, sliderHeight);

	int sliderOffsetX = 20;
	this->chorusSliders[static_cast<int>(ChorusIndex::MIX)]->setBounds(width - sliderWidth - sliderOffsetX, height, sliderWidth, sliderHeight);

	this->setSlidersVisable(this->chorusSliders, true);
}


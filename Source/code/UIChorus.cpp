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
	
	g.setColour(juce::Colour::fromRGB(ColorsScheme::chorusSecondary[0], ColorsScheme::chorusSecondary[1], ColorsScheme::chorusSecondary[2]));
	g.setFont(25.f);

	textArea.setY(startY - textHeight);
    g.drawText(this->chorusSliders[static_cast<int>(ChorusIndex::DELAY)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setY(startY + (sliderHeight * 1.5) - textHeight);
    g.drawText(this->chorusSliders[static_cast<int>(ChorusIndex::RATE)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(width / 2 - (sliderWidth * 1.5) - textOffestX);
	textArea.setY((getLocalBounds().getHeight() / 2) + (sliderHeight / 2) - textHeight);
    g.drawText(this->chorusSliders[static_cast<int>(ChorusIndex::DEPTH)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(width / 2 + (sliderWidth * 0.5) - textOffestX);
    g.drawText(this->chorusSliders[static_cast<int>(ChorusIndex::WIDTH)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(width - (sliderWidth * 1.5) - sliderWidth - textOffestX);
	textArea.setY(startY - textHeight);
    g.drawText(this->chorusSliders[static_cast<int>(ChorusIndex::FEEDBACK)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setY(startY + (sliderHeight * 1.5) - textHeight);
    g.drawText(this->chorusSliders[static_cast<int>(ChorusIndex::HIGHCUT)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(this->effectArea.getWidth() - sliderWidth - 20 - textOffestX);
	textArea.setY(this->effectArea.getHeight() - textHeight);
	g.drawText(this->chorusSliders[static_cast<int>(ChorusIndex::MIX)]->getName(), textArea, juce::Justification::centred, true);
}

void AudioPluginAudioProcessorEditor::chorusResized() {
    auto x = this->effectArea.getX();
    auto y = this->effectArea.getY();
    auto width = this->effectArea.getWidth();
    auto height = this->effectArea.getHeight();
	int sliderWidth = 100;
    int sliderHeight = 100;

	int startX = x + (sliderWidth * 1.5);
	int startY = y + sliderHeight;
	this->chorusSliders[static_cast<int>(ChorusIndex::DELAY)]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->chorusSliders[static_cast<int>(ChorusIndex::RATE)]->setBounds(startX, startY + (sliderHeight * 1.5), sliderWidth, sliderHeight);

	startX = width / 2 - (sliderWidth * 1.5);
	startY = (getLocalBounds().getHeight() / 2) + (sliderHeight / 2);
	this->chorusSliders[static_cast<int>(ChorusIndex::DEPTH)]->setBounds(startX, startY, sliderWidth, sliderHeight);
	startX = width / 2 + (sliderWidth * 0.5);
	this->chorusSliders[static_cast<int>(ChorusIndex::WIDTH)]->setBounds(startX, startY, sliderWidth, sliderHeight);

	startX = width - (sliderWidth * 1.5) - sliderWidth;
	startY = y + sliderHeight;
	this->chorusSliders[static_cast<int>(ChorusIndex::FEEDBACK)]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->chorusSliders[static_cast<int>(ChorusIndex::HIGHCUT)]->setBounds(startX, startY + (sliderHeight * 1.5), sliderWidth, sliderHeight);

	this->chorusSliders[static_cast<int>(ChorusIndex::MIX)]->setBounds(width - sliderWidth - 20, height, sliderWidth, sliderHeight);

	this->setSlidersVisable(this->chorusSliders, true);
}


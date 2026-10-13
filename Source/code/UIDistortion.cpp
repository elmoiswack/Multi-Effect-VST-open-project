#include "PluginEditor.hpp"
#include "EnumIndexes.hpp"

void AudioPluginAudioProcessorEditor::distortionInit() {
	this->distortionSliders.reserve(6);
	this->distortionSliders.emplace_back(std::make_unique<CustomSlider>("Drive", ColorsScheme::distortionPrimary, ColorsScheme::distortionSecondary, static_cast<int>(DistortionIndex::DRIVE)));
	addAndMakeVisible(*this->distortionSliders[static_cast<int>(DistortionIndex::DRIVE)]);

	this->distortionSliders.emplace_back(std::make_unique<CustomSlider>("Tone", ColorsScheme::distortionPrimary, ColorsScheme::distortionSecondary, static_cast<int>(DistortionIndex::TONE)));
	addAndMakeVisible(*this->distortionSliders[static_cast<int>(DistortionIndex::TONE)]);

	this->distortionSliders.emplace_back(std::make_unique<CustomSlider>("OutputGain", ColorsScheme::distortionPrimary, ColorsScheme::distortionSecondary, static_cast<int>(DistortionIndex::OUTPUTGAIN)));
	addAndMakeVisible(*this->distortionSliders[static_cast<int>(DistortionIndex::OUTPUTGAIN)]);

	this->distortionSliders.emplace_back(std::make_unique<CustomSlider>("Highcut", ColorsScheme::distortionPrimary, ColorsScheme::distortionSecondary, static_cast<int>(DistortionIndex::HIGHCUT)));
	addAndMakeVisible(*this->distortionSliders[static_cast<int>(DistortionIndex::HIGHCUT)]);

	this->distortionSliders.emplace_back(std::make_unique<CustomSlider>("Lowcut", ColorsScheme::distortionPrimary, ColorsScheme::distortionSecondary, static_cast<int>(DistortionIndex::LOWCUT)));
	addAndMakeVisible(*this->distortionSliders[static_cast<int>(DistortionIndex::LOWCUT)]);

	this->distortionSliders.emplace_back(std::make_unique<CustomSlider>("Mix", ColorsScheme::distortionPrimary, ColorsScheme::distortionSecondary, static_cast<int>(DistortionIndex::MIX)));
	addAndMakeVisible(*this->distortionSliders[static_cast<int>(DistortionIndex::MIX)]);

	this->distortionLAFCB.setColors(ColorsScheme::distortionPrimary, ColorsScheme::distortionSecondary);
	this->distortionLAFCB.setFontSize(20.0f);
	this->distortionLAFCB.setCornerRadius(6.0f);

	this->distortionType.setLookAndFeel(&this->distortionLAFCB);
	addAndMakeVisible(this->distortionType);
	this->distortionType.addItem("Distortion",  1);
	this->distortionType.addItem("Overdrive", 2);
	this->distortionType.addItem("Saturation", 3);
	this->distortionType.addItem("Fuzz", 4);
	this->distortionType.setSelectedId(1);

	distortionHandler();
}

void AudioPluginAudioProcessorEditor::distortionHandler() {
	for (auto& slider : this->distortionSliders) {
        slider->onValueChange = [this](int index, float value) {
			//TODO: update index with value
            repaint();
        };
    }

	this->distortionType.onChange = [this]() {
		int selected = this->distortionType.getSelectedId();
	};
}

void AudioPluginAudioProcessorEditor::distortionPaint(juce::Graphics& g) {
	g.setColour(juce::Colour::fromRGB(ColorsScheme::distortionBackground[0], ColorsScheme::distortionBackground[1], ColorsScheme::distortionBackground[2]));
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
	
	g.setColour(juce::Colour::fromRGB(ColorsScheme::distortionSecondary[0], ColorsScheme::distortionSecondary[1], ColorsScheme::distortionSecondary[2]));
	g.setFont(25.f);

	textArea.setY(startY - textHeight);
    g.drawText(this->distortionSliders[static_cast<int>(DistortionIndex::DRIVE)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setY(startY + (sliderHeight * 1.5) - textHeight);
    g.drawText(this->distortionSliders[static_cast<int>(DistortionIndex::TONE)]->getName(), textArea, juce::Justification::centred, true);

	int boxWidth = 120;
	int boxHeight = 70;
	textArea.setX((width / 2) - (boxWidth / 2) - textOffestX);
	textArea.setY((getLocalBounds().getHeight() / 2) - (boxHeight * 1.5) - textHeight - 10); //remove magic number
    g.drawText("Type", textArea, juce::Justification::centred, true);

	textArea.setX(width / 2 - (sliderWidth / 2) - textOffestX);
	textArea.setY((getLocalBounds().getHeight() / 2) + (sliderHeight / 2) - textHeight);
	g.drawText(this->distortionSliders[static_cast<int>(DistortionIndex::OUTPUTGAIN)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(width - (sliderWidth * 1.5) - sliderWidth - textOffestX);
	textArea.setY(startY - textHeight);
    g.drawText(this->distortionSliders[static_cast<int>(DistortionIndex::HIGHCUT)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setY(startY + (sliderHeight * 1.5) - textHeight);
    g.drawText(this->distortionSliders[static_cast<int>(DistortionIndex::LOWCUT)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(this->effectArea.getWidth() - sliderWidth - 20 - textOffestX);
	textArea.setY(this->effectArea.getHeight() - textHeight);
	g.drawText(this->distortionSliders[static_cast<int>(DistortionIndex::MIX)]->getName(), textArea, juce::Justification::centred, true);
}

void AudioPluginAudioProcessorEditor::distortionResized() {
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

	int startX = x + (sliderWidth * 1.5);
	int startY = y + sliderHeight;
	this->distortionSliders[static_cast<int>(DistortionIndex::DRIVE)]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->distortionSliders[static_cast<int>(DistortionIndex::TONE)]->setBounds(startX, startY + (sliderHeight * 1.5), sliderWidth, sliderHeight);

	startX = width / 2 - (sliderWidth / 2);
	startY = (getLocalBounds().getHeight() / 2) + (sliderHeight / 2);
	this->distortionSliders[static_cast<int>(DistortionIndex::OUTPUTGAIN)]->setBounds(startX, startY, sliderWidth, sliderHeight);

	startX = width - (sliderWidth * 1.5) - sliderWidth;
	startY = y + sliderHeight;
	this->distortionSliders[static_cast<int>(DistortionIndex::HIGHCUT)]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->distortionSliders[static_cast<int>(DistortionIndex::LOWCUT)]->setBounds(startX, startY + (sliderHeight * 1.5), sliderWidth, sliderHeight);

	this->distortionSliders[static_cast<int>(DistortionIndex::MIX)]->setBounds(width - sliderWidth - 20, height, sliderWidth, sliderHeight);

	this->distortionType.setBounds(boxX, boxY, boxWidth, boxHeight);
	this->distortionType.setVisible(true);
	this->setSlidersVisable(this->distortionSliders, true);
}

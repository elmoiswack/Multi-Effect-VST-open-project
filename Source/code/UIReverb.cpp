#include "PluginEditor.hpp"
#include "EnumIndexes.hpp"

void AudioPluginAudioProcessorEditor::reverbInit() {
	this->reverbSliders.reserve(7);
	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("Decay", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, static_cast<int>(ReverbIndex::DECAY)));
	addAndMakeVisible(*this->reverbSliders[static_cast<int>(ReverbIndex::DECAY)]);

	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("PreDelay", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, static_cast<int>(ReverbIndex::PREDELAY)));
	addAndMakeVisible(*this->reverbSliders[static_cast<int>(ReverbIndex::PREDELAY)]);

	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("Tone", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, static_cast<int>(ReverbIndex::TONE)));
	addAndMakeVisible(*this->reverbSliders[static_cast<int>(ReverbIndex::TONE)]);

	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("Size", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, static_cast<int>(ReverbIndex::SIZE)));
	addAndMakeVisible(*this->reverbSliders[static_cast<int>(ReverbIndex::SIZE)]);

	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("HighCut", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, static_cast<int>(ReverbIndex::HIGHCUT)));
	addAndMakeVisible(*this->reverbSliders[static_cast<int>(ReverbIndex::HIGHCUT)]);

	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("LowCut", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, static_cast<int>(ReverbIndex::LOWCUT)));
	addAndMakeVisible(*this->reverbSliders[static_cast<int>(ReverbIndex::LOWCUT)]);

	this->reverbSliders.emplace_back(std::make_unique<CustomSlider>("Mix", ColorsScheme::reverbPrimary, ColorsScheme::reverbSecondary, static_cast<int>(ReverbIndex::MIX)));
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
        slider->onValueChange = [this](int index, float value) {
			juce::String sliderId = this->getReverbId(index);
			std::cout << sliderId << ": " << value << std::endl;

            repaint();
        };
    }

	this->reverbType.onChange = [this]() {
		juce::String comboId = "reverb.type";
		int selected = this->reverbType.getSelectedId();
	};
}

juce::String AudioPluginAudioProcessorEditor::getReverbId(int index) {
	juce::String id = "reverb.";

	switch (index)
	{
	case static_cast<int>(ReverbIndex::DECAY):
		id += "decay";
		break;
	case static_cast<int>(ReverbIndex::PREDELAY):
		id += "predelay";
		break;
	case static_cast<int>(ReverbIndex::TONE):
		id += "tone";
		break;
	case static_cast<int>(ReverbIndex::SIZE):
		id += "size";
		break;
	case static_cast<int>(ReverbIndex::HIGHCUT):
		id += "highcut";
		break;
	case static_cast<int>(ReverbIndex::LOWCUT):
		id += "lowcut";
		break;
	case static_cast<int>(ReverbIndex::MIX):
		id += "mix";
		break;
	default:
		break;
	}

	return id;
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
    g.drawText(this->reverbSliders[static_cast<int>(ReverbIndex::DECAY)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setY(startY + (sliderHeight * 1.5) - textHeight);
    g.drawText(this->reverbSliders[static_cast<int>(ReverbIndex::PREDELAY)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(width / 2 - (sliderWidth * 1.8));
	textArea.setY((getLocalBounds().getHeight() / 2) + (sliderHeight / 2) - textHeight);
    g.drawText(this->reverbSliders[static_cast<int>(ReverbIndex::TONE)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(width / 2 - (sliderWidth * 1.8) + (getLocalBounds().getWidth() / 4));
    g.drawText(this->reverbSliders[static_cast<int>(ReverbIndex::SIZE)]->getName(), textArea, juce::Justification::centred, true);
	
	int boxWidth = 120;
	int boxHeight = 70;
	textArea.setX((getLocalBounds().getWidth() / 2) - (boxWidth / 2));
	textArea.setY((getLocalBounds().getHeight() / 2) - (boxHeight * 1.5) - textHeight - 10); //remove magic number
    g.drawText("Type", textArea, juce::Justification::centred, true);

	textArea.setX(width - (sliderWidth * 1.5) - sliderWidth);
	textArea.setY(startY - textHeight);
    g.drawText(this->reverbSliders[static_cast<int>(ReverbIndex::HIGHCUT)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setY(startY + (sliderHeight * 1.5) - textHeight);
    g.drawText(this->reverbSliders[static_cast<int>(ReverbIndex::LOWCUT)]->getName(), textArea, juce::Justification::centred, true);

	textArea.setX(this->effectArea.getWidth() - sliderWidth - 20);
	textArea.setY(this->effectArea.getHeight() - textHeight);
	g.drawText(this->reverbSliders[static_cast<int>(ReverbIndex::MIX)]->getName(), textArea, juce::Justification::centred, true);
	
}

void AudioPluginAudioProcessorEditor::reverbResized() {
    auto x = this->effectArea.getX();
    auto y = this->effectArea.getY();
    auto width = this->effectArea.getWidth();
    auto height = this->effectArea.getHeight();
	int sliderWidth = 100;
    int sliderHeight = 100;


	int startX = x + (sliderWidth * 1.5);
	int startY = y + sliderHeight;
	this->reverbSliders[static_cast<int>(ReverbIndex::DECAY)]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->reverbSliders[static_cast<int>(ReverbIndex::PREDELAY)]->setBounds(startX, startY + (sliderHeight * 1.5), sliderWidth, sliderHeight);

	startX = width / 2 - (sliderWidth * 1.8);
	startY = (getLocalBounds().getHeight() / 2) + (sliderHeight / 2);
	this->reverbSliders[static_cast<int>(ReverbIndex::TONE)]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->reverbSliders[static_cast<int>(ReverbIndex::SIZE)]->setBounds(startX + (getLocalBounds().getWidth() / 4), startY, sliderWidth, sliderHeight);

	startX = width - (sliderWidth * 1.5) - sliderWidth;
	startY = y + sliderHeight;
	this->reverbSliders[static_cast<int>(ReverbIndex::HIGHCUT)]->setBounds(startX, startY, sliderWidth, sliderHeight);
	this->reverbSliders[static_cast<int>(ReverbIndex::LOWCUT)]->setBounds(startX, startY + (sliderHeight * 1.5), sliderWidth, sliderHeight);

	this->reverbSliders[static_cast<int>(ReverbIndex::MIX)]->setBounds(this->effectArea.getWidth() - sliderWidth - 20, height, sliderWidth, sliderHeight);

	int boxWidth = 120;
	int boxHeight = 70;
	int boxX = (getLocalBounds().getWidth() / 2) - (boxWidth / 2);
	int boxY = (getLocalBounds().getHeight() / 2) - (boxHeight * 1.5); 

	this->reverbType.setBounds(boxX, boxY, boxWidth, boxHeight);
	this->reverbType.setVisible(true);
	this->setSlidersVisable(this->reverbSliders, true);
}
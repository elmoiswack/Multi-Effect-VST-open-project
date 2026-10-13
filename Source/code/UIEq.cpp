#include "PluginEditor.hpp"
#include "EnumIndexes.hpp"

void AudioPluginAudioProcessorEditor::eqInit() {
	this->eqSliders.reserve(9);
	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Frequency", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, static_cast<int>(eqIndex::LOWFREQ)));
	addAndMakeVisible(*this->eqSliders[static_cast<int>(eqIndex::LOWFREQ)]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Gain", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, static_cast<int>(eqIndex::LOWGAIN)));
	addAndMakeVisible(*this->eqSliders[static_cast<int>(eqIndex::LOWGAIN)]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Quality", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, static_cast<int>(eqIndex::LOWQ)));
	addAndMakeVisible(*this->eqSliders[static_cast<int>(eqIndex::LOWQ)]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Frequency", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, static_cast<int>(eqIndex::MIDFREQ)));
	addAndMakeVisible(*this->eqSliders[static_cast<int>(eqIndex::MIDFREQ)]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Gain", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, static_cast<int>(eqIndex::MIDGAIN)));
	addAndMakeVisible(*this->eqSliders[static_cast<int>(eqIndex::MIDGAIN)]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Quality", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, static_cast<int>(eqIndex::MIDQ)));
	addAndMakeVisible(*this->eqSliders[static_cast<int>(eqIndex::MIDQ)]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Frequency", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, static_cast<int>(eqIndex::HIGHFREQ)));
	addAndMakeVisible(*this->eqSliders[static_cast<int>(eqIndex::HIGHFREQ)]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Gain", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, static_cast<int>(eqIndex::HIGHGAIN)));
	addAndMakeVisible(*this->eqSliders[static_cast<int>(eqIndex::HIGHGAIN)]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Quality", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, static_cast<int>(eqIndex::HIGHQ)));
	addAndMakeVisible(*this->eqSliders[static_cast<int>(eqIndex::HIGHQ)]);

	this->eqLAFCB.setColors(ColorsScheme::eqPrimary, ColorsScheme::eqSecondary);
	this->eqLAFCB.setFontSize(14.0f);
	this->eqLAFCB.setCornerRadius(6.0f);

	for (auto* box : { &this->lowSlope, &this->highSlope }) {
		box->setLookAndFeel(&this->eqLAFCB);
		addAndMakeVisible(box);
		box->addItem("6 dB",  1);
		box->addItem("12 dB", 2);
		box->addItem("24 dB", 3);
		box->addItem("36 dB", 4);
		box->setSelectedId(1);
	}

	eqHandler();
}

void AudioPluginAudioProcessorEditor::eqHandler() {
  	for (auto& slider : eqSliders) {
        slider->onValueChange = [this](int index, float value) {
			//TODO: update index with value
            repaint();
        };
    }

	this->lowSlope.onChange = [this]() {
		int selected = this->lowSlope.getSelectedId();
	};

	this->highSlope.onChange = [this]() {
		int selected = this->lowSlope.getSelectedId();
	};
}

void AudioPluginAudioProcessorEditor::eqPaint(juce::Graphics& g) {
	g.setColour(juce::Colour::fromRGB(ColorsScheme::eqBackground[0], ColorsScheme::eqBackground[1], ColorsScheme::eqBackground[2]));
	g.fillRoundedRectangle(this->effectArea, this->cornerSizeEffectArea);
	g.drawRoundedRectangle(this->effectArea, this->cornerSizeEffectArea, 5.0f);

	juce::Rectangle<float> waveformRect = {(float)getLocalBounds().getWidth() / 8, this->effectArea.getY() + 20.f, (float)getLocalBounds().getWidth() / 8 * 6, 120};
	g.setColour(juce::Colour::fromRGB(ColorsScheme::eqPrimary[0], ColorsScheme::eqPrimary[1], ColorsScheme::eqPrimary[2]));
	g.fillRoundedRectangle(waveformRect, this->cornerSizeEffectArea);
	g.drawRoundedRectangle(waveformRect, this->cornerSizeEffectArea, 5.0f);

	//TODO: create path from incoming data to represent waveform

	auto x = this->effectArea.getX();
	auto y = this->effectArea.getY();
	auto width = this->effectArea.getWidth();
	auto height = this->effectArea.getHeight();
	
	int sliderWidth = 90;
	
	int startX = x + (width / 4) - sliderWidth;
	int startY = y + (height / 2.5f) - 20.f;
    int xOffset = width / 4 + sliderWidth / 2;
	int yOffset = 110.f;
	int textWidth = 100;
	int textHeight = 20;
	
	juce::Rectangle<int> textArea = {startX, startY, textWidth, textHeight};

	g.setColour(juce::Colour::fromRGB(ColorsScheme::eqSecondary[0], ColorsScheme::eqSecondary[1], ColorsScheme::eqSecondary[2]));
	g.setFont(20.f);
	for (std::size_t i = 0; i < this->eqSliders.size(); ++i) {
        int column = i / 3;
        int row = i % 3;

		textArea.setX(startX + (column * xOffset));
		textArea.setY(startY + (row * yOffset));
        g.drawText(this->eqSliders[i]->getName(), textArea, juce::Justification::centred, true);
    }
}

void AudioPluginAudioProcessorEditor::eqResized() {
    auto x = this->effectArea.getX();
    auto y = this->effectArea.getY();
    auto width = this->effectArea.getWidth();
    auto height = this->effectArea.getHeight();

    int sliderWidth = 80;
    int sliderHeight = 80;

    int startX = x + (width / 4) - sliderWidth;
    int startY = y + (height / 2.5f);
    int xOffset = width / 4 + sliderWidth / 2;
    int yOffset = 110;

    for (std::size_t i = 0; i < this->eqSliders.size(); ++i) {
        int column = i / 3;
        int row = i % 3;

        this->eqSliders[i]->setBounds(
            startX + (column * xOffset),
            startY + (row * yOffset),
            sliderWidth,
            sliderHeight
        );
        this->eqSliders[i]->setVisible(true);
    }

	int boxWidth = 70;
	int boxHeight = 50;

	this->lowSlope.setBounds(startX - boxWidth - 20, (startY + ((1 % 3) * yOffset)) + (sliderHeight / 4), boxWidth, boxHeight);
	this->lowSlope.setVisible(true);
	this->highSlope.setBounds((startX + (xOffset * 2)) + boxWidth + 20, (startY + ((1 % 3) * yOffset)) + (sliderHeight / 4), boxWidth, boxHeight);
	this->highSlope.setVisible(true);

}


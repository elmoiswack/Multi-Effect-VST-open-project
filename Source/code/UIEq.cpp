#include "PluginEditor.hpp"
#include "EnumIndexes.hpp"

void AudioPluginAudioProcessorEditor::eqInit() {
	this->eqSliders.reserve(9);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("eq.low.frequency", "Frequency", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, this->processorRef));
	addAndMakeVisible(*this->eqSliders[static_cast<int>(eqIndex::LOWFREQ)]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("eq.low.gain", "Gain", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, this->processorRef));
	addAndMakeVisible(*this->eqSliders[static_cast<int>(eqIndex::LOWGAIN)]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("eq.low.quality", "Quality", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, this->processorRef));
	addAndMakeVisible(*this->eqSliders[static_cast<int>(eqIndex::LOWQ)]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("eq.mid.frequency", "Frequency", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, this->processorRef));
	addAndMakeVisible(*this->eqSliders[static_cast<int>(eqIndex::MIDFREQ)]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("eq.mid.gain", "Gain", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, this->processorRef));
	addAndMakeVisible(*this->eqSliders[static_cast<int>(eqIndex::MIDGAIN)]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("eq.mid.quality", "Quality", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, this->processorRef));
	addAndMakeVisible(*this->eqSliders[static_cast<int>(eqIndex::MIDQ)]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("eq.high.frequency", "Frequency", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, this->processorRef));
	addAndMakeVisible(*this->eqSliders[static_cast<int>(eqIndex::HIGHFREQ)]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("eq.high.gain", "Gain", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, this->processorRef));
	addAndMakeVisible(*this->eqSliders[static_cast<int>(eqIndex::HIGHGAIN)]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("eq.high.quality", "Quality", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, this->processorRef));
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
        slider->onValueChange = [this](float value, juce::String id) {
			auto param = processorRef.getAPVTS().getParameter(id);
			param->setValueNotifyingHost(value);
        };
    }

	this->lowSlope.onChange = [this]() {
		auto param = processorRef.getAPVTS().getParameter("eq.low.slope");
		param->setValueNotifyingHost(this->lowSlope.getSelectedId());
	};

	this->highSlope.onChange = [this]() {
		auto param = processorRef.getAPVTS().getParameter("eq.high.slope");
		param->setValueNotifyingHost(this->highSlope.getSelectedId());
	};
}



juce::Path AudioPluginAudioProcessorEditor::eqComputeWaveform() {
	juce::Path pathToDraw; 

	//get audio inputchannels from processor
	std::vector<std::complex<double>> result = {};
	int numChannels = 2; //get from audio inputchannels

	for (int i = 0; i < numChannels; i++) {
		//call fft function
	
	}

	return pathToDraw;
}

void AudioPluginAudioProcessorEditor::eqPaint(juce::Graphics& g) {
	g.setColour(juce::Colour::fromRGB(ColorsScheme::eqBackground[0], ColorsScheme::eqBackground[1], ColorsScheme::eqBackground[2]));
	g.fillRoundedRectangle(this->effectArea, this->cornerSizeEffectArea);
	g.drawRoundedRectangle(this->effectArea, this->cornerSizeEffectArea, 5.0f);

	juce::Rectangle<float> waveformRect = {(float)getLocalBounds().getWidth() / 8, this->effectArea.getY() + 20.f, (float)getLocalBounds().getWidth() / 8 * 6, 120};
	g.setColour(juce::Colour::fromRGB(ColorsScheme::eqSecondary[0], ColorsScheme::eqSecondary[1], ColorsScheme::eqSecondary[2]));
	g.fillRoundedRectangle(waveformRect, this->cornerSizeEffectArea);
	g.drawRoundedRectangle(waveformRect, this->cornerSizeEffectArea, 5.0f);

	//TODO: create path from incoming data to represent waveform

	int x = static_cast<int>(this->effectArea.getX());
	int y = static_cast<int>(this->effectArea.getY());
	int width = static_cast<int>(this->effectArea.getWidth());
	int height = static_cast<int>(this->effectArea.getHeight());
	
	int sliderWidth = 90;
	
	int startX = x + (width / 4) - sliderWidth;
	int startOffsetY = 20;
	int startY = y + static_cast<int>(height / 2.5) - startOffsetY;
    int startOffsetX = width / 4 + sliderWidth / 2;
	startOffsetY = 110;
	int textWidth = 100;
	int textHeight = 25;
	
	juce::Rectangle<int> textArea = {startX, startY, textWidth, textHeight};

	g.setColour(juce::Colour::fromRGB(ColorsScheme::eqSecondary[0], ColorsScheme::eqSecondary[1], ColorsScheme::eqSecondary[2]));
	g.setFont(20.f);
	for (std::size_t i = 0; i < this->eqSliders.size(); ++i) {
        int column = static_cast<int>(i) / 3;
        int row = static_cast<int>(i) % 3;

		textArea.setX(startX + (column * startOffsetX));
		textArea.setY(startY + (row * startOffsetY));
        g.drawText(this->eqSliders[i]->getName(), textArea, juce::Justification::centred, true);
    }
}

void AudioPluginAudioProcessorEditor::eqResized() {
    int x = static_cast<int>(this->effectArea.getX());
    int y = static_cast<int>(this->effectArea.getY());
    int width = static_cast<int>(this->effectArea.getWidth());
    int height = static_cast<int>(this->effectArea.getHeight());

    int sliderWidth = 80;
    int sliderHeight = 80;

    int startX = x + (width / 4) - sliderWidth;
    int startY = y + static_cast<int>(height / 2.5);
    int startOffsetX = width / 4 + sliderWidth / 2;
    int startOffsetY = 110;

    for (std::size_t i = 0; i < this->eqSliders.size(); ++i) {
        int column = static_cast<int>(i) / 3;
        int row = static_cast<int>(i) % 3;

        this->eqSliders[i]->setBounds(
            startX + (column * startOffsetX),
            startY + (row * startOffsetY),
            sliderWidth,
            sliderHeight
        );
        this->eqSliders[i]->setVisible(true);
    }

	int boxWidth = 70;
	int boxHeight = 50;
	int boxOffsetX = 20;
	int boxY = (startY + static_cast<int>((1 % 3) * startOffsetY)) + (sliderHeight / 4);

	this->lowSlope.setBounds(startX - boxWidth - boxOffsetX, boxY, boxWidth, boxHeight);
	this->lowSlope.setVisible(true);
	this->highSlope.setBounds(startX + (startOffsetX * 2) + boxWidth + boxOffsetX, boxY, boxWidth, boxHeight);
	this->highSlope.setVisible(true);

}


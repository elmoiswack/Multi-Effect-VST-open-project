#include "PluginEditor.hpp"

enum eqIndex {
	LOWFREQ,
	LOWGAIN,
	LOWQ,
	MIDFREQ,
	MIDGAIN,
	MIDQ,
	HIGHFREQ,
	HIGHGAIN,
	HIGHQ,	
};

AudioPluginAudioProcessorEditor::CustomLAFCombo::CustomLAFCombo() {
	setColors();
}

void AudioPluginAudioProcessorEditor::CustomLAFCombo::positionComboBoxText(juce::ComboBox& box, juce::Label& label) {
    label.setBounds(1, 1, box.getWidth() - 20, box.getHeight() - 2);
    label.setFont(getComboBoxFont(box));
    label.setJustificationType(juce::Justification::centred);
}

void AudioPluginAudioProcessorEditor::CustomLAFCombo::drawComboBox(juce::Graphics& g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox& box) {
    auto bounds = juce::Rectangle<float>(0.0f, 0.0f, (float) width, (float) height);

    g.setColour(box.findColour(juce::ComboBox::backgroundColourId));
    g.fillRoundedRectangle(bounds, cornerRadius);

    g.setColour(box.findColour(box.hasKeyboardFocus(true) ? juce::ComboBox::focusedOutlineColourId : juce::ComboBox::outlineColourId));
    g.drawRoundedRectangle(bounds.reduced(0.5f), cornerRadius, 1.0f);

    juce::Rectangle<float> arrowZone((float) buttonX, (float) buttonY, (float) buttonW, (float) buttonH);
    juce::Path arrow;
    arrow.startNewSubPath(arrowZone.getCentreX() - 3.0f, arrowZone.getCentreY() - 2.0f);
    arrow.lineTo(arrowZone.getCentreX(), arrowZone.getCentreY() + 2.0f);
    arrow.lineTo(arrowZone.getCentreX() + 3.0f, arrowZone.getCentreY() - 2.0f);

    g.setColour(box.findColour(juce::ComboBox::arrowColourId).withAlpha(box.isEnabled() ? 1.0f : 0.3f));
    g.strokePath(arrow, juce::PathStrokeType(2.0f));
}

void AudioPluginAudioProcessorEditor::CustomLAFCombo::drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const juce::String& text, const juce::String& shortcutKeyText, const juce::Drawable* icon, const juce::Colour* textColour) {
    juce::Colour grey = juce::Colours::grey;
    juce::LookAndFeel_V4::drawPopupMenuItem(g, area, isSeparator, isActive, isHighlighted, false, hasSubMenu, text, shortcutKeyText, icon, isTicked ? &grey : textColour);
}

juce::Font AudioPluginAudioProcessorEditor::CustomLAFCombo::getComboBoxFont(juce::ComboBox&) {
	return juce::Font(this->fontSize);
}

void AudioPluginAudioProcessorEditor::CustomLAFCombo::setFontSize(float size) { 
	this->fontSize = size; 
}

void AudioPluginAudioProcessorEditor::CustomLAFCombo::setCornerRadius(float radius) { 
	this->cornerRadius = radius; 
}

void AudioPluginAudioProcessorEditor::CustomLAFCombo::setColors() {
    colorPrimary = juce::Colour::fromRGB(ColorsScheme::eqPrimary[0],   ColorsScheme::eqPrimary[1],   ColorsScheme::eqPrimary[2]);
    colorSecondary = juce::Colour::fromRGB(ColorsScheme::eqSecondary[0], ColorsScheme::eqSecondary[1], ColorsScheme::eqSecondary[2]);

    setColour(juce::ComboBox::backgroundColourId, colorSecondary);
    setColour(juce::ComboBox::outlineColourId, colorPrimary);
    setColour(juce::ComboBox::focusedOutlineColourId, colorPrimary);
    setColour(juce::ComboBox::textColourId, juce::Colours::white);
    setColour(juce::ComboBox::arrowColourId, colorPrimary);

    setColour(juce::PopupMenu::backgroundColourId, colorSecondary);
    setColour(juce::PopupMenu::highlightedBackgroundColourId, colorPrimary);
    setColour(juce::PopupMenu::highlightedTextColourId, colorSecondary);
    setColour(juce::PopupMenu::textColourId, juce::Colours::white);
}

void AudioPluginAudioProcessorEditor::eqInit() {
	this->eqSliders.reserve(9);
	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Frequency", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, LOWFREQ));
	addAndMakeVisible(*this->eqSliders[LOWFREQ]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Gain", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, LOWGAIN));
	addAndMakeVisible(*this->eqSliders[LOWGAIN]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Quality", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, LOWQ));
	addAndMakeVisible(*this->eqSliders[LOWQ]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Frequency", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, MIDFREQ));
	addAndMakeVisible(*this->eqSliders[MIDFREQ]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Gain", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, MIDGAIN));
	addAndMakeVisible(*this->eqSliders[MIDGAIN]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Quality", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, MIDQ));
	addAndMakeVisible(*this->eqSliders[MIDQ]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Frequency", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, HIGHFREQ));
	addAndMakeVisible(*this->eqSliders[HIGHFREQ]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Gain", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, HIGHGAIN));
	addAndMakeVisible(*this->eqSliders[HIGHGAIN]);

	this->eqSliders.emplace_back(std::make_unique<CustomSlider>("Quality", ColorsScheme::eqPrimary, ColorsScheme::eqSecondary, HIGHQ));
	addAndMakeVisible(*this->eqSliders[HIGHQ]);

  	for (auto& slider : eqSliders) {
        slider->onValueChange = [this](int index, float value) {
            repaint();
        };
    }

	this->LAFComboBox.setColors();
	this->LAFComboBox.setFontSize(14.0f);
	this->LAFComboBox.setCornerRadius(6.0f);
	for (auto* box : { &lowSlope, &highSlope }) {
		box->setLookAndFeel(&LAFComboBox);
		addAndMakeVisible(box);
		box->addItem("6 dB",  1);
		box->addItem("12 dB", 2);
		box->addItem("24 dB", 3);
		box->addItem("36 dB", 4);
		box->setSelectedId(1);
	}

}

void AudioPluginAudioProcessorEditor::eqPaint(juce::Graphics& g) {
	auto& bgColor = ColorsScheme::eqBackground;

	g.setColour(juce::Colour::fromRGB(bgColor[0], bgColor[1], bgColor[2]));
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
	
	float lowX = x + (width / 4) - sliderWidth;
	float lowY = y + (height / 2.5f) - 20.f;
    float xOffset = width / 4 + sliderWidth / 2;
	float yOffset = 110.f;
	
	juce::Rectangle<float> low = {lowX, lowY, 100.f, 20.f};

	g.setColour(juce::Colour::fromRGB(ColorsScheme::eqSecondary[0], ColorsScheme::eqSecondary[1], ColorsScheme::eqSecondary[2]));	
	for (std::size_t i = 0; i < this->eqSliders.size(); ++i) {
        int column = i / 3;
        int row = i % 3;

		low.setX(lowX + (column * xOffset));
		low.setY(lowY + (row * yOffset));
        g.drawText(this->eqSliders[i]->getName(), low, juce::Justification::centred, true);
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

void AudioPluginAudioProcessorEditor::eqHide() {
	for (std::size_t i = 0; i < this->eqSliders.size(); i++) {
		this->eqSliders[i]->setVisible(false);
	}

	this->lowSlope.setVisible(false);
	this->highSlope.setVisible(false);
}

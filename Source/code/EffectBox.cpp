#include "EffectBox.hpp"

EffectBox::EffectBox() : drawableIcon("xIcon button", juce::DrawableButton::ButtonStyle::ImageFitted), xIcon(nullptr)
{
    effectName = "";
    color[0] = 0;
    color[1] = 0;
    color[2] = 0;
}

EffectBox::EffectBox(juce::String name, const juce::uint8* colorRGB, EffectBoxType typeBox) : drawableIcon("xIcon button", juce::DrawableButton::ButtonStyle::ImageFitted) {
	this->effectName = name;
	this->color[0] = colorRGB[0];
	this->color[1] = colorRGB[1];
	this->color[2] = colorRGB[2];
	this->type = typeBox;

	if (typeBox == EffectBoxType::CHAIN) {
		this->xIcon = juce::Drawable::createFromImageData(
		BinaryData::x_svg,
		BinaryData::x_svgSize);
		this->drawableIcon.setImages(this->xIcon.get());
		addAndMakeVisible(this->drawableIcon);
	}
	else {
		this->xIcon = nullptr;
	}
}

EffectBox::~EffectBox() {

}

EffectBox::EffectBox(EffectBox&& other) noexcept : drawableIcon("xIcon button", juce::DrawableButton::ButtonStyle::ImageFitted) {
    this->effectName = std::move(other.effectName);
	this->xIcon = std::move(other.xIcon);
    this->color[0] = other.color[0];
    this->color[1] = other.color[1];
    this->color[2] = other.color[2];
	this->type = other.type;

    other.effectName = "";
    other.color[0] = 0;
    other.color[1] = 0;
    other.color[2] = 0;
	addAndMakeVisible(this->drawableIcon);
}

EffectBox& EffectBox::operator=(EffectBox&& other) noexcept
{
    if (this != &other) {
    	this->effectName = std::move(other.effectName);
		this->color[0] = other.color[0];
		this->color[1] = other.color[1];
		this->color[2] = other.color[2];
		this->type = other.type;
		this->xIcon = std::move(other.xIcon);
		addAndMakeVisible(this->drawableIcon);
    }
    return *this;
}


void EffectBox::paint(juce::Graphics& g) {
	float cornerSize = 20.f;

	g.setColour(juce::Colour::fromRGB(58, 58, 58));
	g.fillRoundedRectangle(getLocalBounds().toFloat(), cornerSize);
	g.drawRoundedRectangle(getLocalBounds().toFloat(), cornerSize, 5.0f);

	g.setColour(juce::Colour::fromRGB(this->color[0], this->color[1], this->color[2]));
	// juce::FontOptions font("FreeSans", 40.0f, juce::Font::bold);
	// std::cout << font.getTypeface() << std::endl;
	g.setFont(30.f);
	g.drawText(this->effectName, getLocalBounds(), juce::Justification::centred);
}

void EffectBox::resized() {
	auto width = (float)getWidth();
	float svgHeight = 10.0f;
	float svgWidth = 10.0f;

	if (this->type == EffectBoxType::CHAIN) {
		this->drawableIcon.setBounds(width - (svgWidth * 2), svgHeight, svgWidth, svgHeight);
	}
}


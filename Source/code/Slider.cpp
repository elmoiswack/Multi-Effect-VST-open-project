#include "Slider.hpp"

Slider::Slider() {
	this->primaryColor[0] = 0;
	this->primaryColor[1] = 0;
	this->primaryColor[2] = 0;

	this->secondaryColor[0] = 0;
	this->secondaryColor[1] = 0;
	this->secondaryColor[2] = 0;

	this->rotaryStartAngle = 0.f;
	this->sliderPos = 0.f;
	this->rotaryEndAngle = 0.f;
}

Slider::Slider(juce::String sliderName, const juce::uint8* primary, const juce::uint8* secondary) {
	this->name = sliderName;

	this->primaryColor[0] = primary[0];
	this->primaryColor[1] = primary[1];
	this->primaryColor[2] = primary[2];

	this->secondaryColor[0] = secondary[0];
	this->secondaryColor[1] = secondary[1];
	this->secondaryColor[2] = secondary[2];

	this->rotaryStartAngle = 20.f;
	this->sliderPos = 10.f;
	this->rotaryEndAngle = 80.f;
}

Slider::Slider(Slider&& other) noexcept {
    this->name = other.name;

    this->primaryColor[0] = other.primaryColor[0];
    this->primaryColor[1] = other.primaryColor[1];
    this->primaryColor[2] = other.primaryColor[2];
    this->secondaryColor[0] = other.secondaryColor[0];
    this->secondaryColor[1] = other.secondaryColor[1];
    this->secondaryColor[2] = other.secondaryColor[2];

	this->rotaryStartAngle = other.rotaryStartAngle;
	this->rotaryEndAngle = other.rotaryEndAngle;
	this->sliderPos = other.sliderPos;
}

Slider& Slider::operator=(Slider&& other) noexcept {
    if (this != &other)
    {
        this->name = other.name;

		this->primaryColor[0] = other.primaryColor[0];
		this->primaryColor[1] = other.primaryColor[1];
		this->primaryColor[2] = other.primaryColor[2];
		this->secondaryColor[0] = other.secondaryColor[0];
		this->secondaryColor[1] = other.secondaryColor[1];
		this->secondaryColor[2] = other.secondaryColor[2];

		this->rotaryStartAngle = other.rotaryStartAngle;
		this->rotaryEndAngle = other.rotaryEndAngle;
		this->sliderPos = other.sliderPos;
    }

    return *this;
}

Slider::~Slider()
{
}

void Slider::paint (juce::Graphics& g) {
	float width = (float)getLocalBounds().getWidth();
	float height = (float)getLocalBounds().getHeight();

	float x = 0.f;
	float y = 0.f;


	auto radius = (float) juce::jmin(width / 2, height / 2) - 4.0f;
	auto centreX = x + width * 0.5f;
	auto centreY = y + height * 0.5f;
	auto rx = centreX - radius;
	auto ry = centreY - radius;
	auto rw = radius * 2.0f;
	auto angle = this->rotaryStartAngle + this->sliderPos * (this->rotaryEndAngle - this->rotaryStartAngle);

	g.setColour(juce::Colour::fromRGB(this->primaryColor[0], this->primaryColor[1], this->primaryColor[2]));
	g.fillEllipse(rx, ry, rw, rw);
	g.setColour(juce::Colour::fromRGB(this->secondaryColor[0], this->secondaryColor[1], this->secondaryColor[2]));
	g.drawEllipse(rx, ry, rw, rw, 1.0f);

	juce::Path p;
	auto pointerLength = radius * 0.5f;
	auto pointerThickness = 4.0f;
	p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
	p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));
	g.setColour(juce::Colour::fromRGB(this->secondaryColor[0], this->secondaryColor[1], this->secondaryColor[2]));
	g.fillPath(p);
}

void Slider::resized() {
}

void Slider::setRotaryStart(float value) {
	this->rotaryStartAngle = value;
}

void Slider::setRotaryEnd(float value) {
	this->rotaryEndAngle = value;
}

void Slider::setSliderPos(float value) {
	this->sliderPos = value;
}

juce::String Slider::getName() {
	return this->name;
}
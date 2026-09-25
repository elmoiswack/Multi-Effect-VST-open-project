#include "CustomSlider.hpp"

CustomSlider::CustomSlider() {
	this->primaryColor[0] = 0;
	this->primaryColor[1] = 0;
	this->primaryColor[2] = 0;

	this->secondaryColor[0] = 0;
	this->secondaryColor[1] = 0;
	this->secondaryColor[2] = 0;

	this->sliderPos = 0.f;
	this->index = 0;
}

CustomSlider::CustomSlider(juce::String sliderName, const juce::uint8* primary, const juce::uint8* secondary, int indexValue) {
	this->name = sliderName;

	this->primaryColor[0] = primary[0];
	this->primaryColor[1] = primary[1];
	this->primaryColor[2] = primary[2];

	this->secondaryColor[0] = secondary[0];
	this->secondaryColor[1] = secondary[1];
	this->secondaryColor[2] = secondary[2];

	this->sliderPos = 0.f;
	this->index = indexValue;
}

CustomSlider::~CustomSlider() {}

void CustomSlider::paint(juce::Graphics& g) {
    float width  = static_cast<float>(getLocalBounds().getWidth());
    float height = static_cast<float>(getLocalBounds().getHeight());
    float rotaryStartAngle = juce::degreesToRadians(-135.0f);
    float rotaryEndAngle   = juce::degreesToRadians(135.0f);

    float radius = juce::jmin(width / 2.0f, height / 2.0f) - 4.0f;
    float centreX = width * 0.5f;
    float centreY = height * 0.5f;
    float rx = centreX - radius;
    float ry = centreY - radius;
    float rw = radius * 2.0f;

    float normalizedPosition = this->sliderPos / 20.0f;
    float angle = rotaryStartAngle + normalizedPosition *(rotaryEndAngle - rotaryStartAngle);

    g.setColour(juce::Colour::fromRGB(this->primaryColor[0], this->primaryColor[1], this->primaryColor[2]));
    g.fillEllipse(rx, ry, rw, rw);
    g.setColour(juce::Colour::fromRGB(this->secondaryColor[0], this->secondaryColor[1], this->secondaryColor[2]));
    g.drawEllipse(rx, ry, rw, rw, 1.0f);

    juce::Path p;
    float pointerLength  = radius * 0.5f;
    float pointerThickness = 4.0f;
    p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness,pointerLength);
    p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));
    g.setColour(juce::Colour::fromRGB(this->secondaryColor[0], this->secondaryColor[1], this->secondaryColor[2]));
    g.fillPath(p);
}


void CustomSlider::resized() {}

void CustomSlider::mouseDrag(const juce::MouseEvent& event) {
	if (moveSlider) {
		moveSlider(event, this->index);
	}
}

void CustomSlider::setSliderPos(float value) {
	this->sliderPos = juce::jlimit(0.f, 20.f, (value / 20.f));
	repaint();
}

juce::String CustomSlider::getName() {
	return this->name;
}
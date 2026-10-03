#include "CustomSlider.hpp"

CustomSlider::CustomSlider() {
	this->index = 0;
	this->primaryColor[0] = 0;
	this->primaryColor[1] = 0;
	this->primaryColor[2] = 0;

	this->secondaryColor[0] = 0;
	this->secondaryColor[1] = 0;
	this->secondaryColor[2] = 0;

	this->normalisedValue = 0.f;
    this->dragStartValue = 0.f;
}

CustomSlider::CustomSlider(juce::String sliderName, const juce::uint8* primary, const juce::uint8* secondary, int indexValue) {
	this->name = sliderName;
	this->index = indexValue;

	this->primaryColor[0] = primary[0];
	this->primaryColor[1] = primary[1];
	this->primaryColor[2] = primary[2];

	this->secondaryColor[0] = secondary[0];
	this->secondaryColor[1] = secondary[1];
	this->secondaryColor[2] = secondary[2];

	this->normalisedValue = 0.f;
    this->dragStartValue = 0.f;
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
    float angle = rotaryStartAngle + this->normalisedValue *(rotaryEndAngle - rotaryStartAngle);

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

void CustomSlider::mouseDown(const juce::MouseEvent&) {
    this->dragStartValue = this->normalisedValue;
}

void CustomSlider::mouseDrag(const juce::MouseEvent& event) {
    float pixelsForFullRange = 400.0f;
    float delta = (float) (event.getDistanceFromDragStartX() - event.getDistanceFromDragStartY());

	this->setValue(this->dragStartValue + delta / pixelsForFullRange);
}

void CustomSlider::setValue(float newValue) {
    newValue = juce::jlimit(0.0f, 1.0f, newValue);
    if (newValue == this->normalisedValue)
        return;

    this->normalisedValue = newValue;
    repaint();

    if (onValueChange)
        onValueChange(this->index, this->normalisedValue);
}

juce::String CustomSlider::getName() {
	return this->name;
}
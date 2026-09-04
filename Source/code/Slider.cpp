#include "Slider.hpp"

Slider::Slider()
{

}

Slider::~Slider()
{
}

void Slider::paint (juce::Graphics& g) {
	float width = (float)getLocalBounds().getWidth();
	float height = (float)getLocalBounds().getHeight();

	float x = 0.f;
	float y = 0.f;
	float rotaryStartAngle = 20.f;
	float sliderPos = 10.f;
	float rotaryEndAngle = 80.f;

	auto radius = (float) juce::jmin(width / 2, height / 2) - 4.0f;
	auto centreX = x + width * 0.5f;
	auto centreY = y + height * 0.5f;
	auto rx = centreX - radius;
	auto ry = centreY - radius;
	auto rw = radius * 2.0f;
	auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

	g.setColour(juce::Colour::fromRGB(255, 255, 200));
	g.fillEllipse(rx, ry, rw, rw);
	// g.setColour(juce::Colours::red);
	// g.drawEllipse(rx, ry, rw, rw, 1.0f);

	juce::Path p;
	auto pointerLength = radius * 0.5f;
	auto pointerThickness = 6.0f;
	p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
	p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));
	g.setColour(juce::Colours::orange);
	g.fillPath(p);
}

void Slider::resized() {
}
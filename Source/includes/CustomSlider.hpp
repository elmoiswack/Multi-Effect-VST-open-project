#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class CustomSlider : public juce::Component
{
private:
	juce::String name;
	int index;
	juce::uint8 primaryColor[3];
	juce::uint8 secondaryColor[3];

	float normalisedValue = 0.f;
    float dragStartValue = 0.f;

public:
	CustomSlider();
	CustomSlider(juce::String sliderName, const juce::uint8* primary, const juce::uint8* secondary, int indexValue);
	~CustomSlider() override; 

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setValue(float newValue);
    float getValue() const;

	juce::String getName();

	void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;
	std::function<void(int index, float value)> onValueChange;
};


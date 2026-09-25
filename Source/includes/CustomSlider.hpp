#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

class CustomSlider : public juce::Component
{
private:
	juce::String name;
	int index;
	juce::uint8 primaryColor[3];
	juce::uint8 secondaryColor[3];

	float sliderPos;

public:
	CustomSlider();
	// Slider(Slider&& other) noexcept;
	// Slider& operator=(Slider&& other) noexcept;
	CustomSlider(juce::String sliderName, const juce::uint8* primary, const juce::uint8* secondary, int indexValue);
	~CustomSlider() override; 

    void paint(juce::Graphics& g) override;
    void resized() override;

	void setSliderPos(float value);

	juce::String getName();

	void mouseDrag(const juce::MouseEvent& event) override;
	std::function<void(const juce::MouseEvent&, int)> moveSlider;
};


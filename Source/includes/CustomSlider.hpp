#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include "PluginProcessor.hpp"

class CustomSlider : public juce::Component
{
private:
	juce::String paramId;
	juce::String name;
	int index;
	juce::uint8 primaryColor[3];
	juce::uint8 secondaryColor[3];

	float normalisedValue = 0.f;
    float dragStartValue = 0.f;

public:
	CustomSlider();
	CustomSlider(juce::String sliderParamId, juce::String sliderName, const juce::uint8* primary, const juce::uint8* secondary, AudioPluginAudioProcessor& pRef);
	~CustomSlider() override; 

    void paint(juce::Graphics& g) override;
    void resized() override;

    void setValue(float newValue);
    float getValue() const;

	juce::String getParamId();
	juce::String getName();

	void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const juce::MouseEvent& event) override;
	std::function<void(float value, juce::String id)> onValueChange;
};


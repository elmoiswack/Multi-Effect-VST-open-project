#pragma once

#include <juce_dsp/juce_dsp.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_utils/juce_audio_utils.h>
#include <memory>

class Parameters
{
private:
	juce::AudioProcessorValueTreeState apvts;
public:
	explicit Parameters(juce::AudioProcessor& processorRef);
	~Parameters();

	juce::AudioProcessorValueTreeState::ParameterLayout initApvts();
	juce::AudioProcessorValueTreeState& getApvts();

	void initReverb(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
	void initDistoriton(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
	void initDelay(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
	void initChorus(juce::AudioProcessorValueTreeState::ParameterLayout& layout);
	void initEQ(juce::AudioProcessorValueTreeState::ParameterLayout& layout);

	JUCE_DECLARE_NON_COPYABLE(Parameters)
	JUCE_DECLARE_NON_MOVEABLE(Parameters)
};

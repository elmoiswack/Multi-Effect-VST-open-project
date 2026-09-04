#pragma once

#include "PluginProcessor.hpp"
#include "Slider.hpp"
#include "EffectBox.hpp"
#include <vector>

enum EffectIndex {
    REVERB,
    DISTORTION,
    DELAY,
    CHORUS,
    EQ
};

//==============================================================================
class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    void initEffectBoxes();

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;

    std::vector<EffectBox> selectEffectBox;
    std::vector<EffectBox> chainEffectBox;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
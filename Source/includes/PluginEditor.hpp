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

struct ColorsScheme {
    inline static constexpr juce::uint8 reverbPrimary[3] = {255, 255, 100};
    inline static constexpr juce::uint8 distortionPrimary[3] = {158, 27, 0};
    inline static constexpr juce::uint8 delayPrimary[3] = {11, 150, 71};
    inline static constexpr juce::uint8 chorusPrimary[3] = {101, 6, 126};
    inline static constexpr juce::uint8 eqPrimary[3] = {255, 255, 255};
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
    std::vector<EffectBox> activeChain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
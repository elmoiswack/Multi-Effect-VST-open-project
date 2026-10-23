#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include "Parameters.hpp"

enum class ProcessingIndex {
    REVERB,
    DISTORTION,
    DELAY,
    CHORUS,
    EQ,
    NONE
};

struct EQBiquadParameters {
    float b0 = 1.0f, b1 = 0.0f, b2 = 0.0f;
    float a1 = 0.0f, a2 = 0.0f;
};

struct EQBiquadState {
    float s1 = 0.0f, s2 = 0.0f;
};

static constexpr int maxChannels = 2;
static constexpr int maxSlopes = 4; 

//==============================================================================
class AudioPluginAudioProcessor final : public juce::AudioProcessor
{
public:
    //==============================================================================
    AudioPluginAudioProcessor();
    ~AudioPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    juce::AudioProcessorValueTreeState&  getAPVTS();

    void initActiveChain();

/////////////////////EQ Functions////////////////
    void computeLowCutCoefficients(EQBiquadParameters& params, float lowFreq);
    void computeHighCutCoefficients(EQBiquadParameters& params, float highFreq);
    void updateEQCoefficients();
    float calculateOutput(float x, const EQBiquadParameters& parameters, EQBiquadState& state);
    void useEQ(float* buffer, int numSamples, int channel);
    void resetEQState();


private:
    //==============================================================================
    Parameters params{ *this };
    double sampleRate;
    std::array<ProcessingIndex, 5> activeChain;

/////////////////////EQ Params///////////////////
    EQBiquadParameters lowCutParameters;
    EQBiquadParameters highCutParameters;
    EQBiquadState  lowCutState[maxChannels][maxSlopes];
    EQBiquadState  highCutState[maxChannels][maxSlopes];
    int lowCutSlopes  = 1;
    int highCutSlopes = 1;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessor)
};
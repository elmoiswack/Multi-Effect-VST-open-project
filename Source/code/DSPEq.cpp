#include "PluginProcessor.hpp"
#include <cmath>

void AudioPluginAudioProcessor::computeLowCutCoefficients(EQBiquadParameters& params, float lowFreq) {
	float w0 = 2 * M_PI * (lowFreq / this->sampleRate);
	float cosw  = std::cos(w0);
	float alpha = std::sin(w0) / (2 * (1 / std::sqrt(2)));
	float a0 = 1 + alpha;

	params.a1 = (-2 * cosw) / a0;
	params.a2 = (1 - alpha) / a0;
	params.b0 = ((1 + cosw) / 2) / a0;
	params.b1 = -(1 + cosw) / a0;
	params.b2 = ((1 + cosw) / 2) / a0;
}

void AudioPluginAudioProcessor::computeHighCutCoefficients(EQBiquadParameters& params, float highFreq) {
	float w0 = 2 * M_PI * (highFreq / this->sampleRate);
	float cosw  = std::cos(w0);
	float alpha = std::sin(w0) / (2 * (1 / std::sqrt(2)));
	float a0 = 1 + alpha;

	params.a1 = (-2 * cosw) / a0;
	params.a2 = (1 - alpha) / a0;
	params.b0 = ((1 - cosw) / 2) / a0;
	params.b1 = (1 - cosw) / a0;
	params.b2 = ((1 - cosw) / 2) / a0;
}

void AudioPluginAudioProcessor::updateEQCoefficients() {
    auto& apvts = getAPVTS();

    float lowFreq  = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("eq.low.frequency"))->get();
    float highFreq = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("eq.high.frequency"))->get();

    int lowIdx  = dynamic_cast<juce::AudioParameterChoice*>(apvts.getParameter("eq.low.slope"))->getIndex();
    int highIdx = dynamic_cast<juce::AudioParameterChoice*>(apvts.getParameter("eq.high.slope"))->getIndex();

    lowCutSlopes  = juce::jlimit(1, maxSlopes, lowIdx + 1);
    highCutSlopes = juce::jlimit(1, maxSlopes, highIdx + 1);

	this->computeLowCutCoefficients(this->lowCutParameters, this->sampleRate);
	this->computeHighCutCoefficients(this->highCutParameters, this->sampleRate);
}


float AudioPluginAudioProcessor::calculateOutput(float x, const EQBiquadParameters& parameters, EQBiquadState& state) {
    float y = parameters.b0 * x + state.s1;
    state.s1 = parameters.b1 * x - parameters.a1 * y + state.s2;
    state.s2 = parameters.b2 * x - parameters.a2 * y;
    return y;
}

void AudioPluginAudioProcessor::useEQ(float* buffer, int numSamples, int channel) {
    if (channel >= maxChannels)
        return;

    for (int i = 0; i < numSamples; ++i) {
        float x = buffer[i];

        for (int s = 0; s < lowCutSlopes; ++s)
            x = calculateOutput(x, lowCutParameters, lowCutState[channel][s]);

        for (int s = 0; s < highCutSlopes; ++s)
            x = calculateOutput(x, highCutParameters, highCutState[channel][s]);

        buffer[i] = x;
    }
}

void AudioPluginAudioProcessor::resetEQState() {
    for (int ch = 0; ch < maxChannels; ++ch)
        for (int s = 0; s < maxSlopes; ++s) {
            lowCutState [ch][s] = EQBiquadState{};
            highCutState[ch][s] = EQBiquadState{};
        }
}
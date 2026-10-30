#include "PluginProcessor.hpp"
#include <cmath>

void AudioPluginAudioProcessor::computeLowCutCoefficients(BiquadParameters& params, float lowFreq) {
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

void AudioPluginAudioProcessor::computeHighCutCoefficients(BiquadParameters& params, float highFreq) {
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
    auto& apvts = this->getAPVTS();

    float lowFreq  = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("eq.low.frequency"))->get();
    float highFreq = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("eq.high.frequency"))->get();

	this->computeLowCutCoefficients(this->lowCutParameters, lowFreq);
	this->computeHighCutCoefficients(this->highCutParameters, highFreq);

    int lowIdx  = dynamic_cast<juce::AudioParameterChoice*>(apvts.getParameter("eq.low.slope"))->getIndex();
    int highIdx = dynamic_cast<juce::AudioParameterChoice*>(apvts.getParameter("eq.high.slope"))->getIndex();

    this->lowCutSlopes  = juce::jlimit(1, maxSlopes, lowIdx + 1);
    this->highCutSlopes = juce::jlimit(1, maxSlopes, highIdx + 1);

}

float AudioPluginAudioProcessor::calculateOutput(float x, BiquadParameters& parameters, BiquadState& state) {
    float y = parameters.b0 * x + state.s1;
    state.s1 = parameters.b1 * x - parameters.a1 * y + state.s2;
    state.s2 = parameters.b2 * x - parameters.a2 * y;
    return y;
}

void AudioPluginAudioProcessor::useEQ(float* buffer, int numSamples, int channel) {
    if (channel >= maxChannels)
        return;

    for (int i = 0; i < numSamples; i++) {
        float x = buffer[i];

        for (int index = 0; index < lowCutSlopes; index++)
            x = calculateOutput(x, this->lowCutParameters, this->lowCutState[channel][index]);

        for (int index = 0; index < lowCutSlopes; index++)
            x = calculateOutput(x, this->highCutParameters, this->highCutState[channel][index]);

        buffer[i] = x;
    }
}

void AudioPluginAudioProcessor::resetEQState() {
    for (int ch = 0; ch < maxChannels; ch++)
        for (int s = 0; s < maxSlopes; s++) {
            this->lowCutState[ch][s] = BiquadState{};
            this->highCutState[ch][s] = BiquadState{};
        }
}
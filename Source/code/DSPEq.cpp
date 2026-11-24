#include "PluginProcessor.hpp"
#include <cmath>


void AudioPluginAudioProcessor::computeLowCutCoefficients(BiquadParameters& parameters, float lowFreq) {
	float w0 = 2.f * static_cast<float>(M_PI * (lowFreq / this->currentSampleRate));
	float cosw  = std::cos(w0);
	float alpha = std::sin(w0) / (2 * (1 / static_cast<float>(std::sqrt(2))));
	float a0 = 1 + alpha;

	parameters.a1 = (-2 * cosw) / a0;
	parameters.a2 = (1 - alpha) / a0;
	parameters.b0 = ((1 + cosw) / 2) / a0;
	parameters.b1 = -(1 + cosw) / a0;
	parameters.b2 = ((1 + cosw) / 2) / a0;
}

void AudioPluginAudioProcessor::computeHighCutCoefficients(BiquadParameters& parameters, float highFreq) {
	float w0 = 2.f * static_cast<float>(M_PI * (highFreq / this->currentSampleRate));
	float cosw  = std::cos(w0);
	float alpha = std::sin(w0) / (2 * (1 / static_cast<float>(std::sqrt(2))));
	float a0 = 1 + alpha;

	parameters.a1 = (-2 * cosw) / a0;
	parameters.a2 = (1 - alpha) / a0;
	parameters.b0 = ((1 - cosw) / 2) / a0;
	parameters.b1 = (1 - cosw) / a0;
	parameters.b2 = ((1 - cosw) / 2) / a0;
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
    for (int i = 0; i < numSamples; i++) {
        float bufferSample = buffer[i];

        for (int index = 0; index < lowCutSlopes; index++)
            bufferSample = calculateOutput(bufferSample, this->lowCutParameters, this->lowCutState[channel][index]);

        for (int index = 0; index < lowCutSlopes; index++)
            bufferSample = calculateOutput(bufferSample, this->highCutParameters, this->highCutState[channel][index]);

        buffer[i] = bufferSample;
    }
}

void AudioPluginAudioProcessor::resetEQState() {
    for (int channel = 0; channel < maxChannels; channel++) {
        for (int s = 0; s < maxSlopes; s++) {
            this->lowCutState[channel][s] = BiquadState{};
            this->highCutState[channel][s] = BiquadState{};
        }
    }
}

void AudioPluginAudioProcessor::myFFT() {


}

void AudioPluginAudioProcessor::computeFFTBuffer(juce::AudioBuffer<float>& buffer) {
    this->fftFinished = false;
    int numChannels = buffer.getNumChannels();
    std::size_t numSamples = static_cast<std::size_t>(buffer.getNumSamples());
    
    if (numChannels == 0)
        return ;

    int channelIndex = 0;
    std::vector<float> copyBuffer = {};

    auto* channelData = buffer.getReadPointer(channelIndex);

    for (std::size_t i = 0; i < numSamples; i++) 
        copyBuffer.push_back(channelData[i]);
    
    if (numChannels > 1) {
        channelIndex++;
        channelData = buffer.getReadPointer(channelIndex);
        
        for (std::size_t i = 0; i < numSamples; i++) {
            float currentSample = copyBuffer[i];
            copyBuffer[i] = (currentSample + channelData[i]) / 2;
        }
    }

    //convert copyBuffer to a complex<float> array
        
    this->fftFinished = true;
}

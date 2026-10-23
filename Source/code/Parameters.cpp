#include "Parameters.hpp"

Parameters::Parameters(juce::AudioProcessor& processorRef) : apvts{processorRef, nullptr, "Parameters", initApvts()} {}

Parameters::~Parameters() {}

juce::AudioProcessorValueTreeState::ParameterLayout Parameters::initApvts() {
    juce::AudioProcessorValueTreeState::ParameterLayout layout;

	this->initReverb(layout);
	this->initDistoriton(layout);
	this->initDelay(layout);
	this->initChorus(layout);
	this->initEQ(layout);

    return layout;
}

juce::AudioProcessorValueTreeState& Parameters::getApvts() {
    return this->apvts;
}

void Parameters::initReverb(juce::AudioProcessorValueTreeState::ParameterLayout& layout) {
	layout.add(std::make_unique<juce::AudioParameterInt>("reverb.on", "On", -1, 4, -1)); //if effect is on, -1 is off, 0 till 5 is index
	
	layout.add(std::make_unique<juce::AudioParameterChoice>("reverb.type", "Type", juce::StringArray("Plate", "Spring", "Hall"), 0));

	layout.add(std::make_unique<juce::AudioParameterFloat>("reverb.decay", "Decay", 0.0f, 30.0f, 4.0f)); //seconds
	layout.add(std::make_unique<juce::AudioParameterFloat>("reverb.predelay", "PreDelay", 0.0f, 80.0f, 20.0f)); //ms

	layout.add(std::make_unique<juce::AudioParameterFloat>("reverb.tone", "Tone", 0.0f, 127.0f, 63.0f)); //none
	layout.add(std::make_unique<juce::AudioParameterFloat>("reverb.size", "Size", 0.0f, 100.0f, 50.0f)); //percentage

	layout.add(std::make_unique<juce::AudioParameterFloat>("reverb.highcut", "Highcut", 10.0f, 20000.0f, 20000.0f)); //hz
	layout.add(std::make_unique<juce::AudioParameterFloat>("reverb.lowcut", "Lowcut", 10.0f, 20000.0f, 10.0f)); //hz
	
	layout.add(std::make_unique<juce::AudioParameterFloat>("reverb.mix", "Mix", 0.0f, 100.0f, 50.0f)); //percentage
}

void Parameters::initDistoriton(juce::AudioProcessorValueTreeState::ParameterLayout& layout) {
	layout.add(std::make_unique<juce::AudioParameterInt>("distortion.on", "On", -1, 4, -1)); //if effect is on, -1 is off, 0 till 5 is index

	layout.add(std::make_unique<juce::AudioParameterChoice>("distortion.type", "Type", juce::StringArray("Distortion", "Overdive", "Saturation", "Fuzz"), 0));
	
	layout.add(std::make_unique<juce::AudioParameterFloat>("distortion.drive", "Drive", 0.0f, 20.0f, 5.0f)); //dB
	layout.add(std::make_unique<juce::AudioParameterFloat>("distortion.tone", "Tone", 0.0f, 127.0f, 63.0f)); //none

	layout.add(std::make_unique<juce::AudioParameterFloat>("distortion.outputgain", "OutputGain", 0.0f, 20.0f, 5.0f)); //dB
	
	layout.add(std::make_unique<juce::AudioParameterFloat>("distortion.highcut", "Highcut", 10.0f, 20000.0f, 20000.0f)); //hz
	layout.add(std::make_unique<juce::AudioParameterFloat>("distortion.lowcut", "Lowcut", 10.0f, 20000.0f, 10.0f)); //hz

	layout.add(std::make_unique<juce::AudioParameterFloat>("distortion.mix", "Mix", 0.0f, 100.0f, 50.0f)); //percentage
}

void Parameters::initDelay(juce::AudioProcessorValueTreeState::ParameterLayout& layout) {
	layout.add(std::make_unique<juce::AudioParameterInt>("delay.on", "On", -1, 4, -1)); //if effect is on, -1 is off, 0 till 5 is index

	layout.add(std::make_unique<juce::AudioParameterChoice>("delay.type", "Type", juce::StringArray("Free", "Sync", "Ping-Pong"), 0));
	
	layout.add(std::make_unique<juce::AudioParameterFloat>("delay.left.time", "Left time", 0.0f, 1000.0f, 300.0f)); //ms
	layout.add(std::make_unique<juce::AudioParameterFloat>("delay.right.time", "Right time", 0.0f, 1000.0f, 300.0f)); //ms

	layout.add(std::make_unique<juce::AudioParameterChoice>("delay.left.option", "Time option", juce::StringArray("Free", "4th Note", "8th Note", "16th Note"), 0));
	layout.add(std::make_unique<juce::AudioParameterChoice>("delay.right.option", "Time option", juce::StringArray("Free", "4th Note", "8th Note", "16th Note"), 0));

	layout.add(std::make_unique<juce::AudioParameterFloat>("delay.left.feedback", "Left feedback", 0.0f, 100.0f, 50.0f)); //percentage
	layout.add(std::make_unique<juce::AudioParameterFloat>("delay.right.feedback", "Right feedback", 0.0f, 100.0f, 50.0f)); //percentage

	layout.add(std::make_unique<juce::AudioParameterFloat>("delay.highcut", "Highcut", 10.0f, 20000.0f, 20000.0f)); //hz
	layout.add(std::make_unique<juce::AudioParameterFloat>("delay.lowcut", "Lowcut", 10.0f, 20000.0f, 10.0f)); //hz

	layout.add(std::make_unique<juce::AudioParameterFloat>("delay.mix", "Mix", 0.0f, 100.0f, 50.0f)); //percentage
}

void Parameters::initChorus(juce::AudioProcessorValueTreeState::ParameterLayout& layout) {
	layout.add(std::make_unique<juce::AudioParameterInt>("chorus.on", "On", -1, 4, -1)); //if effect is on, -1 is off, 0 till 5 is index

	layout.add(std::make_unique<juce::AudioParameterFloat>("chorus.delay", "Delay", 0.0f, 100.0f, 10.0f)); //ms
	layout.add(std::make_unique<juce::AudioParameterFloat>("chorus.rate", "Rate", 0.0f, 2.0f, 0.4f)); //hz

	layout.add(std::make_unique<juce::AudioParameterFloat>("chorus.depth", "depth", 0.0f, 100.0f, 50.0f)); //percentage
	layout.add(std::make_unique<juce::AudioParameterFloat>("chorus.width", "width", 0.0f, 100.0f, 50.0f)); //percentage
	layout.add(std::make_unique<juce::AudioParameterFloat>("chorus.feedback", "Feedback", 0.0f, 100.0f, 50.0f)); //percentage
	
	layout.add(std::make_unique<juce::AudioParameterFloat>("chorus.highcut", "Highcut", 10.0f, 20000.0f, 20000.0f)); //hz

	layout.add(std::make_unique<juce::AudioParameterFloat>("chorus.mix", "Mix", 0.0f, 100.0f, 50.0f)); //percentage
}

void Parameters::initEQ(juce::AudioProcessorValueTreeState::ParameterLayout& layout) {
	layout.add(std::make_unique<juce::AudioParameterInt>("eq.on", "On", -1, 4, -1)); //if effect is on, -1 is off, 0 till 5 is index

	layout.add(std::make_unique<juce::AudioParameterFloat>("eq.low.frequency", "Frequency", juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 1.f), 20.0f)); //hz
	layout.add(std::make_unique<juce::AudioParameterFloat>("eq.low.gain", "Gain", juce::NormalisableRange<float>(-24.f, 24.f, 0.5f, 1.f), 0.0f)); //dB
	layout.add(std::make_unique<juce::AudioParameterFloat>("eq.low.quality", "Quality",juce::NormalisableRange<float>(0.1f, 10.f, 0.05f, 1.f), 1.f)); //dB
	layout.add(std::make_unique<juce::AudioParameterChoice>("eq.low.slope", "Slope", juce::StringArray("6 db", "12 db", "24 db", "36 db"), 0));

	layout.add(std::make_unique<juce::AudioParameterFloat>("eq.mid.frequency", "Frequency", juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 1.f), 1000.0f)); //hz
	layout.add(std::make_unique<juce::AudioParameterFloat>("eq.mid.gain", "Gain", juce::NormalisableRange<float>(-24.f, 24.f, 0.5f, 1.f), 0.0f)); //dB
	layout.add(std::make_unique<juce::AudioParameterFloat>("eq.mid.quality", "Quality",juce::NormalisableRange<float>(0.1f, 10.f, 0.05f, 1.f), 1.f)); //dB

	layout.add(std::make_unique<juce::AudioParameterFloat>("eq.high.frequency", "Frequency", juce::NormalisableRange<float>(20.f, 20000.f, 1.f, 1.f), 20000.0f)); //hz
	layout.add(std::make_unique<juce::AudioParameterFloat>("eq.high.gain", "Gain", juce::NormalisableRange<float>(-24.f, 24.f, 0.5f, 1.f), 0.0f)); //dB
	layout.add(std::make_unique<juce::AudioParameterFloat>("eq.high.quality", "Quality",juce::NormalisableRange<float>(0.1f, 10.f, 0.05f, 1.f), 1.f)); //dB
	layout.add(std::make_unique<juce::AudioParameterChoice>("eq.high.slope", "Slope", juce::StringArray("6 db", "12 db", "24 db", "36 db"), 0));
}


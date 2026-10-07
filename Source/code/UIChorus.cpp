#include "PluginEditor.hpp"

enum ChorusIndex {
	CHORUSDELAY,
	RATE,
	DEPTH,
	SPREAD,
	FEEDBACK,
	HIGHCUT,
	MIX
};

void AudioPluginAudioProcessorEditor::chorusInit() {
	
}

void AudioPluginAudioProcessorEditor::chorusPaint(juce::Graphics& g) {
	g.setColour(juce::Colour::fromRGB(ColorsScheme::chorusBackground[0], ColorsScheme::chorusBackground[1], ColorsScheme::chorusBackground[2]));
	g.fillRoundedRectangle(this->effectArea, this->cornerSizeEffectArea);
	g.drawRoundedRectangle(this->effectArea, this->cornerSizeEffectArea, 5.0f);
}

void AudioPluginAudioProcessorEditor::chorusResized() {



	this->setSlidersVisable(this->chorusSliders, true);
}


#include "PluginEditor.hpp"

void AudioPluginAudioProcessorEditor::delayPaint(juce::Graphics& g) {
	float minWidth = 10.f;
	float maxWidth = 980.f;
	float minHeight = 120.f;
	float maxHeight = 570.f;
	float cornerSize = 20.f;

	auto& bgColor = ColorsScheme::delayBackground;

	g.setColour(juce::Colour::fromRGB(bgColor[0], bgColor[1], bgColor[2]));
	g.fillRoundedRectangle(minWidth, minHeight, maxWidth, maxHeight, cornerSize);
	g.drawRoundedRectangle(minWidth, minHeight, maxWidth, maxHeight, cornerSize, 5.0f);
}

void AudioPluginAudioProcessorEditor::delayResized() {

}

void AudioPluginAudioProcessorEditor::delayHide() {

}

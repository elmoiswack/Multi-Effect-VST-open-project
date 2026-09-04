#include "PluginProcessor.hpp"
#include "PluginEditor.hpp"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    initEffectBoxes();

    setSize(1000, 800);
    resized();
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

void AudioPluginAudioProcessorEditor::initEffectBoxes() {
    juce::uint8 cRev[3] = {255, 255, 200};
    this->reverb = EffectBox("Reverb", cRev);
    addAndMakeVisible(this->reverb);

    juce::uint8 cDis[3] = {158, 27, 0};
    this->distortion = EffectBox("Distortion", cDis);
    addAndMakeVisible(this->distortion);

    juce::uint8 cDel[3] = {11, 150, 71};
    this->delay = EffectBox("Delay", cDel);
    addAndMakeVisible(this->delay);

    juce::uint8 cCho[3] = {101, 6, 126};
    this->chorus = EffectBox("Chorus", cCho);
    addAndMakeVisible(this->chorus);

    juce::uint8 cEQ[3] = {255, 255, 255};
    this->eq = EffectBox("EQ", cEQ);
    addAndMakeVisible(this->eq);
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g) {
    g.fillAll(juce::Colour::fromRGB(95, 95, 95));
}

void AudioPluginAudioProcessorEditor::resized() {
    auto height = getHeight();
    auto width = getWidth();

    auto widthBox = 150;
    auto heigthBox = 125;

    this->reverb.setBounds(
        width / 4 - (width / 8), 
        height / 4, 
        widthBox, 
        heigthBox);

    this->distortion.setBounds(
        width / 4 * 3 - (width / 8), 
        height / 4, 
        widthBox, 
        heigthBox);

    this->delay.setBounds(
        width / 4 - (width / 8), 
        height / 4 * 2, 
        widthBox, 
        heigthBox);

    this->chorus.setBounds(
        width / 4 * 3 - (width / 8), 
        height / 4 * 2, 
        widthBox, 
        heigthBox);

    this->eq.setBounds(
        width / 2 - (width / 8), 
        height / 4 * 2, 
        widthBox,
        heigthBox);
}


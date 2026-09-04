#include "PluginProcessor.hpp"
#include "PluginEditor.hpp"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    this->selectEffectBox.reserve(5);
    this->chainEffectBox.reserve(5);
    initEffectBoxes();

    setSize(1000, 800);
    resized();
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
}

void AudioPluginAudioProcessorEditor::initEffectBoxes() {
    juce::uint8 cRev[3] = {255, 255, 200};
    this->selectEffectBox.push_back(EffectBox("Reverb", cRev));
    this->chainEffectBox.push_back(EffectBox("Reverb", cRev));
    addAndMakeVisible(this->selectEffectBox[EffectIndex::REVERB]);
    addAndMakeVisible(this->chainEffectBox[EffectIndex::REVERB]);

    juce::uint8 cDis[3] = {158, 27, 0};
    this->selectEffectBox.push_back(EffectBox("Distortion", cDis));
    this->chainEffectBox.push_back(EffectBox("Distortion", cDis));
    addAndMakeVisible(this->selectEffectBox[EffectIndex::DISTORTION]);

    juce::uint8 cDel[3] = {11, 150, 71};
    this->selectEffectBox.push_back(EffectBox("Delay", cDel));
    this->chainEffectBox.push_back(EffectBox("Delay", cDel));
    addAndMakeVisible(this->selectEffectBox[EffectIndex::DELAY]);

    juce::uint8 cCho[3] = {101, 6, 126};
    this->selectEffectBox.push_back(EffectBox("Chorus", cCho));
    this->chainEffectBox.push_back(EffectBox("Chorus", cCho));
    addAndMakeVisible(this->selectEffectBox[EffectIndex::CHORUS]);

    juce::uint8 cEQ[3] = {255, 255, 255};
    this->selectEffectBox.push_back(EffectBox("EQ", cEQ));
    this->chainEffectBox.push_back(EffectBox("EQ", cEQ));
    addAndMakeVisible(this->selectEffectBox[EffectIndex::EQ]);
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll(juce::Colour::fromRGB(35, 35, 35));

    juce::Path seperator;
    seperator.addRectangle(0, 100, 1000, 10);
    g.setColour(juce::Colours::black);
	g.fillPath(seperator);
}

void AudioPluginAudioProcessorEditor::resized() {
    auto height = getHeight();
    auto width = getWidth();

    auto widthBox = 150;
    auto heigthBox = 125;

    this->selectEffectBox[EffectIndex::REVERB].setBounds(
        width / 4 - (width / 8), 
        height / 4,
        widthBox,
        heigthBox);

   this->selectEffectBox[EffectIndex::DISTORTION].setBounds(
        width / 4 * 3 - (width / 8), 
        height / 4, 
        widthBox, 
        heigthBox);

    this->selectEffectBox[EffectIndex::DELAY].setBounds(
        width / 4 - (width / 8), 
        height / 4 * 2, 
        widthBox, 
        heigthBox);

    this->selectEffectBox[EffectIndex::CHORUS].setBounds(
        width / 4 * 3 - (width / 8), 
        height / 4 * 2, 
        widthBox, 
        heigthBox);

    this->selectEffectBox[EffectIndex::EQ].setBounds(
        width / 2 - (width / 8), 
        height / 4 * 2, 
        widthBox,
        heigthBox);

    this->chainEffectBox[EffectIndex::REVERB].setBounds(
        20,
        10,
        180,
        80
    );
}


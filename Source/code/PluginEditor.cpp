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
    this->selectEffectBox.push_back(EffectBox("Reverb", ColorsScheme::reverbPrimary));
    this->chainEffectBox.push_back(EffectBox("Reverb", ColorsScheme::reverbPrimary));
    addAndMakeVisible(this->selectEffectBox[EffectIndex::REVERB]);
    addAndMakeVisible(this->chainEffectBox[EffectIndex::REVERB]);

    this->selectEffectBox.push_back(EffectBox("Distortion", ColorsScheme::distortionPrimary));
    this->chainEffectBox.push_back(EffectBox("Distortion", ColorsScheme::distortionPrimary));
    addAndMakeVisible(this->selectEffectBox[EffectIndex::DISTORTION]);
    addAndMakeVisible(this->chainEffectBox[EffectIndex::DISTORTION]);

    this->selectEffectBox.push_back(EffectBox("Delay", ColorsScheme::delayPrimary));
    this->chainEffectBox.push_back(EffectBox("Delay", ColorsScheme::delayPrimary));
    addAndMakeVisible(this->selectEffectBox[EffectIndex::DELAY]);
    addAndMakeVisible(this->chainEffectBox[EffectIndex::DELAY]);
    
    this->selectEffectBox.push_back(EffectBox("Chorus", ColorsScheme::chorusPrimary));
    this->chainEffectBox.push_back(EffectBox("Chorus", ColorsScheme::chorusPrimary));
    addAndMakeVisible(this->selectEffectBox[EffectIndex::CHORUS]);
    addAndMakeVisible(this->chainEffectBox[EffectIndex::CHORUS]);

    this->selectEffectBox.push_back(EffectBox("EQ", ColorsScheme::eqPrimary));
    this->chainEffectBox.push_back(EffectBox("EQ", ColorsScheme::eqPrimary));
    addAndMakeVisible(this->selectEffectBox[EffectIndex::EQ]);
    addAndMakeVisible(this->chainEffectBox[EffectIndex::EQ]);
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll(juce::Colour::fromRGB(35, 35, 35));

    float startX = 197.5;
    g.setColour(juce::Colours::white);
    for (std::size_t i = 0; i < (this->chainEffectBox.size() - 1); i++) {
        juce::Path seperatorChainSelector;
        seperatorChainSelector.addRectangle(startX + (i * 200), 20, 5, 60);    
        g.fillPath(seperatorChainSelector);
    }

    juce::Path seperatorChainSelector;
    seperatorChainSelector.addRectangle(0, 100, 1000, 10);
    g.setColour(juce::Colours::black);
	g.fillPath(seperatorChainSelector);
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

    int spacing = 200;
    int startX = 10;
    int chainBoxY = 10;
    int chainBoxWidth = 180;
    int chainBoxHeight = 80;

    for (std::size_t i = 0; i < this->chainEffectBox.size(); i++) {
        this->chainEffectBox[i].setBounds(startX + (i * spacing), chainBoxY, chainBoxWidth, chainBoxHeight);
    }
}


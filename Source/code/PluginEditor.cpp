#include "PluginProcessor.hpp"
#include "PluginEditor.hpp"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);

    this->selectEffectBox.reserve(5);
    this->chainEffectBox.reserve(5);
    this->activeChain.reserve(5);
    initEffectBoxes();

    setSize(1000, 800);
    resized();
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {

}

void AudioPluginAudioProcessorEditor::initEffectBoxes() {
    this->initEffectObject("Reverb", ColorsScheme::reverbPrimary, EffectIndex::REVERB);
    this->initEffectObject("Distortion", ColorsScheme::distortionPrimary, EffectIndex::DISTORTION);
    this->initEffectObject("Delay", ColorsScheme::delayPrimary, EffectIndex::DELAY);
    this->initEffectObject("Chorus", ColorsScheme::chorusPrimary, EffectIndex::CHORUS);
    this->initEffectObject("EQ", ColorsScheme::eqPrimary, EffectIndex::EQ);
}

void AudioPluginAudioProcessorEditor::initEffectObject(juce::String name, const juce::uint8* color, EffectIndex index) {
    auto& objectSelector = this->selectEffectBox.emplace_back(
        name,
        color,
        EffectBoxType::SELECTOR,
        index
    );
    objectSelector.onLeftClickAdd = [this](EffectIndex effect) {
        selectorClicked(effect);
    };
    objectSelector.onLeftClickRemove = [this](EffectIndex effect) {
        removeFromChain(effect);
    };
    addAndMakeVisible(objectSelector);
    
    auto& objectChain = this->chainEffectBox.emplace_back(
        name,
        color,
        EffectBoxType::CHAIN,
        index
    );
    addAndMakeVisible(objectChain);
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics& g) {
    g.fillAll(juce::Colour::fromRGB(35, 35, 35));

    float startX = 200;
    g.setColour(juce::Colours::white);
    juce::Path seperatorChain;
    for (std::size_t i = 0; (i + 1) < this->activeChain.size(); i++) {
        seperatorChain.addRectangle(startX + (i * 200), 20, 5, 60);    
        g.fillPath(seperatorChain);
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
    int startX = 15;
    int chainBoxY = 10;
    int chainBoxWidth = 170;
    int chainBoxHeight = 80;

    for (std::size_t i = 0; i < this->activeChain.size(); i++) {
        this->activeChain[i]->setBounds(startX + (i * spacing), chainBoxY, chainBoxWidth, chainBoxHeight);
    }
}

void AudioPluginAudioProcessorEditor::selectorClicked(EffectIndex effect) {
    for (auto& it : this->activeChain) {
        if (effect == EffectIndex::REVERB && it->getEffectName() == "Reverb") {
            return ; //TODO: INSTEAD OF RETURN, DIRECT USER TO REVERB PAGE
        }
        if (effect == EffectIndex::DISTORTION && it->getEffectName() == "Distortion") {
            return ; //TODO: INSTEAD OF RETURN, DIRECT USER TO Distortion PAGE
        }
        if (effect == EffectIndex::CHORUS && it->getEffectName() == "Chorus") {
            return ; //TODO: INSTEAD OF RETURN, DIRECT USER TO Chorus PAGE
        }
        if (effect == EffectIndex::DELAY && it->getEffectName() == "Delay") {
            return ; //TODO: INSTEAD OF RETURN, DIRECT USER TO Delay PAGE
        }
        if (effect == EffectIndex::EQ && it->getEffectName() == "EQ") {
            return ; //TODO: INSTEAD OF RETURN, DIRECT USER TO EQ PAGE
        }
    }

    this->activeChain.push_back(&chainEffectBox[effect]);
    resized();
    repaint();
}

void AudioPluginAudioProcessorEditor::removeFromChain(EffectIndex effect) {
    auto target = &chainEffectBox[effect];

    for (auto it = activeChain.begin(); it != activeChain.end(); ++it) {
        if (*it == target) {
            activeChain.erase(it);
            resized();
            repaint();
            return;
        }
    }
}
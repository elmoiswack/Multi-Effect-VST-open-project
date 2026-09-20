#pragma once

#include "PluginProcessor.hpp"
#include "Slider.hpp"
#include "EffectBox.hpp"
#include <vector>
#include <algorithm>

struct ColorsScheme {
    inline static constexpr juce::uint8 reverbPrimary[3] = {255, 255, 100};
	inline static constexpr juce::uint8 reverbSecondary[3] = {251, 156, 14};
	inline static constexpr juce::uint8 reverbBackground[3] = {205, 205, 50};

    inline static constexpr juce::uint8 distortionPrimary[3] = {195, 35, 2};
	inline static constexpr juce::uint8 distortionSecondary[3] = {10, 10, 10}; //andere kleur asahbi
    inline static constexpr juce::uint8 distortionBackground[3] = {108, 0, 0};

    inline static constexpr juce::uint8 delayPrimary[3] = {19, 197, 96};
    inline static constexpr juce::uint8 delaySecondary[3] = {255, 255, 0};
	inline static constexpr juce::uint8 delayBackground[3] = {0, 100, 21};

    inline static constexpr juce::uint8 chorusPrimary[3] = {124, 25, 150};
    inline static constexpr juce::uint8 chorusSecondary[3] = {25, 255, 25};
	inline static constexpr juce::uint8 chorusBackground[3] = {51, 0, 76};

    inline static constexpr juce::uint8 eqPrimary[3] = {255, 255, 255};
	inline static constexpr juce::uint8 eqSecondary[3] = {10, 10, 10};
	inline static constexpr juce::uint8 eqBackground[3] = {205, 205, 205};

	inline static constexpr juce::uint8 addBackground[3] = {20, 20, 20};
};

//==============================================================================
class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    void initEffectBoxes();
    void initEffectObject(juce::String name, const juce::uint8* color, EffectIndex index);

	void computeView(EffectIndex effect);

    void selectorPaint(juce::Graphics& g);
    void selectorResized();
    void selectorHide();

    void reverbPaint(juce::Graphics& g);
    void reverbResized();
    void reverbHide();

    void distortionPaint(juce::Graphics& g);
    void distortionResized();
    void distortionHide();

    void delayPaint(juce::Graphics& g);
    void delayResized();
    void delayHide();

    void chorusPaint(juce::Graphics& g);
    void chorusResized();
    void chorusHide();

    void eqPaint(juce::Graphics& g);
    void eqResized();
    void eqHide();

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    void selectorClicked(EffectIndex effect);
    void removeFromChain(EffectIndex effect);

    void dragChainObject(EffectIndex effect, const juce::MouseEvent& event);
    void swapChainObjects(EffectIndex effect, const juce::MouseEvent& event);

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;

    std::vector<EffectBox> selectEffectBox;
    std::vector<EffectBox> chainEffectBox;
    std::vector<EffectBox*> activeChain;
    EffectBox* adder;

    EffectIndex currentSelected;

    bool drawMoveChainObject;
    juce::Path moveRectangle;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AudioPluginAudioProcessorEditor)
};
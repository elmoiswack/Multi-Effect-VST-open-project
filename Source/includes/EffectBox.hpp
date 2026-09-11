#include "BinaryData.h"
#include <juce_gui_basics/juce_gui_basics.h>

enum EffectIndex {
    REVERB,
    DISTORTION,
    DELAY,
    CHORUS,
    EQ
};

enum EffectBoxType {
	CHAIN,
	SELECTOR,
};

class EffectBox : public juce::Component
{
private:
	juce::String effectName;
	juce::uint8 color[3];
	EffectBoxType type;
	std::unique_ptr<juce::Drawable> xIcon;
	juce::DrawableButton drawableIcon;
	EffectIndex effectIndex;

public:
	EffectBox();
	EffectBox(juce::String name, const juce::uint8* colorRGB, EffectBoxType type, EffectIndex index);
	EffectBox(EffectBox&& other) noexcept;
	EffectBox& operator=(EffectBox&& other) noexcept;
	~EffectBox() override; 

    void paint(juce::Graphics& g) override;
    void resized() override;

	void mouseDown(const juce::MouseEvent& event) override;
    std::function<void(EffectIndex)> onLeftClickAdd;
    std::function<void(EffectIndex)> onLeftClickRemove;

	juce::String getEffectName();
};


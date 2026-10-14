#include "BinaryData.h"
#include <juce_gui_basics/juce_gui_basics.h>

enum EffectIndex {
    REVERB,
    DISTORTION,
    DELAY,
    CHORUS,
    EQ,
	ADD,
};

enum CustomEffectBoxType {
	CHAIN,
	SELECTOR,
	ADDER,
};

class CustomEffectBox : public juce::Component
{
private:
	juce::String effectName;
	juce::uint8 color[3];
	CustomEffectBoxType type;
	std::unique_ptr<juce::Drawable> xIcon;
	juce::DrawableButton drawableIcon;
	EffectIndex effectIndex;
	bool isActive;

public:
	CustomEffectBox();
	CustomEffectBox(juce::String name, const juce::uint8* colorRGB, CustomEffectBoxType type, EffectIndex index);
	CustomEffectBox(CustomEffectBox&& other) noexcept;
	CustomEffectBox& operator=(CustomEffectBox&& other) noexcept;
	~CustomEffectBox() override; 

    void paint(juce::Graphics& g) override;
    void resized() override;

	void setActive(bool value);

	void mouseDown(const juce::MouseEvent& event) override;
	void mouseDrag(const juce::MouseEvent& event) override;
	void mouseUp(const juce::MouseEvent& event) override;

	//selector box functions
    std::function<void(EffectIndex)> onLeftClickAdd;

	//chain box functions
    std::function<void(EffectIndex, const juce::MouseEvent&)> onLeftClickDragEffect;
	std::function<void(EffectIndex, const juce::MouseEvent&)> onLeftClickReplaceAfterDrag;
	std::function<void(EffectIndex)> onLeftClickShowEffect;
    std::function<void(EffectIndex)> onLeftClickRemove;

	juce::String getEffectName();
	CustomEffectBoxType getCustomEffectBoxType();
};


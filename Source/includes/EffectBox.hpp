#include "BinaryData.h"
#include <juce_gui_basics/juce_gui_basics.h>

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

public:
	EffectBox();
	EffectBox(juce::String name, const juce::uint8* colorRGB, EffectBoxType type);
	EffectBox(EffectBox&& other) noexcept;
	EffectBox& operator=(EffectBox&& other) noexcept;
	~EffectBox() override; 

    void paint(juce::Graphics& g) override;
    void resized() override;

};


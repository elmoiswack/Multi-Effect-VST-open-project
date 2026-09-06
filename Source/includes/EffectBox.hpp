#include <juce_gui_basics/juce_gui_basics.h>

class EffectBox : public juce::Component
{
private:
	juce::String effectName;
	juce::uint8 color[3];
public:
	EffectBox();
	EffectBox(juce::String name, const juce::uint8* colorRGB);
	EffectBox(EffectBox&& other) noexcept;
	EffectBox& operator=(EffectBox&& other) noexcept;
	~EffectBox() override; 

    void paint(juce::Graphics& g) override;
    void resized() override;
};


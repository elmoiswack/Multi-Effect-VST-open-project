#include <juce_gui_basics/juce_gui_basics.h>

class Slider : public juce::Component
{
private:
	juce::String name;
	juce::uint8 primaryColor[3];
	juce::uint8 secondaryColor[3];

	float rotaryStartAngle;
	float rotaryEndAngle;
	float sliderPos;

public:
	Slider();
	Slider(Slider&& other) noexcept;
	Slider& operator=(Slider&& other) noexcept;
	Slider(juce::String sliderName, const juce::uint8* primary, const juce::uint8* secondary);
	~Slider() override; 

    void paint(juce::Graphics& g) override;
    void resized() override;

	void setRotaryStart(float value);
	void setRotaryEnd(float value);
	void setSliderPos(float value);

	juce::String getName();

	std::function<void(const juce::MouseEvent&)> moveSlider;
};


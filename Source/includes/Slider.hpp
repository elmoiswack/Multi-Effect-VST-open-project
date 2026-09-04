#include <juce_gui_basics/juce_gui_basics.h>

class Slider : public juce::Component
{
private:
public:
	Slider();
	~Slider() override; 

    void paint(juce::Graphics& g) override;
    void resized() override;
};


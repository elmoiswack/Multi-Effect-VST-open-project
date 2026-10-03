#include <juce_gui_basics/juce_gui_basics.h>

class CustomLAFCombo : public juce::LookAndFeel_V4 
{
private:
    juce::Colour colorPrimary = juce::Colours::white;
    juce::Colour colorSecondary = juce::Colours::black;
    
	float fontSize = 14.0f;
    float cornerRadius = 6.0f;
public:
    CustomLAFCombo();

    void setColors(const juce::uint8* primary, const juce::uint8* secondary);

    void positionComboBoxText(juce::ComboBox& box, juce::Label& label) override;
    
	void drawComboBox(juce::Graphics& g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox& box) override;
    void drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const juce::String& text, const juce::String& shortcutKeyText, const juce::Drawable* icon, const juce::Colour* textColour) override;
   	juce::PopupMenu::Options getOptionsForComboBoxPopupMenu(juce::ComboBox& box, juce::Label& label) override;

	juce::Font getComboBoxFont(juce::ComboBox&) override;
    void setFontSize(float size);
    
	void setCornerRadius(float radius);
};
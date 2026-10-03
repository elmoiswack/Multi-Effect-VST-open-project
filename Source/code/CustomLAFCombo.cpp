#include "CustomLAFCombo.hpp"

CustomLAFCombo::CustomLAFCombo() {
	juce::uint8 primary[3] = {255, 255, 255};
	juce::uint8 secondary[3] = {255, 255, 255};

	setColors(primary, secondary);
}

void CustomLAFCombo::positionComboBoxText(juce::ComboBox& box, juce::Label& label) {
    label.setBounds(1, 1, box.getWidth() - 20, box.getHeight() - 2);
    label.setFont(getComboBoxFont(box));
    label.setJustificationType(juce::Justification::centred);
}

void CustomLAFCombo::drawComboBox(juce::Graphics& g, int width, int height, bool isButtonDown, int buttonX, int buttonY, int buttonW, int buttonH, juce::ComboBox& box) {
    auto bounds = juce::Rectangle<float>(0.0f, 0.0f, (float) width, (float) height);

    g.setColour(box.findColour(juce::ComboBox::backgroundColourId));
    g.fillRoundedRectangle(bounds, cornerRadius);

    g.setColour(box.findColour(box.hasKeyboardFocus(true) ? juce::ComboBox::focusedOutlineColourId : juce::ComboBox::outlineColourId));
    g.drawRoundedRectangle(bounds.reduced(0.5f), cornerRadius, 1.0f);

    juce::Rectangle<float> arrowZone((float) buttonX, (float) buttonY, (float) buttonW, (float) buttonH);
    juce::Path arrow;
    arrow.startNewSubPath(arrowZone.getCentreX() - 3.0f, arrowZone.getCentreY() - 2.0f);
    arrow.lineTo(arrowZone.getCentreX(), arrowZone.getCentreY() + 2.0f);
    arrow.lineTo(arrowZone.getCentreX() + 3.0f, arrowZone.getCentreY() - 2.0f);

    g.setColour(box.findColour(juce::ComboBox::arrowColourId).withAlpha(box.isEnabled() ? 1.0f : 0.3f));
    g.strokePath(arrow, juce::PathStrokeType(2.0f));
}

void CustomLAFCombo::drawPopupMenuItem(juce::Graphics& g, const juce::Rectangle<int>& area, bool isSeparator, bool isActive, bool isHighlighted, bool isTicked, bool hasSubMenu, const juce::String& text, const juce::String& shortcutKeyText, const juce::Drawable* icon, const juce::Colour* textColour) {
    juce::Colour grey = juce::Colours::grey;
    juce::LookAndFeel_V4::drawPopupMenuItem(g, area, isSeparator, isActive, isHighlighted, false, hasSubMenu, text, shortcutKeyText, icon, isTicked ? &grey : textColour);
}

juce::PopupMenu::Options CustomLAFCombo::getOptionsForComboBoxPopupMenu(juce::ComboBox& box, juce::Label&) {
    auto boxBounds = box.getScreenBounds();
    auto target = juce::Rectangle<int>(boxBounds.getX(), boxBounds.getBottom(), 1, 1);

    return juce::PopupMenu::Options().withTargetScreenArea(target).withMinimumWidth(box.getWidth());
}

juce::Font CustomLAFCombo::getComboBoxFont(juce::ComboBox&) {
	return juce::Font(this->fontSize);
}

void CustomLAFCombo::setFontSize(float size) { 
	this->fontSize = size; 
}

void CustomLAFCombo::setCornerRadius(float radius) { 
	this->cornerRadius = radius; 
}

void CustomLAFCombo::setColors(const juce::uint8* primary, const juce::uint8* secondary) {
    this->colorPrimary = juce::Colour::fromRGB(primary[0],   primary[1],   primary[2]);
    this->colorSecondary = juce::Colour::fromRGB(secondary[0], secondary[1], secondary[2]);

    setColour(juce::ComboBox::backgroundColourId, colorSecondary);
    setColour(juce::ComboBox::outlineColourId, colorPrimary);
    setColour(juce::ComboBox::focusedOutlineColourId, colorPrimary);
    setColour(juce::ComboBox::textColourId, juce::Colours::white);
    setColour(juce::ComboBox::arrowColourId, colorPrimary);

    setColour(juce::PopupMenu::backgroundColourId, colorSecondary);
    setColour(juce::PopupMenu::highlightedBackgroundColourId, colorPrimary);
    setColour(juce::PopupMenu::highlightedTextColourId, colorSecondary);
    setColour(juce::PopupMenu::textColourId, juce::Colours::white);
}
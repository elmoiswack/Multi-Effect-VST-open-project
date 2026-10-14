#include "CustomEffectBox.hpp"

CustomEffectBox::CustomEffectBox() : xIcon(nullptr), drawableIcon("xIcon button", juce::DrawableButton::ButtonStyle::ImageFitted), effectIndex(EffectIndex::REVERB) {
    this->effectName = "";
    this->color[0] = 0;
    this->color[1] = 0;
    this->color[2] = 0;
    this->type = CustomEffectBoxType::ADDER;
    this->effectIndex = EffectIndex::ADD;
    this->isActive = false;
}

CustomEffectBox::CustomEffectBox(juce::String name, const juce::uint8* colorRGB, CustomEffectBoxType typeBox, EffectIndex index) : 
    drawableIcon("xIcon button", juce::DrawableButton::ButtonStyle::ImageFitted), effectIndex(index) 
{
	this->effectName = name;
	this->color[0] = colorRGB[0];
	this->color[1] = colorRGB[1];
	this->color[2] = colorRGB[2];
	this->type = typeBox;
    this->isActive = false;
    
	if (typeBox == CustomEffectBoxType::CHAIN) {
		this->xIcon = juce::Drawable::createFromImageData(
		BinaryData::x_svg,
		BinaryData::x_svgSize);
		this->drawableIcon.setImages(this->xIcon.get());
        this->drawableIcon.onClick = [this] { onLeftClickRemove(this->effectIndex); };
		addAndMakeVisible(this->drawableIcon);
	} else {
		this->xIcon = nullptr;
	}
}

CustomEffectBox::~CustomEffectBox() {

}

CustomEffectBox::CustomEffectBox(CustomEffectBox&& other) noexcept
    : drawableIcon("xIcon button", juce::DrawableButton::ButtonStyle::ImageFitted) {
    this->effectName = std::move(other.effectName);
    this->xIcon = std::move(other.xIcon);

    this->color[0] = other.color[0];
    this->color[1] = other.color[1];
    this->color[2] = other.color[2];
    this->type = other.type;
    this->effectIndex = other.effectIndex;
    this->isActive = other.isActive;

    if (this->xIcon != nullptr)
        this->drawableIcon.setImages(this->xIcon.get());

    addAndMakeVisible(this->drawableIcon);

    other.effectName = "";
    other.color[0] = 0;
    other.color[1] = 0;
    other.color[2] = 0;
}

CustomEffectBox& CustomEffectBox::operator=(CustomEffectBox&& other) noexcept {
    if (this != &other)
    {
        this->effectName = std::move(other.effectName);

        this->color[0] = other.color[0];
        this->color[1] = other.color[1];
        this->color[2] = other.color[2];
        this->effectIndex = other.effectIndex;
        this->type = other.type;
        this->xIcon = std::move(other.xIcon);
        this->isActive = other.isActive;


        if (this->xIcon != nullptr)
            this->drawableIcon.setImages(this->xIcon.get());

        addAndMakeVisible(this->drawableIcon);
    }

    return *this;
}

void CustomEffectBox::paint(juce::Graphics& g) {
	float cornerSize = 20.f;

    if (this->isActive == true && this->type == CustomEffectBoxType::SELECTOR)
        g.setColour(juce::Colour::fromRGB(38, 38, 38));
    else
        g.setColour(juce::Colour::fromRGB(58, 58, 58));
    
	g.fillRoundedRectangle(getLocalBounds().toFloat(), cornerSize);
	g.drawRoundedRectangle(getLocalBounds().toFloat(), cornerSize, 5.0f);

    if (this->type == CustomEffectBoxType::ADDER) {
        juce::Path verticle;
        juce::Path horizontal;
        int chainBoxWidth = 170;
        int chainBoxHeight = 80;

        int startVert = chainBoxWidth / 2 ;
        int startHori = chainBoxHeight / 2;
        int vertHeight = 60;

        verticle.addRectangle(startVert, 10, 10, vertHeight);
        horizontal.addRectangle((getWidth() / 2) - (vertHeight / 2) + 5, startHori - 5, vertHeight, 10);

        g.setColour(juce::Colours::white);
        g.fillPath(verticle);
        g.fillPath(horizontal);
    } else {
        // juce::FontOptions font("FreeSans", 40.0f, juce::Font::bold);
        // std::cout << font.getTypeface() << std::endl;
        g.setColour(juce::Colour::fromRGB(this->color[0], this->color[1], this->color[2]));
        g.setFont(30.f);
        g.drawText(this->effectName, getLocalBounds(), juce::Justification::centred);
    }
}

void CustomEffectBox::resized() {
	int width = getWidth();
	int svgHeight = 15.0f;
	int svgWidth = 15.0f;

	if (this->type == CustomEffectBoxType::CHAIN) {
		this->drawableIcon.setBounds(width - (svgWidth * 1.5f), 10.0f, svgWidth, svgHeight);
	}
}

void CustomEffectBox::mouseDown(const juce::MouseEvent& event)
{
    if (event.mods.isLeftButtonDown()) {
        if (this->onLeftClickAdd && this->type == CustomEffectBoxType::SELECTOR)
            this->onLeftClickAdd(this->effectIndex);
        if (this->onLeftClickShowEffect && \
            (this->type == CustomEffectBoxType::CHAIN || this->type == CustomEffectBoxType::ADDER))
            this->onLeftClickShowEffect(this->effectIndex);
    }
}

void CustomEffectBox::mouseDrag(const juce::MouseEvent& event) {
    if (onLeftClickDragEffect && this->type == CustomEffectBoxType::CHAIN) {
        onLeftClickDragEffect(this->effectIndex, event);
    }
}

void CustomEffectBox::mouseUp(const juce::MouseEvent& event) {
    if (onLeftClickReplaceAfterDrag && this->type == CustomEffectBoxType::CHAIN) {
        onLeftClickReplaceAfterDrag(this->effectIndex, event);
    }
}

juce::String CustomEffectBox::getEffectName() {
    return this->effectName;
}

CustomEffectBoxType CustomEffectBox::getCustomEffectBoxType() {
    return this->type;
}

void CustomEffectBox::setActive(bool value) {
    this->isActive = value;
    resized();
    repaint();
}

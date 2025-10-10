#include "TextElement.h"
#include <iostream>

TextElement::TextElement() : RenderElement(), sfText(*new sf::Font()) {
    std::cout << "[TextElement] Default constructor called.\n";
    text = "";
    textColor = sf::Color::White;
    fontSize = 24;
    textStyle = sf::Text::Regular;
    
    font = new sf::Font();
    fontLoaded = loadSystemFont();
    
    if (fontLoaded) {
        sfText.setFont(*font);
    }
    
    sfText.setString(text);
    sfText.setCharacterSize(fontSize);
    sfText.setFillColor(textColor);
    sfText.setStyle(textStyle);
    
    if (!fontLoaded) {
        std::cout << "[TextElement] WARNING: Font failed to load in constructor!\n";
    }
}

TextElement::TextElement(const std::string& text, int x, int y, unsigned int fontSize) 
    : RenderElement(), sfText(*new sf::Font()) {
    std::cout << "[TextElement] Constructor called with text, position, and size.\n";
    this->text = text;
    this->fontSize = fontSize;
    this->textColor = sf::Color::White;
    this->textStyle = sf::Text::Regular;
    
    this->font = new sf::Font();
    this->fontLoaded = loadSystemFont();
    
    if (fontLoaded) {
        sfText.setFont(*font);
    }
    
    sfText.setString(text);
    sfText.setCharacterSize(fontSize);
    sfText.setFillColor(textColor);
    sfText.setPosition({static_cast<float>(x), static_cast<float>(y)});
    sfText.setStyle(textStyle);
    
    if (!fontLoaded) {
        std::cout << "[TextElement] WARNING: Font failed to load in constructor!\n";
    }
}

TextElement::TextElement(const std::string& text, int x, int y, unsigned int fontSize, sf::Color color) 
    : RenderElement(), sfText(*new sf::Font()) {
    std::cout << "[TextElement] Constructor called with text, position, size, and color.\n";
    this->text = text;
    this->fontSize = fontSize;
    this->textColor = color;
    this->textStyle = sf::Text::Regular;
    
    this->font = new sf::Font();
    this->fontLoaded = loadSystemFont();
    
    if (fontLoaded) {
        sfText.setFont(*font);
    }
    
    sfText.setString(text);
    sfText.setCharacterSize(fontSize);
    sfText.setFillColor(textColor);
    sfText.setPosition({static_cast<float>(x), static_cast<float>(y)});
    sfText.setStyle(textStyle);
    
    if (!fontLoaded) {
        std::cout << "[TextElement] WARNING: Font failed to load in constructor!\n";
    }
}

TextElement::~TextElement() {
    std::cout << "[TextElement] Destructor called.\n";
    if (font != nullptr) {
        delete font;
        font = nullptr;
    }
}

void TextElement::onMount() {
    std::cout << "[TextElement] onMount() called.\n";
    
    if (!fontLoaded) {
        loadSystemFont();
    }
}

void TextElement::draw(sf::RenderWindow* globalWindow) {
    if (globalWindow == nullptr || !fontLoaded) {
        std::cout << "[TextElement] ERROR: Cannot draw, font or window invalid.\n";
        return;
    }

    // Handle animation
    if (animationType == TextAnimation::Ellipsis) {
        sf::Time elapsed = animationClock.getElapsedTime();
        
        if (elapsed.asMilliseconds() >= 300) {  // Change frame every 300ms
            animationFrame = (animationFrame + 1) % 4;  // 0 to 3
            std::string dots(animationFrame, '.');
            sfText.setString(baseText + dots);
            animationClock.restart();
        }
    }

    globalWindow->draw(sfText);
}


void TextElement::setText(const std::string& newText) {
    text = newText;
    sfText.setString(newText);
    std::cout << "[TextElement] Text updated to: \"" << newText << "\"\n";
}

void TextElement::setColor(sf::Color color) {
    textColor = color;
    sfText.setFillColor(color);
}

void TextElement::setFontSize(unsigned int size) {
    fontSize = size;
    sfText.setCharacterSize(size);
}

void TextElement::setStyle(sf::Text::Style style) {
    textStyle = style;
    sfText.setStyle(style);
}

void TextElement::setBold(bool bold) {
    if (bold) {
        sfText.setStyle(sfText.getStyle() | sf::Text::Bold);
    } else {
        sfText.setStyle(sfText.getStyle() & ~sf::Text::Bold);
    }
}

void TextElement::setItalic(bool italic) {
    if (italic) {
        sfText.setStyle(sfText.getStyle() | sf::Text::Italic);
    } else {
        sfText.setStyle(sfText.getStyle() & ~sf::Text::Italic);
    }
}

void TextElement::setUnderlined(bool underlined) {
    if (underlined) {
        sfText.setStyle(sfText.getStyle() | sf::Text::Underlined);
    } else {
        sfText.setStyle(sfText.getStyle() & ~sf::Text::Underlined);
    }
}

bool TextElement::loadFont(const std::string& fontPath) {
    std::cout << "[TextElement] loadFont() called but embedded font is used exclusively.\n";
    return false;
}

bool TextElement::loadSystemFont() {
    std::cout << "[TextElement] Loading embedded font from memory...\n";
    
    if (font == nullptr) {
        std::cout << "[TextElement] ERROR: Font pointer is null!\n";
        return false;
    }
    
    if (font->openFromMemory(fontData, fontData_len)) {
        fontLoaded = true;
        sfText.setFont(*font);
        std::cout << "[TextElement] Successfully loaded embedded font from memory!\n";
        return true;
    }
    
    std::cout << "[TextElement] ERROR: Failed to load embedded font from memory!\n";
    fontLoaded = false;
    return false;
}

void TextElement::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
    sfText.setPosition({static_cast<float>(newX), static_cast<float>(newY)});
}

sf::FloatRect TextElement::getBounds() const {
    return sfText.getGlobalBounds();
}

void TextElement::setAnimationStyle(TextAnimation type) {
    animationType = type;
    animationClock.restart();
    animationFrame = 0;
    
    baseText = text;
}


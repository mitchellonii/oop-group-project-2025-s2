#ifndef TEXTELEMENT_H
#define TEXTELEMENT_H

#include "RenderElement.h"
#include <SFML/Graphics.hpp>
#include <string>
#include "font_data.h"
enum class TextAnimation {
    None,
    Ellipsis
};

class TextElement : public RenderElement {
private:
    std::string text;
    sf::Font* font;
    sf::Text sfText;
    sf::Color textColor;
    unsigned int fontSize;
    bool fontLoaded;
    sf::Text::Style textStyle;
    TextAnimation animationType = TextAnimation::None;
    sf::Clock animationClock;
    int animationFrame = 0;
    std::string baseText;
    
public:
    TextElement();
    TextElement(const std::string& text, int x, int y, unsigned int fontSize = 24);
    TextElement(const std::string& text, int x, int y, unsigned int fontSize, sf::Color color);
    
    virtual ~TextElement();
    
    virtual void onMount() override;
    virtual void draw(sf::RenderWindow* globalWindow) override;
    
    void setText(const std::string& newText);
    std::string getText() const { return text; }
    
    void setColor(sf::Color color);
    void setFontSize(unsigned int size);
    void setStyle(sf::Text::Style style);
    void setBold(bool bold);
    void setItalic(bool italic);
    void setUnderlined(bool underlined);
    
    bool loadFont(const std::string& fontPath);
    bool loadSystemFont();  
    
    void setPosition(int newX, int newY);
    
    sf::FloatRect getBounds() const;
    bool isFontLoaded() const { return fontLoaded; }
    void setAnimationStyle(TextAnimation type);
};

#endif
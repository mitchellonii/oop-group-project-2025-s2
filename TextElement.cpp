#include "TextElement.h"

#include <iostream>

TextElement::TextElement() : RenderElement(), sfText(*new sf::Font()) {
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
  }
}

TextElement::TextElement(const std::string& text, int x, int y,
                         unsigned int fontSize)
    : RenderElement(), sfText(*new sf::Font()) {
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
  }
}

TextElement::TextElement(const std::string& text, int x, int y,
                         unsigned int fontSize, sf::Color color)
    : RenderElement(), sfText(*new sf::Font()) {
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
  }
}

TextElement::~TextElement() {
  if (font != nullptr) {
    delete font;
    font = nullptr;
  }
}

void TextElement::onMount() {
  if (!fontLoaded) {
    loadSystemFont();
  }
}

void TextElement::draw(sf::RenderWindow* globalWindow) {
  if (globalWindow == nullptr || !fontLoaded) {
    return;
  }

  if (animationType == TextAnimation::Ellipsis) {
    sf::Time elapsed = animationClock.getElapsedTime();

    if (elapsed.asMilliseconds() >= 300) {
      animationFrame = (animationFrame + 1) % 4;
      std::string dots(animationFrame, '.');
      sfText.setString(baseText + dots);
      animationClock.restart();
    }
  }

  if (!this->getIsHidden()) globalWindow->draw(sfText);

  sf::Vector2i pos = this->getPosition();
  sf::Vector2i box = this->getClickbox();

  sf::RectangleShape clickRect;
  clickRect.setPosition(
      sf::Vector2f(static_cast<float>(pos.x), static_cast<float>(pos.y)));
  clickRect.setSize(
      sf::Vector2f(static_cast<float>(box.x), static_cast<float>(box.y)));
  clickRect.setFillColor(sf::Color::Transparent);
  clickRect.setOutlineColor(sf::Color(0, 255, 0, 180));
  clickRect.setOutlineThickness(1.0f);

  globalWindow->draw(clickRect);
}

void TextElement::setText(const std::string& newText) {
  text = newText;
  sfText.setString(newText);
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

bool TextElement::loadFont(const std::string& fontPath) { return false; }

bool TextElement::loadSystemFont() {
  if (font == nullptr) {
    return false;
  }

  if (font->openFromMemory(fontData, fontData_len)) {
    fontLoaded = true;
    sfText.setFont(*font);
    return true;
  }

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

#include "ProgressBar.h"

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>

ProgressBar::ProgressBar(std::string imageFilePath, int x, int y, int width,
                         int height)
    : progressPercentage(0), width(width), height(height) {
  this->x = x;
  this->y = y;
  if (!texture.loadFromFile(imageFilePath)) {
  }
}

void ProgressBar::setProgress(int percentage) {
  progressPercentage = std::clamp(percentage, 0, 100);
}

void ProgressBar::draw(sf::RenderWindow* window) {
  const float insetX = 10.f;
  const float insetY = 3.f;

  float fillWidth = (width - 2 * insetX) * (progressPercentage / 100.f);
  float fillHeight = height - 2 * insetY;

  sf::RectangleShape fillRect(sf::Vector2f(fillWidth, fillHeight));
  fillRect.setPosition(
      {static_cast<float>(x) + insetX, static_cast<float>(y) + insetY});
  fillRect.setFillColor(sf::Color(235, 171, 52));

  if (!this->getIsHidden()) window->draw(fillRect);

  sf::Sprite outlineSprite(texture);
  outlineSprite.setPosition({static_cast<float>(x), static_cast<float>(y)});

  const auto texSize = texture.getSize();
  if (texSize.x > 0 && texSize.y > 0) {
    outlineSprite.setScale({static_cast<float>(width) / texSize.x,
                            static_cast<float>(height) / texSize.y});
  }

  if (!this->getIsHidden()) window->draw(outlineSprite);
}

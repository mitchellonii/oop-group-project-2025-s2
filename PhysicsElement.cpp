#include "PhysicsElement.h"

#include <iostream>
#include <string>

#include "RenderElement.h"

PhysicsElement::PhysicsElement() {};

PhysicsElement::PhysicsElement(std::string filePath, int posX, int posY,
                               int hitboxR)
    : hitboxRadius(hitboxR) {
  spriteFilepath = filePath;
  x = posX;
  y = posY;
  dx = 0;
  dy = 0;
};

void PhysicsElement::onMount() { return; }

void PhysicsElement::draw(sf::RenderWindow* globalWindow) {
  if (!globalWindow) {
    std::cout << "[RenderElement] ERROR: globalWindow is null.\n";
    return;
  }

  if (spriteFilepath.empty()) {
    std::cout << "[RenderElement] WARNING: spriteFilepath is empty, nothing to "
                 "draw.\n";
    return;
  }

  sf::Texture texture;
  if (!texture.loadFromFile(spriteFilepath)) {
    std::cout << "[RenderElement] ERROR: Failed to load texture from "
              << spriteFilepath << std::endl;
    return;
  }

  sf::Sprite sprite(texture);
  sprite.setPosition(
      sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
  if (lx > 0 && ly > 0) {
    sf::Vector2u texSize = texture.getSize();
    float scaleX = static_cast<float>(lx) / texSize.x;
    float scaleY = static_cast<float>(ly) / texSize.y;
    sprite.setScale(
        sf::Vector2f(static_cast<float>(scaleX), static_cast<float>(scaleY)));
  }

  globalWindow->draw(sprite);

  sf::RectangleShape clickRect;
  clickRect.setPosition(
      sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
  clickRect.setSize(
      sf::Vector2f(static_cast<float>(lx), static_cast<float>(ly)));
  clickRect.setFillColor(sf::Color::Transparent);

  clickRect.setOutlineColor(clickable ? sf::Color::Green : sf::Color::Red);
  clickRect.setOutlineThickness(1.0f);

  globalWindow->draw(clickRect);
}

void PhysicsElement::physicsTick() {
  x += dx;
  y += dy;
  const float damping = 0.97f;
  dx *= damping;
  dy *= damping;

  if (std::abs(dx) < 0.01f) dx = 0.0f;
  if (std::abs(dy) < 0.01f) dy = 0.0f;
  setPosition(x, y);
}

PhysicsElement::~PhysicsElement() { return; }

void PhysicsElement::setVelocity(double dxx, double dyy) {
  dx = dxx;
  dy = dyy;
}
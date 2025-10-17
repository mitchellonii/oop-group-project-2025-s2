#ifndef SCROLLINGBACKGROUND_H
#define SCROLLINGBACKGROUND_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>

#include "RenderElement.h"

class ScrollingBackground : public RenderElement {
 private:
  sf::Texture texture;
  std::unique_ptr<sf::Sprite> sprite1;
  std::unique_ptr<sf::Sprite> sprite2;

  float scrollSpeed;      // pixels per second
  bool horizontal;        // true = horizontal scroll
  float loopWidth;        // width of each sprite in pixels
  float scrollDirection;  // 1 = normal, -1 = reversed

 public:
  ScrollingBackground(std::string imageFilePath, float speed = 100.0f,
                      bool horizontalScroll = true,
                      float loopWidthOverride = 0.f, float direction = 1.0f);

  virtual ~ScrollingBackground() {}

  virtual void onMount() override;
  virtual void draw(sf::RenderWindow* globalWindow) override;
  void update(float deltaTime);

  // Optional: set direction dynamically
  void setDirection(float dir) { scrollDirection = dir; }
};

#endif

#include "ScrollingBackground.h"

ScrollingBackground::ScrollingBackground(std::string imageFilePath, float speed,
                                         bool horizontalScroll,
                                         float loopWidthOverride,
                                         float direction)
    : RenderElement(imageFilePath, 0, 0),
      scrollSpeed(speed),
      horizontal(horizontalScroll),
      loopWidth(loopWidthOverride),
      scrollDirection(direction) {}

void ScrollingBackground::onMount() {
  if (!texture.loadFromFile(spriteFilepath)) {
    return;
  }

  sprite1 = std::make_unique<sf::Sprite>(texture);
  sprite2 = std::make_unique<sf::Sprite>(texture);

  if (loopWidth <= 0.f)
    loopWidth = horizontal ? static_cast<float>(texture.getSize().x)
                           : static_cast<float>(texture.getSize().y);

  if (horizontal) {
    sprite1->setPosition({0.f, 0.f});
    sprite2->setPosition({loopWidth, 0.f});
  } else {
    sprite1->setPosition({0.f, 0.f});
    sprite2->setPosition({0.f, loopWidth});
  }
}

void ScrollingBackground::update(float deltaTime) {
  if (!sprite1 || !sprite2) return;

  float movement = scrollSpeed * deltaTime * scrollDirection;

  if (horizontal) {
    sprite1->move({movement, 0.f});
    sprite2->move({movement, 0.f});

    float sprite1X = sprite1->getPosition().x;
    float sprite2X = sprite2->getPosition().x;

    if (movement < 0) {
      if (sprite1X <= -loopWidth)
        sprite1->setPosition({sprite2X + loopWidth, 0.f});
      if (sprite2X <= -loopWidth)
        sprite2->setPosition({sprite1X + loopWidth, 0.f});
    } else {
      if (sprite1X >= loopWidth)
        sprite1->setPosition({sprite2X - loopWidth, 0.f});
      if (sprite2X >= loopWidth)
        sprite2->setPosition({sprite1X - loopWidth, 0.f});
    }
  } else {
    sprite1->move({0.f, movement});
    sprite2->move({0.f, movement});

    float sprite1Y = sprite1->getPosition().y;
    float sprite2Y = sprite2->getPosition().y;

    if (movement < 0) {
      if (sprite1Y <= -loopWidth)
        sprite1->setPosition({0.f, sprite2Y + loopWidth});
      if (sprite2Y <= -loopWidth)
        sprite2->setPosition({0.f, sprite1Y + loopWidth});
    } else {
      if (sprite1Y >= loopWidth)
        sprite1->setPosition({0.f, sprite2Y - loopWidth});
      if (sprite2Y >= loopWidth)
        sprite2->setPosition({0.f, sprite1Y - loopWidth});
    }
  }
}

void ScrollingBackground::draw(sf::RenderWindow* globalWindow) {
  if (!globalWindow) return;
  if (!sprite1 || !sprite2) return;

  float dt = 1.0f / 60.0f;
  update(dt);

  globalWindow->draw(*sprite1);
  globalWindow->draw(*sprite2);
}

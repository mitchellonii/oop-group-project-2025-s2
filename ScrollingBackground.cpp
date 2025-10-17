#include "ScrollingBackground.h"

ScrollingBackground::ScrollingBackground(std::string imageFilePath, float speed,
                                         bool horizontalScroll,
                                         float loopWidthOverride,
                                         float direction)
    : RenderElement(imageFilePath, 0, 0),
      scrollSpeed(speed),
      horizontal(horizontalScroll),
      loopWidth(loopWidthOverride),
      scrollDirection(direction) {
  std::cout << "[ScrollingBackground] Constructor: file=" << imageFilePath
            << ", speed=" << speed << ", horizontal=" << horizontal
            << ", loopWidth=" << loopWidth << ", direction=" << scrollDirection
            << std::endl;
}

void ScrollingBackground::onMount() {
  std::cout << "[ScrollingBackground] onMount() called." << std::endl;

  if (!texture.loadFromFile(spriteFilepath)) {
    std::cerr << "[ScrollingBackground] ERROR: Failed to load texture from "
              << spriteFilepath << std::endl;
    return;
  }

  // Create sprites after texture is loaded
  sprite1 = std::make_unique<sf::Sprite>(texture);
  sprite2 = std::make_unique<sf::Sprite>(texture);

  // Determine loop width based on texture size or override
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

  std::cout << "[ScrollingBackground] Sprites positioned. "
            << "Sprite1: (" << sprite1->getPosition().x << ", "
            << sprite1->getPosition().y << ") "
            << "Sprite2: (" << sprite2->getPosition().x << ", "
            << sprite2->getPosition().y << ")" << std::endl;
}

void ScrollingBackground::update(float deltaTime) {
  if (!sprite1 || !sprite2) return;

  float movement = scrollSpeed * deltaTime * scrollDirection;

  if (horizontal) {
    sprite1->move({movement, 0.f});
    sprite2->move({movement, 0.f});

    float sprite1X = sprite1->getPosition().x;
    float sprite2X = sprite2->getPosition().x;

    // Loop sprites smoothly
    if (movement < 0) {  // moving left
      if (sprite1X <= -loopWidth)
        sprite1->setPosition({sprite2X + loopWidth, 0.f});
      if (sprite2X <= -loopWidth)
        sprite2->setPosition({sprite1X + loopWidth, 0.f});
    } else {  // moving right
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

    if (movement < 0) {  // moving up
      if (sprite1Y <= -loopWidth)
        sprite1->setPosition({0.f, sprite2Y + loopWidth});
      if (sprite2Y <= -loopWidth)
        sprite2->setPosition({0.f, sprite1Y + loopWidth});
    } else {  // moving down
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

  // Update scroll on every draw call
  float dt = 1.0f / 60.0f;  // approximate frame time
  update(dt);

  globalWindow->draw(*sprite1);
  globalWindow->draw(*sprite2);

  // Debug positions
  std::cout << "[ScrollingBackground] draw() called. "
            << "Sprite1 Pos: (" << sprite1->getPosition().x << ", "
            << sprite1->getPosition().y << ") "
            << "Sprite2 Pos: (" << sprite2->getPosition().x << ", "
            << sprite2->getPosition().y << ")" << std::endl;
}

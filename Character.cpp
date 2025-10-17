#include "Character.h"

#include <iostream>

Character::Character()
    : PhysicsElement(),
      isWalkingLeft(false),
      isWalkingRight(false),
      isFacingRight(true),
      currentFrame(0),
      frameDuration(0.12f),
      animationTimer(0.0f) {}

Character::Character(const std::string& imageFilePath, int xPos, int yPos,
                     int hitboxR, const std::vector<std::string>& walkLeftPaths,
                     const std::vector<std::string>& walkRightPaths,
                     float frameDurationSec)
    : PhysicsElement(imageFilePath, xPos, yPos, hitboxR),
      isWalkingLeft(false),
      isWalkingRight(false),
      isFacingRight(true),
      currentFrame(0),
      frameDuration(frameDurationSec),
      animationTimer(0.0f) {
  walkLeftFrames.reserve(walkLeftPaths.size());
  walkRightFrames.reserve(walkRightPaths.size());

  for (const auto& path : walkLeftPaths) {
    auto tex = std::make_shared<sf::Texture>();
    if (!tex->loadFromFile(path)) {
      std::cerr << "Failed to load left frame: " << path << std::endl;
    }
    walkLeftFrames.push_back(tex);
  }

  for (const auto& path : walkRightPaths) {
    auto tex = std::make_shared<sf::Texture>();
    if (!tex->loadFromFile(path)) {
      std::cerr << "Failed to load right frame: " << path << std::endl;
    }
    walkRightFrames.push_back(tex);
  }
}

void Character::onMount() { PhysicsElement::onMount(); }

void Character::physicsTick() {
  x += dx;
  y += dy;

  const float damping = 0.99f;
  dx *= damping;
  dy *= damping;

  if (std::abs(dx) < 0.01f) dx = 0.0f;
  if (std::abs(dy) < 0.01f) dy = 0.0f;
  setPosition(x, y);

  if (x < 100) {
    x = 100;
    dx = -dx * 0.5f;
  }
  if (x > 800 - this->hitboxRadius * 2) {
    x = 800 - this->hitboxRadius * 2;
    dx = -dx * 0.5f;
  }
}

void Character::draw(sf::RenderWindow* globalWindow) {
  if (!globalWindow) return;

  float delta = animationClock.restart().asSeconds();
  animationTimer += delta;

  const auto& frames = isFacingRight ? walkRightFrames : walkLeftFrames;
  bool isMoving = (dx != 0 || dy != 0);
  if ((isWalkingLeft || isWalkingRight || isMoving) && !frames.empty() &&
      isMoving == true) {
    if (animationTimer >= frameDuration) {
      animationTimer = 0.f;
      currentFrame = (currentFrame + 1) % static_cast<int>(frames.size());
    }
  } else {
    currentFrame = 0;  // idle
  }

  if (frames.empty() || !frames[currentFrame]) return;

  sf::Sprite sprite(*frames[currentFrame]);
  sprite.setPosition({static_cast<float>(x), static_cast<float>(y)});

  globalWindow->draw(sprite);
}

void Character::moveLeft() {
  isWalkingLeft = true;
  isWalkingRight = false;
  isFacingRight = false;
  this->setVelocity(-10, dy);
}

void Character::moveRight() {
  isWalkingRight = true;
  isWalkingLeft = false;
  isFacingRight = true;
  this->setVelocity(10, dy);
}

void Character::stop() {
  isWalkingLeft = false;
  isWalkingRight = false;
  this->setVelocity(0, dy);
}

void Character::handleInput() {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
    this->moveLeft();
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
    this->moveRight();
  } else {
    stop();
  }
}
bool Character::hasItem() const { return !heldItem.empty(); }

std::string Character::getHeldItem() const { return heldItem; }

void Character::setHeldItem(const std::string& itemName) {
  heldItem = itemName;
}

void Character::clearHeldItem() { heldItem.clear(); }

Character::~Character() = default;

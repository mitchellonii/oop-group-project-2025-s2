#include "Character.h"

#include <iostream>

#include "GameController.h"
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
                     float frameDurationSec, GameController* c)
    : PhysicsElement(imageFilePath, xPos, yPos, hitboxR),
      isWalkingLeft(false),
      isWalkingRight(false),
      isFacingRight(true),
      currentFrame(0),
      controller(c),
      heldItem("none"),
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

  if (x < 180) {
    x = 180;
    dx = -dx * 0.5f;
  }
  if (x > 780 - this->hitboxRadius * 2) {
    x = 780 - this->hitboxRadius * 2;
    dx = -dx * 0.5f;
  }

  if (this->heldItem == "toolbox") {
    controller->getToolbox()->setPosition(x + 30, 250);
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
  // Log start of input handling
  std::cout << "[DEBUG] Handling input for Character at position x=" << x
            << ", heldItem=" << heldItem << std::endl;

  // Movement input
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
    std::cout << "[DEBUG] Key A pressed -> Moving Left" << std::endl;
    this->moveLeft();
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
    std::cout << "[DEBUG] Key D pressed -> Moving Right" << std::endl;
    this->moveRight();
  } else {
    std::cout << "[DEBUG] No horizontal key pressed -> Stopping" << std::endl;
    stop();
  }

  // Interaction input
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
    std::cout << "[DEBUG] Key E pressed -> Attempting interaction" << std::endl;

    int currentTaskId = controller->getCurrentTask()
                            ? controller->getCurrentTask()->getTaskId()
                            : -1;

    if (240 < x && x < 320 && currentTaskId == 1 && this->heldItem == "none") {
      this->heldItem = "toolbox";
      std::cout << "[DEBUG] Picked up toolbox!" << std::endl;
    } else if (this->heldItem == "toolbox" && currentTaskId == 1 && x > 650) {
      std::cout << "placed toolbox down in acceptable location" << std::endl;
      this->heldItem = "none";
      controller->getToolbox()->setPosition(287, 390);
      controller->getCurrentTask()->complete();
    } else {
      std::cout << "[DEBUG] Interaction failed: conditions not met"
                << std::endl;
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
    std::string currentTaskDir = controller->getCurrentTask()->getDirection();
    int currentTaskId = controller->getCurrentTask()
                            ? controller->getCurrentTask()->getTaskId()
                            : -1;

    if (x < 200 && currentTaskId == 2 && this->heldItem == "none" &&
        currentTaskDir == "up") {
      std::cout << "fixed navs" << std::endl;
      controller->getCurrentTask()->complete();
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
    std::string currentTaskDir = controller->getCurrentTask()->getDirection();
    int currentTaskId = controller->getCurrentTask()
                            ? controller->getCurrentTask()->getTaskId()
                            : -1;

    if (x < 200 && currentTaskId == 2 && this->heldItem == "none" &&
        currentTaskDir == "down") {
      std::cout << "fixed navs" << std::endl;
      controller->getCurrentTask()->complete();
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
    std::string currentTaskDir = controller->getCurrentTask()->getDirection();
    int currentTaskId = controller->getCurrentTask()
                            ? controller->getCurrentTask()->getTaskId()
                            : -1;

    if (x < 200 && currentTaskId == 2 && this->heldItem == "none" &&
        currentTaskDir == "left") {
      std::cout << "fixed navs" << std::endl;
      controller->getCurrentTask()->complete();
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
    std::string currentTaskDir = controller->getCurrentTask()->getDirection();
    int currentTaskId = controller->getCurrentTask()
                            ? controller->getCurrentTask()->getTaskId()
                            : -1;

    if (x < 200 && currentTaskId == 2 && this->heldItem == "none" &&
        currentTaskDir == "right") {
      std::cout << "fixed navs" << std::endl;
      controller->getCurrentTask()->complete();
    }
  }

  // Log end of input handling
  std::cout << "[DEBUG] Input handling complete for Character. Current state: "
            << "x=" << x << ", heldItem=" << heldItem << std::endl;
}

bool Character::hasItem() const { return !heldItem.empty(); }

std::string Character::getHeldItem() const { return heldItem; }

void Character::setHeldItem(const std::string& itemName) {
  heldItem = itemName;
}

void Character::clearHeldItem() { heldItem.clear(); }

Character::~Character() = default;

#ifndef CHARACTER_H
#define CHARACTER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

#include "PhysicsElement.h"

class GameController;

class Character : public PhysicsElement {
 private:
  bool isWalkingLeft;
  bool isWalkingRight;
  bool isFacingRight;
  GameController* controller;
  std::vector<std::shared_ptr<sf::Texture>> walkLeftFrames;
  std::vector<std::shared_ptr<sf::Texture>> walkRightFrames;

  int currentFrame;
  float frameDuration;
  float animationTimer;

  sf::Clock animationClock;

  std::string heldItem;

 public:
  Character();
  void handleInput();
  Character(const std::string& imageFilePath, int x, int y, int hitboxR,
            const std::vector<std::string>& walkLeftPaths,
            const std::vector<std::string>& walkRightPaths,
            float frameDurationSec, GameController* controller);

  void onMount() override;
  void physicsTick() override;
  void draw(sf::RenderWindow* globalWindow) override;

  void moveLeft();
  void moveRight();
  void stop();

  bool hasItem() const;
  std::string getHeldItem() const;
  void setHeldItem(const std::string& itemName);
  void clearHeldItem();

  ~Character() override;
};

#endif

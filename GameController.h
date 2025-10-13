#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "PhysicsElement.h"
#include "RenderElement.h"

class GameController {
 private:
  std::vector<RenderElement*> renderables;
  std::vector<PhysicsElement*> physicsItems;

  sf::RenderWindow* globalWindow;
  bool runinng;

 public:
  GameController();
  ~GameController();

  void init();
  void physicsTick();
  void drawAll();
  void run();
  void stop();

  int mountRenderable(RenderElement* element);
  int mountPhysicsElement(PhysicsElement* element);

  bool dismountRenderable(int index);
  bool dismountRenderable(const RenderElement* element);
  bool dismountPhysicsElement(int index);

  void clearAllRenderables();
  void clearAllPhysicsElements();
  void clearAll();

  RenderElement* getRenderableAt(int index);
  PhysicsElement* getPhysicsElementAt(int index);
};

#endif

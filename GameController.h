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
  PhysicsElement* cargo1;
  PhysicsElement* cargo2;
  PhysicsElement* cargo3;
  RenderElement* navComputer;
  RenderElement* toolbox;
  RenderElement* handrail;
  int cargosRemaining;
  sf::RenderWindow* globalWindow;
  bool runinng;
  int currentTaskIndex;
  int currentTaskFramesRemaining;

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

  void setCargos(PhysicsElement* c1, PhysicsElement* c2, PhysicsElement* c3);
  void removeCargo();
  void clearAllRenderables();
  void clearAllPhysicsElements();
  void clearAll();

  void setNavComputer(RenderElement* nav);
  void setToolbox(RenderElement* box);
  void setHandrail(RenderElement* rail);

  RenderElement* getRenderableAt(int index);
  PhysicsElement* getPhysicsElementAt(int index);
};

#endif

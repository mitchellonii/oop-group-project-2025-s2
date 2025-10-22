#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "PhysicsElement.h"
#include "RenderElement.h"
#include "Task.h"
#include "TextElement.h"

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
  bool dismountAllRenderableNextFrame;
  bool dismountAllPhysicsNextFrame;
  bool won;
  bool hasTask;
  Task* currentTask;
  bool gameStarted;
  int framesRemaining;
  TextElement* countdown;
  bool countdownExists;
  bool lost;

 public:
  GameController();
  ~GameController();

  void init();
  void physicsTick();
  void drawAll();
  void run();
  void stop();
  void setWon(bool w);
  int mountRenderable(RenderElement* element);
  int mountPhysicsElement(PhysicsElement* element);
  int getFramesRemaining();
  void setFramesRemaining(int h);
  bool getGameStarted();
  void setGameStarted(bool g);
  bool dismountRenderable(const RenderElement* element);
  bool dismountRenderable(int index);
  int frameCounter;
  bool getHasTask();
  Task* getCurrentTask();
  void setCurrentTask(Task* h);
  void setHasTask(bool t);

  RenderElement* getToolbox();
  bool dismountPhysicsElement(int index);
  void setLost(bool l);
  void setCargos(PhysicsElement* c1, PhysicsElement* c2, PhysicsElement* c3);
  void removeCargo();
  void clearAllRenderables();
  void clearAllPhysicsElements();
  void clearAll();
  void setCountdown(TextElement* a);
  void setNavComputer(RenderElement* nav);
  void setToolbox(RenderElement* box);
  void setHandrail(RenderElement* rail);

  RenderElement* getRenderableAt(int index);
  PhysicsElement* getPhysicsElementAt(int index);
};

#endif
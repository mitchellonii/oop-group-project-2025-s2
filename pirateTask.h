#ifndef PIRATE_T_H
#define PIRATE_T_H
#include <string>

#include "PhysicsElement.h"
#include "RenderElement.h"
#include "Task.h"
#include "TextElement.h"
using namespace std;
class GameController;
class pirateTask : public Task {
 private:
  string type;
  TextElement* alert;
  RenderElement* box;
  RenderElement* ship;
  RenderElement* pirate;

 public:
  pirateTask(int timeTaken, string type, int taskId,
             GameController* controller);
  void tick() override;
  void complete() override;
  virtual std::string getType() override;
};

#endif
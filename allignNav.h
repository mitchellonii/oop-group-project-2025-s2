#ifndef ALIGN_H
#define ALIGN_H
#include <string>

#include "RenderElement.h"
#include "Task.h"
#include "TextElement.h"
using namespace std;
class GameController;
class allignNav : public Task {
 private:
  string direction;
  TextElement* alert;
  RenderElement* box;

 public:
  allignNav(int timeTaken, string direction, int taskId,
            GameController* controller);
  void tick() override;
  void complete() override;
  virtual std::string getDirection() override;
};

#endif
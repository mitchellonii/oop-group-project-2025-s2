#ifndef RAILFIX_H
#define RAILFIX_H
#include <string>

#include "GameController.h"
#include "RenderElement.h"
#include "Task.h"
#include "TextElement.h"
using namespace std;

class railFix : public Task {
 private:
  string necessaryTool;
  TextElement* alert;
  RenderElement* box;

 public:
  railFix(int timeTaken, bool necessaryTool, int taskId,
          GameController* controller);
  void fixRail();
  void tick() override;
  void complete() override;
};

#endif
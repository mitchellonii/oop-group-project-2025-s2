#include "railFix.h"

#include <iostream>

#include "GameController.h"
#include "ProgressBar.h"
#include "RenderElement.h"
#include "TextElement.h"
railFix::railFix(int time, bool tool, int taskId, GameController* controller)
    : Task(taskId, time, tool, controller) {
  RenderElement* b = new RenderElement("assets/Text_box_resized.png", 500, 40);
  box = b;
  controller->mountRenderable(box);

  TextElement* a = new TextElement("Fix the rail", 525, 40);
  alert = a;
  TextElement* c = new TextElement("Press e to interact", 525, 65);
  c->setFontSize(12);
  alert2 = c;

  controller->mountRenderable(alert);
  controller->mountRenderable(alert2);
  alert->setBlinking(true);
  alert2->setBlinking(true);
  alert->setAnimationStyle(TextAnimation::Ellipsis);

  ProgressBar* progressBar =
      new ProgressBar("assets/progress_bar.png", 300, 40, 200, 20);
  progressBar->setProgress(0);
  progress = progressBar;
  controller->mountRenderable(progress);
}

void railFix::tick() {
  if (ticksRemaining <= 0) {
    return;
  }

  ticksRemaining--;

  float progressPercent = 1.0f - (static_cast<float>(ticksRemaining) /
                                  static_cast<float>(this->timeTaken * 30));
  progress->setProgress(static_cast<int>(progressPercent * 100));
}

void railFix::complete() {
  progress->setHidden(true);
  alert->setHidden(true);
  box->setHidden(true);
  alert2->setHidden(true);
  this->completed = true;
}

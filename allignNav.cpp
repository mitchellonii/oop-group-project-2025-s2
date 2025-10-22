#include "allignNav.h"

#include <iostream>

#include "GameController.h"
#include "ProgressBar.h"
#include "RenderElement.h"
#include "TextElement.h"
allignNav::allignNav(int time, string direction, int taskId,
                     GameController* controller)
    : Task(taskId, time, "null", controller) {
  this->direction = direction;
  RenderElement* b = new RenderElement("assets/Text_box_resized.png", 500, 40);
  box = b;
  controller->mountRenderable(box);

  TextElement* a = new TextElement("Allign navs: " + direction, 525, 45);
  a->setFontSize(20);
  alert = a;

  controller->mountRenderable(alert);
  alert->setBlinking(true);
  alert->setAnimationStyle(TextAnimation::None);

  ProgressBar* progressBar =
      new ProgressBar("assets/progress_bar.png", 300, 40, 200, 20);
  progressBar->setProgress(0);
  progress = progressBar;
  controller->mountRenderable(progress);
}

void allignNav::tick() {
  if (ticksRemaining <= 0) {
    return;
  }

  ticksRemaining--;

  float progressPercent = 1.0f - (static_cast<float>(ticksRemaining) /
                                  static_cast<float>(this->timeTaken * 30));
  progress->setProgress(static_cast<int>(progressPercent * 100));
}

void allignNav::complete() {
  progress->setHidden(true);
  alert->setHidden(true);
  box->setHidden(true);
  this->completed = true;
}

std::string allignNav::getDirection() { return direction; };
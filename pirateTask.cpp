#include "pirateTask.h"

#include <iostream>

#include "GameController.h"
#include "ProgressBar.h"
#include "RenderElement.h"
#include "TextElement.h"
// Call the parent constructor with all three parameters
pirateTask::pirateTask(int time, string type, int taskId,
                       GameController* controller)
    : Task(taskId, time, "null", controller) {
  this->type = type;
  RenderElement* b = new RenderElement("assets/Text_box_resized.png", 500, 40);
  box = b;
  controller->mountRenderable(box);

  TextElement* a = new TextElement("Pirate encounter", 525, 45);
  alert = a;

  controller->mountRenderable(alert);
  alert->setBlinking(true);
  alert->setAnimationStyle(TextAnimation::Ellipsis);

  ProgressBar* progressBar =
      new ProgressBar("assets/progress_bar.png", 300, 40, 200, 20);
  progressBar->setProgress(0);
  progress = progressBar;
  controller->mountRenderable(progress);

  RenderElement* s = new RenderElement(
      "assets/" + this->type + "_pirate_ship_400w.png", 700, -150);
  ship = s;
  controller->mountRenderable(ship);

  RenderElement* p = new RenderElement("assets/Pirate_resized.png", 528, 263);
  pirate = p;

  pirate->setHidden(true);
  controller->mountRenderable(pirate);
}

void pirateTask::tick() {
  if (ticksRemaining <= 0) {
    return;  // Task complete
  }

  if (ticksRemaining > (this->timeTaken * 30 - 80)) {
    sf::Vector2i pos = ship->getPosition();
    ship->setPosition(pos.x - 2, pos.y + 1);
  } else {
    if (pirate->getIsHidden()) pirate->setHidden(false);
  }

  ticksRemaining--;

  // Calculate progress as percentage (0.0 to 1.0)
  float progressPercent = 1.0f - (static_cast<float>(ticksRemaining) /
                                  static_cast<float>(this->timeTaken * 30));
  progress->setProgress(static_cast<int>(progressPercent * 100));
}

void pirateTask::complete() {
  progress->setHidden(true);
  alert->setHidden(true);
  box->setHidden(true);
  ship->setHidden(true);
  pirate->setHidden(true);
  this->completed = true;
}

std::string pirateTask::getType() { return type; };
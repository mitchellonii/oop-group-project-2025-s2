#include "pirateTask.h"

#include <iostream>

#include "GameController.h"
#include "ProgressBar.h"
#include "RenderElement.h"
#include "Sound.h"
#include "TextElement.h"
pirateTask::pirateTask(int time, string type, int taskId,
                       GameController* controller)
    : Task(taskId, time, "null", controller) {
  currentSelected = 1;
  this->type = type;
  RenderElement* b = new RenderElement("assets/Text_box_resized.png", 500, 40);
  box = b;
  controller->mountRenderable(box);

  TextElement* a = new TextElement("Pirate encounter", 525, 45);
  a->setFontSize(20);
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

  TextElement* empathy = new TextElement("Beg for mercy", 370, 430);
  TextElement* insult = new TextElement("Insult them", 180, 430);
  TextElement* bribe = new TextElement("Pay money", 590, 430);
  RenderElement* b1 =
      new RenderElement("assets/Text_box_resized.png", 150, 420);
  RenderElement* b2 =
      new RenderElement("assets/Text_box_resized.png", 350, 420);
  RenderElement* b3 =
      new RenderElement("assets/Text_box_resized.png", 550, 420);

  text1 = empathy;
  text2 = insult;
  text3 = bribe;
  box1 = b1;
  box2 = b2;
  box3 = b3;

  box1->setClickable(true);
  box1->setClickboxSize(179, 47);
  box2->setClickable(true);
  box2->setClickboxSize(179, 47);
  box3->setClickable(true);
  box3->setClickboxSize(179, 47);

  box1->setOnClickCallback([type, this]() {
    if (type == "insecure")
      this->complete();
    else
      this->ticksRemaining = 1;
  });
  box2->setOnClickCallback([type, this]() {
    if (type == "empathetic")
      this->complete();
    else
      this->ticksRemaining = 1;
  });
  box3->setOnClickCallback([type, this]() {
    if (type == "money")
      this->complete();
    else
      this->ticksRemaining = 1;
  });

  controller->mountRenderable(box1);
  controller->mountRenderable(box2);
  controller->mountRenderable(box3);
  controller->mountRenderable(text1);
  controller->mountRenderable(text2);
  controller->mountRenderable(text3);
  box1->setHidden(true);
  box2->setHidden(true);
  box3->setHidden(true);
  text1->setHidden(true);
  text2->setHidden(true);
  text3->setHidden(true);

  MusicTrack* m = new MusicTrack();
  m->openFromFile("assets/arrival.mp3");
  m->play();
}

void pirateTask::tick() {
  if (ticksRemaining <= 0) {
    return;
  }

  if (ticksRemaining > (this->timeTaken * 30 - 80)) {
    sf::Vector2i pos = ship->getPosition();
    ship->setPosition(pos.x - 2, pos.y + 1);
  } else {
    if (pirate->getIsHidden()) {
      if (ticksRemaining > this->timeTaken * 30 - 100) {
        MusicTrack* m = new MusicTrack();
        m->openFromFile("assets/yar.mp3");
        m->play();
      }
      pirate->setHidden(false);
      box1->setHidden(false);
      box2->setHidden(false);
      box3->setHidden(false);
      text1->setHidden(false);
      text2->setHidden(false);
      text3->setHidden(false);
    }
  }

  ticksRemaining--;

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
  box1->setHidden(true);
  box2->setHidden(true);
  box3->setHidden(true);
  text1->setHidden(true);
  text2->setHidden(true);
  text3->setHidden(true);

  this->completed = true;
}

std::string pirateTask::getType() { return type; };
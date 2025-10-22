#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Character.h"
#include "CountdownText.h"
#include "GameController.h"
#include "PhysicsElement.h"
#include "ProgressBar.h"
#include "RenderElement.h"
#include "ScrollingBackground.h"
#include "Sound.h"
#include "TextElement.h"

int main() {
  GameController engine;

  engine.init();

  ScrollingBackground* wallpaper =
      new ScrollingBackground("assets/bg.jpg", 10, true, 900, -1.0f);
  wallpaper->onMount();
  engine.mountRenderable(wallpaper);

  RenderElement* button =
      new RenderElement("assets/Text_box_tall.png", 350, 400);
  engine.mountRenderable(button);

  RenderElement* title =
      new RenderElement("assets/Spacefairer_title_resized.png", 300, 150);
  engine.mountRenderable(title);

  TextElement* instructionText =
      new TextElement("Click to Start", 385, 395, 20, sf::Color::White);
  instructionText->setBold(true);
  engine.mountRenderable(instructionText);

  button->setClickable(true);
  button->setClickboxSize(200, 20);

  std::vector<std::string> leftFrames = {
      "assets/RoggertWalkLeft/frame1_scaled.png",
      "assets/RoggertWalkLeft/frame2_scaled.png",
      "assets/RoggertWalkLeft/frame3_scaled.png",
      "assets/RoggertWalkLeft/frame4_scaled.png",
      "assets/RoggertWalkLeft/frame5_scaled.png",
      "assets/RoggertWalkLeft/frame6_scaled.png",
      "assets/RoggertWalkLeft/frame7_scaled.png",
      "assets/RoggertWalkLeft/frame8_scaled.png"};

  std::vector<std::string> rightFrames = {
      "assets/RoggertWalkRight/frame1_scaled.png",
      "assets/RoggertWalkRight/frame2_scaled.png",
      "assets/RoggertWalkRight/frame3_scaled.png",
      "assets/RoggertWalkRight/frame4_scaled.png",
      "assets/RoggertWalkRight/frame5_scaled.png",
      "assets/RoggertWalkRight/frame6_scaled.png",
      "assets/RoggertWalkRight/frame7_scaled.png",
      "assets/RoggertWalkRight/frame8_scaled.png"};

  Character* player =
      new Character("assets/RoggertWalkRight/Rog_walk_right_frame-1.png", 100,
                    230, 50, leftFrames, rightFrames, 0.1f, &engine);

  GameController* enginePtr = &engine;

  button->setOnClickCallback([button, enginePtr, wallpaper, title, player]() {
    enginePtr->dismountRenderable(title);
    enginePtr->dismountRenderable(wallpaper);

    RenderElement* countdownBG =
        new RenderElement("assets/text-display-diegetic_scaled.png", 390, 45);

    TextElement* countdown =
        new TextElement("Distance travelled: 0%", 522, 180, 20);

    ScrollingBackground* bgGame = new ScrollingBackground(
        "assets/Spacefairer_background_scaled.png", 50, true, 5625, 1.0f);
    RenderElement* ship =
        new RenderElement("assets/Bongo_Frontier_900.png", 0, 70);
    RenderElement* computer =
        new RenderElement("assets/CourseCorrectComputer_225.png", 4, 325);
    PhysicsElement* cargo1 =
        new PhysicsElement("assets/CargoCrate_140.png", 800, 370, 10);
    PhysicsElement* cargo2 =
        new PhysicsElement("assets/CargoCrate_140.png", 800, 315, 10);
    PhysicsElement* cargo3 =
        new PhysicsElement("assets/CargoCrate_140.png", 800, 260, 10);
    RenderElement* Toolbox =
        new RenderElement("assets/Toolbox_70.png", 287, 390);
    RenderElement* Handrail =
        new RenderElement("assets/Handrail_70.png", 720, 320);

    bgGame->onMount();
    enginePtr->mountRenderable(bgGame);
    enginePtr->mountRenderable(ship);
    enginePtr->mountRenderable(countdownBG);

    enginePtr->mountRenderable(countdown);

    enginePtr->mountRenderable(computer);
    enginePtr->mountPhysicsElement(cargo1);
    enginePtr->mountPhysicsElement(cargo2);
    enginePtr->mountPhysicsElement(cargo3);
    enginePtr->setCargos(cargo1, cargo2, cargo3);
    enginePtr->setHandrail(Handrail);
    enginePtr->setNavComputer(computer);
    enginePtr->setToolbox(Toolbox);
    enginePtr->mountRenderable(Handrail);
    enginePtr->mountPhysicsElement(player);
    enginePtr->mountRenderable(Toolbox);

    enginePtr->dismountRenderable(button);

    enginePtr->setCountdown(countdown);

    std::cout << "[Main] Countdown set at address: " << countdown << std::endl;

    enginePtr->setGameStarted(true);
  });

  engine.run();
  return 0;
}
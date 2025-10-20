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

  // Initial background and title
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

  MusicTrack* audio = new MusicTrack();
  audio->openFromFile("assets/music.ogg");
  audio->play();
  audio->setLoop(true);

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
                    200, 50, leftFrames, rightFrames, 0.1f);

  button->setOnClickCallback([&button, &engine, &audio, &wallpaper, &title,
                              &player]() {
    // Remove start screen
    engine.dismountRenderable(title);
    engine.dismountRenderable(wallpaper);
    audio->stop();

    // Countdown background
    RenderElement* countdownBG =
        new RenderElement("assets/text-display-diegetic_scaled.png", 390, 45);

    // Countdown
    CountdownText* countdown = new CountdownText(522, 180, 20);

    // "YOU WON" text (not yet mounted)
    TextElement* youWonText =
        new TextElement("YOU WON!", 350, 250, 50, sf::Color::Yellow);
    youWonText->setBold(true);

    // Game background and elements
    ScrollingBackground* bgGame = new ScrollingBackground(
        "assets/Spacefairer_background_scaled.png", 50, true, 5625, 1.0f);
    RenderElement* ship =
        new RenderElement("assets/Bongo_Frontier_900.png", 0, 70);
    RenderElement* computer =
        new RenderElement("assets/CourseCorrectComputer_225.png", 4, 325);
    computer->setBlinking(true);
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
    ProgressBar* progressBar =
        new ProgressBar("assets/progress_bar.png", 300, 40, 200, 20);
    progressBar->setProgress(45);

    // Mount everything
    bgGame->onMount();
    engine.mountRenderable(bgGame);
    engine.mountRenderable(ship);
    engine.mountRenderable(countdownBG);
    engine.mountRenderable(countdown);
    engine.mountRenderable(computer);
    engine.mountPhysicsElement(cargo1);
    engine.mountPhysicsElement(cargo2);
    engine.mountPhysicsElement(cargo3);
    engine.setCargos(cargo1, cargo2, cargo3);
    engine.setHandrail(Handrail);
    engine.setNavComputer(computer);
    engine.setToolbox(Toolbox);
    engine.mountRenderable(Toolbox);
    engine.mountRenderable(Handrail);
    engine.mountPhysicsElement(player);
    engine.mountRenderable(progressBar);

    // Remove start button
    engine.dismountRenderable(button);

    // COUNTDOWN END CALLBACK AT THE VERY BOTTOM
    countdown->setCountdownEndCallback(
        [&engine, &bgGame, &ship, &countdownBG, &countdown, &computer, &cargo1,
         &cargo2, &cargo3, &Toolbox, &Handrail, &player, &progressBar,
         &youWonText](CountdownText* ct) {
          // Remove each element individually
          engine.dismountRenderable(ship);
          // engine.dismountRenderable(countdown);
          engine.dismountRenderable(computer);

          engine.dismountRenderable(Toolbox);
          engine.dismountRenderable(Handrail);
          engine.dismountRenderable(progressBar);

          // Show "YOU WON"
          engine.mountRenderable(youWonText);
        });
  });

  engine.run();
  return 0;
}

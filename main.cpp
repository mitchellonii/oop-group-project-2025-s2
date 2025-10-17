#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Character.h"
#include "CountdownText.h"
#include "GameController.h"
#include "PhysicsElement.h"
#include "RenderElement.h"
#include "ScrollingBackground.h"
#include "Sound.h"
#include "TextElement.h"
int main() {
  GameController engine;

  engine.init();
  RenderElement* wallpaper = new RenderElement("assets/bg.jpg", 0, 0);
  engine.mountRenderable(wallpaper);

  RenderElement* button = new RenderElement("assets/button.jpg", 350, 400);
  engine.mountRenderable(button);

  TextElement* title = new TextElement("Spacefairer", 370, 100, 40);
  engine.mountRenderable(title);

  MusicTrack* audio = new MusicTrack();
  audio->openFromFile("assets/music.ogg");
  audio->play();
  audio->setLoop(true);

  title->setBold(true);
  title->setAnimationStyle(TextAnimation::Ellipsis);

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
    engine.dismountRenderable(title);
    engine.dismountRenderable(wallpaper);
    audio->stop();
    RenderElement* countdownBG =
        new RenderElement("assets/text-display-diegetic_scaled.png", 390, 45);
    CountdownText* countdown = new CountdownText(400, 50, 30);
    ScrollingBackground* wallpaper =
        new ScrollingBackground("assets/Spacefairer_background_scaled.png",
                                50,    // speed
                                true,  // horizontal
                                5625,  // loop width
                                1.0f  // scroll direction: negative = move right
        );
    RenderElement* ship =
        new RenderElement("assets/Bongo_Frontier_900.png", 0, 0);
    wallpaper->onMount();
    engine.mountRenderable(wallpaper);
    engine.mountRenderable(ship);
    engine.mountRenderable(countdownBG);
    engine.mountRenderable(countdown);
    engine.mountPhysicsElement(player);

    // must be at end of callback. cannot remove self mid-callback
    engine.dismountRenderable(button);
  });

  engine.run();
  return 0;
}

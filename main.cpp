#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "Character.h"
#include "CountdownText.h"
#include "GameController.h"
#include "PhysicsElement.h"
#include "RenderElement.h"
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

  std::vector<std::string> leftFrames = {"assets/smileyface.jpg"};
  std::vector<std::string> rightFrames = {"assets/smileyface.jpg"};
  Character* player = new Character("assets/smileyface.jpg", 100, 300, 50,
                                    leftFrames, rightFrames, 0.1f);

  button->setOnClickCallback(
      [&button, &engine, &audio, &wallpaper, &title, &player]() {
        engine.dismountRenderable(title);
        engine.dismountRenderable(wallpaper);
        audio->stop();
        engine.mountPhysicsElement(player);

        // must be at end of callback. cannot remove self mid-callback
        engine.dismountRenderable(button);
      });

  engine.run();
  return 0;
}

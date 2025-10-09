#include <SFML/Graphics.hpp>

#include "GameController.h"
#include "PhysicsElement.h"
#include "RenderElement.h"
#include "TextElement.h"
#include "CountdownText.h"
#include <iostream>
int main()
{
    GameController engine;

    engine.init();

    TextElement* text = new TextElement();
    
    text->setText("If you see this, rendering is working");
    text->setColor(sf::Color::Green);
    text->setBold(true);
    text->setPosition(100, 100);
    text->setFontSize(15);
    text->setAnimationStyle(TextAnimation::Ellipsis);
    //text class listens for keyboard events (TextElement.cpp). output in console

    engine.mountRenderable(text);//add text to the render loop
    
    CountdownText* countdown = new CountdownText(250, 200, 72);
    int countdownTextID = engine.mountRenderable(countdown);//add countdown text to the render loop. store ID for removal at a later time

    countdown->setDismountCallback([&engine, countdownTextID, text](CountdownText* obj) {//called after the time left reaches 0
        engine.dismountRenderable(countdownTextID);//remove text from scene
        text->setText("Woah");
        text->setAnimationStyle(TextAnimation::None);
        text->setColor(sf::Color::Yellow);
    });


    engine.run();// engine.run blocks execution until program exited

    //nothing here will run until engine.run() has finshed (ie. program window is closed)
    //nothing should go here

    return 0;
}

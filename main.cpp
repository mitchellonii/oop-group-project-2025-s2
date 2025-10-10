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

    sf::Keyboard::Key keyA = sf::Keyboard::Key::A;
    const sf::Keyboard::Key* keys[] = { &keyA};

    text->setKeyboardEventListners(keys, 1);

    text->setKeyPressCallback([&text](sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Key::A) {
        text->setText("You pressed A!");
        text->setFontSize(30);
        text->setColor(sf::Color::Yellow);
        text->setAnimationStyle(TextAnimation::None);

    }
});

    engine.mountRenderable(text);//add text to the render loop
    
    CountdownText* countdown = new CountdownText(250, 200, 72);
    int ID = engine.mountRenderable(countdown);//add countdown text to the render loop. store ID for removal at a later time

    countdown->setCountdownEndCallback([&engine, text, ID](CountdownText* obj) {//called after the time left reaches 0
        text->setText("Woah");
        text->setAnimationStyle(TextAnimation::None);
        text->setColor(sf::Color::Yellow);

        //uncomment to remove countdown text after finished
        //engine.dismountRenderable(ID);
    });


    engine.run();// engine.run blocks execution until program exited

    //nothing here will run until engine.run() has finshed (ie. program window is closed)
    //nothing should go here

    return 0;
}

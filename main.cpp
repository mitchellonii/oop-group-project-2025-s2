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
    sf::Keyboard::Key keyD = sf::Keyboard::Key::D;

    const sf::Keyboard::Key* keys[] = {&keyA, &keyD};

    text->setKeyboardEventListners(keys, 2);

    text->setKeyPressCallback([&text](sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Key::A) {
        text->setText("You pressed A!");
        text->setFontSize(30);
        text->setColor(sf::Color::Yellow);
        text->setAnimationStyle(TextAnimation::None);
    }else if (key == sf::Keyboard::Key::D) {
        text->setText("You pressed D!");
        text->setFontSize(30);
        text->setColor(sf::Color::Yellow);
        text->setAnimationStyle(TextAnimation::None);

    }
});

 TextElement* text2 = new TextElement();
    
    text2->setText("Click me");
    text2->setColor(sf::Color::Blue);
    text2->setBold(true);
    text2->setPosition(200, 200);
    text2->setFontSize(15);
    text2->setClickable(true);
    text2->setClickboxSize(100, 20);
    text2->setOnClickCallback([&text2](){
        text2->setText("Clicked!");
        text2->setClickable(false);
    });

    engine.mountRenderable(text2);
    engine.mountRenderable(text);
    
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

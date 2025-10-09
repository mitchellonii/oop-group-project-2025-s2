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
    //text class listens for keyboard events (TextElement.cpp). try pressing some keys while the prog is running. look in console

    engine.mountRenderable(text);
    
    CountdownText* countdown = new CountdownText(250, 200, 72);
    int id = engine.mountRenderable(countdown);

    countdown->setDismountCallback([&engine, id](CountdownText* obj) {
        engine.dismountPhysicsElement(id);//remove item by id
        engine.clearAllRenderables(); // remove all items
    });


    engine.run();
    //engine.run blocks execution until exited. anything under will not run
    return 0;
}

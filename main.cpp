#include <SFML/Graphics.hpp>

#include "GameController.h"
#include "PhysicsElement.h"
#include "RenderElement.h"
#include "TextElement.h"

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

    int id = engine.mountRenderable(text);

    //to remove the text from the engine, use:
    //engine.dismountRenderable(id);

    engine.run();
    //engine.run blocks execution until exited. anything under will not run
    return 0;
}

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
    
    engine.mountRenderable(text);

    engine.run();
    //engine.run blocks execution until exited. anything under will not run
    return 0;
}

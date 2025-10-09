#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SFML/Graphics.hpp>
#include "PhysicsElement.h"
#include "RenderElement.h"

class GameController {
private:
    RenderElement** renderables;  
    int renderablesSize;
    int renderablesCapacity;
    
    PhysicsElement** physicsItems;
    int physicsItemsSize;
    int physicsItemsCapacity;
    
    bool runinng;
    sf::RenderWindow* globalWindow;

public:
    static constexpr double FPS = 1000 / 60;

    GameController();
    ~GameController();

    void init();
    void physicsTick();
    void drawAll();
    void run();
    void stop();

    bool mountRenderable(RenderElement* element);  
bool mountPhysicsElement(PhysicsElement* element);
    
    bool dismountRenderable(int index);
    bool dismountPhysicsElement(int index);
    
    bool dismountRenderable(const RenderElement* element);
    bool dismountPhysicsElement(const PhysicsElement* element);
    
    void clearAllRenderables();
    void clearAllPhysicsElements();
    void clearAll();
    
    int getRenderablesCount() const { return renderablesSize; }
    int getPhysicsElementsCount() const { return physicsItemsSize; }
    bool hasRenderables() const { return renderablesSize > 0; }
    bool hasPhysicsElements() const { return physicsItemsSize > 0; }
    
    RenderElement* getRenderableAt(int index);
    PhysicsElement* getPhysicsElementAt(int index);

private:
    void resizeRenderablesIfNeeded();
    void resizePhysicsItemsIfNeeded();
};

#endif
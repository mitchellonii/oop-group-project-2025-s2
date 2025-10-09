#include <string>
#include "RenderElement.h"
#include "PhysicsElement.h"


PhysicsElement::PhysicsElement(){};

PhysicsElement::PhysicsElement(std::string filePath, int posX, int posY, int hitboxR) : hitboxRadius(hitboxR) {
    spriteFilepath = filePath;
    x = posX;
    y = posY;
};

void PhysicsElement::onMount() {
    return;
}
void PhysicsElement::draw(sf::RenderWindow* globalWindow){
    return;
}

void PhysicsElement::physicsTick() {
    return;
}

PhysicsElement::~PhysicsElement() {
    return;
}
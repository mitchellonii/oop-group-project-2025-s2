#ifndef PHYSICSELEMENT_H
#define PHYSICSELEMENT_H

#include "RenderElement.h"
#include <string>
#include <SFML/Graphics.hpp>

class PhysicsElement : public RenderElement {
    protected:
        int dx;
        int dy;
        int hitboxRadius;

    public:
        PhysicsElement();
        PhysicsElement(std::string imageFilePath, int x, int y, int hitboxR);
        void onMount() override;
        void draw(sf::RenderWindow* globalWindow) override;
        void physicsTick();
        ~PhysicsElement() override;
};

#endif
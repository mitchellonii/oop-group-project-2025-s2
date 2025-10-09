#include "RenderElement.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>
RenderElement::RenderElement(){
}
RenderElement::RenderElement(std::string filePath, int posX, int posY) : spriteFilepath(filePath),x(posX),y(posY) {};

void RenderElement::onMount(){
    return;
}



RenderElement::~RenderElement() {
    return;
}
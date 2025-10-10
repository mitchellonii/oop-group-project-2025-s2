#include "RenderElement.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

RenderElement::RenderElement()
    : spriteFilepath(""), x(0), y(0), keybordEvents(nullptr), storedKeyCount(0), lx(0),ly(0),clickable(false) {
}

RenderElement::RenderElement(std::string filePath, int posX, int posY)
    : spriteFilepath(filePath), x(posX), y(posY), keybordEvents(nullptr), storedKeyCount(0), lx(0),ly(0),clickable(false) {
}

void RenderElement::onMount() {
}

RenderElement::~RenderElement() {
    delete[] keybordEvents; 
}

void RenderElement::setKeyPressCallback(std::function<void(sf::Keyboard::Key)> callback) {
    keyPressCallback = callback;
}

void RenderElement::setKeyboardEventListners(const sf::Keyboard::Key* keys[], std::size_t length) {
    delete[] keybordEvents;
    keybordEvents = new sf::Keyboard::Key[length];
    storedKeyCount = static_cast<int>(length);

    for (std::size_t i = 0; i < length; ++i) {
        if (keys[i]) {
            keybordEvents[i] = *keys[i];
        } else {
            keybordEvents[i] = sf::Keyboard::Key::Unknown;
        }
    }
}

sf::Keyboard::Key* RenderElement::getKeyboardEventListners() {
    return keybordEvents;
}

std::size_t RenderElement::getKeyboardEventListnersCount() const {
    return static_cast<std::size_t>(storedKeyCount);
}

void RenderElement::onKeyPress(sf::Keyboard::Key key) {
    if (keyPressCallback) {
        keyPressCallback(key);
    }
}



    void getClickable();
    void setClickable(bool clickable);
    void setClickboxSize(int lx, int ly);


bool RenderElement::getClickable(){
    return clickable;
}

void RenderElement::setClickable(bool c){
    clickable = c;
    return;
}

void RenderElement::setClickboxSize(int lxx, int lyy){
    lx = lxx;
    ly = lyy;
    return;
}

void RenderElement::setOnClickCallback(std::function<void()> callback){
    clickCallback = callback;
}


sf::Vector2i RenderElement::getPosition() const {
    return sf::Vector2i(x, y);
}

sf::Vector2i RenderElement::getClickbox() const {
    return sf::Vector2i(lx, ly);
}
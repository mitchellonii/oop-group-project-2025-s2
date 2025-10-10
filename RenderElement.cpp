#include "RenderElement.h"
#include <string>
#include <SFML/Graphics.hpp>
#include <iostream>

RenderElement::RenderElement()
    : spriteFilepath(""), x(0), y(0), keybordEvents(nullptr), storedKeyCount(0) {
}

RenderElement::RenderElement(std::string filePath, int posX, int posY)
    : spriteFilepath(filePath), x(posX), y(posY), keybordEvents(nullptr), storedKeyCount(0) {
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

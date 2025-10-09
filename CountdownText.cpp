#include "CountdownText.h"
#include <iostream>

CountdownText::CountdownText(int x, int y, unsigned int fontSize)
    : TextElement("5", x, y, fontSize)
{
    std::cout << "[CountdownText] Countdown initialized.\n";
    lastSecond = 5;
}

void CountdownText::setDismountCallback(std::function<void(CountdownText*)> callback) {
    dismountCallback = callback;
}

void CountdownText::draw(sf::RenderWindow* globalWindow) {
    if (globalWindow == nullptr || !isFontLoaded()) {
        std::cout << "[CountdownText] ERROR: Cannot draw.\n";
        return;
    }

    float elapsed = countdownClock.getElapsedTime().asSeconds();
    int currentSecond = 5 - static_cast<int>(elapsed);

    if (currentSecond != lastSecond && currentSecond >= 0) {
        setText(std::to_string(currentSecond));
        lastSecond = currentSecond;
    }

    if (elapsed >= 5.0f) {
        if (dismountCallback) {
            dismountCallback(this);
            dismountCallback = nullptr;
        }
        return; // Skip drawing after countdown ends
    }

    TextElement::draw(globalWindow);
}

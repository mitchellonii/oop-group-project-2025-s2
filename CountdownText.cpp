#include "CountdownText.h"
#include <iostream>

CountdownText::CountdownText(int x, int y, unsigned int fontSize)
    : TextElement("5", x, y, fontSize)
{
    std::cout << "[CountdownText] Countdown initialized.\n";
    lastSecond = 5;
}

void CountdownText::setCountdownEndCallback(std::function<void(CountdownText*)> callback) {
    countdownEndCallback = callback;
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
        if (countdownEndCallback) {
            countdownEndCallback(this);
            countdownEndCallback = nullptr;
        }
    }

    TextElement::draw(globalWindow);
}

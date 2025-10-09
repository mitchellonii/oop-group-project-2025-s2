#ifndef COUNTDOWNTEXT_H
#define COUNTDOWNTEXT_H

#include "TextElement.h"
#include <functional>

class CountdownText : public TextElement {
private:
    sf::Clock countdownClock;
    std::function<void(CountdownText*)> dismountCallback;
    int lastSecond = 5;

public:
    CountdownText(int x, int y, unsigned int fontSize);

    void draw(sf::RenderWindow* globalWindow) override;
    void setDismountCallback(std::function<void(CountdownText*)> callback);
};

#endif

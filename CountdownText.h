#ifndef COUNTDOWNTEXT_H
#define COUNTDOWNTEXT_H

#include <functional>

#include "TextElement.h"

class CountdownText : public TextElement {
 private:
  sf::Clock countdownClock;
  std::function<void(CountdownText*)> countdownEndCallback;
  int lastSecond = 5;
  bool countdownFinished;

 public:
  CountdownText(int x, int y, unsigned int fontSize);

  bool getCountdownFinished();
  void runCountdownEndCallback();
  void draw(sf::RenderWindow* globalWindow) override;
  void setCountdownEndCallback(std::function<void(CountdownText*)> callback);
};

#endif

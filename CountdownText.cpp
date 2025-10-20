#include "CountdownText.h"

#include <iomanip>
#include <iostream>
#include <sstream>

CountdownText::CountdownText(int x, int y, unsigned int fontSize)
    : TextElement("distance travelled 100%", x, y, fontSize) {
  std::cout << "[CountdownText] Initialized with 300-second default.\n";
  lastSecond = 10;
}

void CountdownText::setCountdownEndCallback(
    std::function<void(CountdownText*)> callback) {
  countdownEndCallback = callback;
}

void CountdownText::draw(sf::RenderWindow* globalWindow) {
  if (globalWindow == nullptr || !isFontLoaded()) {
    std::cout << "[CountdownText] ERROR: Cannot draw.\n";
    return;
  }

  float elapsed = countdownClock.getElapsedTime().asSeconds();
  float ratio = (10.0f - elapsed) / 10.0f;
  if (ratio < 0.f) ratio = 0.f;
  if (ratio > 1.f) ratio = 1.f;

  int percent = static_cast<int>(ratio * 100.0f);

  // Only update if value changed (optional optimization)
  if (percent != lastSecond) {
    std::ostringstream ss;
    ss << "distance travelled: " << 100 - percent << "%";
    setText(ss.str());
    lastSecond = percent;
  }

  if (elapsed >= 10.0f) {
    if (countdownEndCallback) {
      countdownEndCallback(this);
      countdownEndCallback = nullptr;
    }
  }

  TextElement::draw(globalWindow);
}

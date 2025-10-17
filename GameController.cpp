#include "GameController.h"

#include <cstring>
#include <iostream>

#include "Character.h"
#include "font_data.h"

GameController::GameController() : runinng(false), globalWindow(nullptr) {
  std::cout << "[GameController] Constructor called.\n";
  renderables.reserve(50);
  physicsItems.reserve(20);
}

void GameController::init() {
  std::cout << "[GameController] Init called.\n";
  globalWindow =
      new sf::RenderWindow(sf::VideoMode({900u, 500u}), "Spacefairer v0.1");
}

void GameController::physicsTick() {
  for (auto* element : physicsItems) {
    element->physicsTick();
  }
}

void GameController::drawAll() {
  for (auto* element : renderables)
    if (element) element->draw(globalWindow);
  for (auto* element : physicsItems) element->draw(globalWindow);
}

void GameController::stop() {
  std::cout << "[GameController] stop() called. Stopping game loop.\n";
  runinng = false;
}

int GameController::mountRenderable(RenderElement* element) {
  if (element == nullptr) {
    std::cout << "[GameController] ERROR: Cannot mount null renderable!\n";
    return -1;
  }
  renderables.push_back(element);
  std::cout << "[GameController] Mounted renderable. Total: "
            << renderables.size() << "\n";
  return static_cast<int>(renderables.size() - 1);
}

int GameController::mountPhysicsElement(PhysicsElement* element) {
  if (element == nullptr) {
    std::cout << "[GameController] ERROR: Cannot mount null physics element!\n";
    return -1;
  }
  physicsItems.push_back(element);
  std::cout << "[GameController] Mounted physics element. Total: "
            << physicsItems.size() << "\n";
  return static_cast<int>(physicsItems.size() - 1);
}

bool GameController::dismountRenderable(int index) {
  if (index < 0 || index >= static_cast<int>(renderables.size())) {
    std::cout << "[GameController] ERROR: Invalid renderable index: " << index
              << "\n";
    return false;
  }
  delete renderables[index];
  renderables.erase(renderables.begin() + index);
  std::cout << "[GameController] Dismounted renderable at index " << index
            << ". Remaining: " << renderables.size() << "\n";
  return true;
}

bool GameController::dismountRenderable(const RenderElement* element) {
  if (element == nullptr) {
    return false;
  }
  for (size_t i = 0; i < renderables.size(); ++i) {
    if (renderables[i] == element) {
      return dismountRenderable(static_cast<int>(i));
    }
  }
  std::cout << "[GameController] WARNING: Renderable not found.\n";
  return false;
}

bool GameController::dismountPhysicsElement(int index) {
  if (index < 0 || index >= static_cast<int>(physicsItems.size())) {
    std::cout << "[GameController] ERROR: Invalid physics element index: "
              << index << "\n";
    return false;
  }
  delete physicsItems[index];
  physicsItems.erase(physicsItems.begin() + index);
  std::cout << "[GameController] Dismounted physics element at index " << index
            << ". Remaining: " << physicsItems.size() << "\n";
  return true;
}

void GameController::clearAllRenderables() {
  for (auto* elem : renderables) {
    if (elem != nullptr) delete elem;
  }
  renderables.clear();
  std::cout << "[GameController] Cleared all renderables.\n";
}

void GameController::clearAllPhysicsElements() {
  for (auto* elem : physicsItems) {
    if (elem != nullptr) delete elem;
  }
  physicsItems.clear();
  std::cout << "[GameController] Cleared all physics elements.\n";
}

void GameController::clearAll() {
  clearAllRenderables();
  clearAllPhysicsElements();
  std::cout << "[GameController] Cleared all elements.\n";
}

RenderElement* GameController::getRenderableAt(int index) {
  if (index < 0 || index >= static_cast<int>(renderables.size()))
    return nullptr;
  return renderables[index];
}

PhysicsElement* GameController::getPhysicsElementAt(int index) {
  if (index < 0 || index >= static_cast<int>(physicsItems.size()))
    return nullptr;
  return physicsItems[index];
}

void GameController::run() {
  std::cout << "[GameController] run() started.\n";
  runinng = true;

  sf::Font font;
  bool fontLoaded = false;

  if (font.openFromMemory(fontData, fontData_len)) {
    fontLoaded = true;
    std::cout << "[GameController] Loaded font from memory.\n";
  }

  sf::Text waitingText(font);
  if (fontLoaded) {
    waitingText.setCharacterSize(24);
    waitingText.setFillColor(sf::Color::Red);
    waitingText.setStyle(sf::Text::Bold);
    waitingText.setPosition({50, 50});
    waitingText.setString("Nothing to render");
  }

  sf::Clock frameClock;
  sf::Time accumulator = sf::Time::Zero;

  sf::Time physicsStep = sf::seconds(1.f / 20.f);
  sf::Time frameLimit = sf::seconds(1.f / 60.f);

  while (runinng && globalWindow->isOpen()) {
    while (const std::optional event = globalWindow->pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        globalWindow->close();
      } else if (event->is<sf::Event::KeyPressed>()) {
        sf::Keyboard::Key key;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
          key = sf::Keyboard::Key::Left;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
          key = sf::Keyboard::Key::Right;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
          key = sf::Keyboard::Key::A;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
          key = sf::Keyboard::Key::D;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
          key = sf::Keyboard::Key::E;
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
          key = sf::Keyboard::Key::Space;
        } else {
          key = sf::Keyboard::Key::Unknown;
        }
        for (size_t i = 0; i < renderables.size(); ++i) {
          auto element = renderables[i];
          if (!element) continue;

          sf::Keyboard::Key* listenedKeys = element->getKeyboardEventListners();
          std::size_t keyCount = element->getKeyboardEventListnersCount();

          for (std::size_t j = 0; j < keyCount; ++j) {
            if (listenedKeys[j] == key) {
              element->onKeyPress(key);
              if (element->keyPressCallback) element->keyPressCallback(key);
              break;
            }
          }
        }

        for (size_t i = 0; i < physicsItems.size(); ++i) {
          auto element = physicsItems[i];
          if (!element) continue;

          sf::Keyboard::Key* listenedKeys = element->getKeyboardEventListners();
          std::size_t keyCount = element->getKeyboardEventListnersCount();

          for (std::size_t j = 0; j < keyCount; ++j) {
            if (listenedKeys[j] == key) {
              element->onKeyPress(key);
              if (element->keyPressCallback) element->keyPressCallback(key);
              break;
            }
          }
          if (auto* character = dynamic_cast<Character*>(element)) {
            character->handleInput();
          }
        }
      }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      sf::Vector2i mousePos = sf::Mouse::getPosition(*globalWindow);

      for (auto* element : renderables) {
        if (!element || !element->getClickable()) continue;

        sf::Vector2i pos = element->getPosition();
        sf::Vector2i box = element->getClickbox();

        int left = pos.x;
        int right = pos.x + box.x;
        int top = pos.y;
        int bottom = pos.y + box.y;

        if (mousePos.x >= left && mousePos.x <= right && mousePos.y >= top &&
            mousePos.y <= bottom && element->clickCallback) {
          element->clickCallback();
        }
      }
    }

    globalWindow->clear(sf::Color::Black);

    sf::Time frameTime = frameClock.restart();
    accumulator += frameTime;

    while (accumulator >= physicsStep) {
      physicsTick();
      accumulator -= physicsStep;
    }

    if (physicsItems.empty() && renderables.empty()) {
      if (fontLoaded) {
        globalWindow->draw(waitingText);
      } else {
        sf::CircleShape errorIndicator(50);
        errorIndicator.setFillColor(sf::Color::Red);
        errorIndicator.setPosition({275, 225});
        globalWindow->draw(errorIndicator);
      }
    } else {
      drawAll();
    }

    globalWindow->display();

    sf::Time elapsed = frameClock.getElapsedTime();
    if (elapsed < frameLimit) {
      sf::sleep(frameLimit - elapsed);
    }
  }

  std::cout << "[GameController] run() exited.\n";
}

GameController::~GameController() {
  std::cout << "[GameController] Destructor called. Cleaning up.\n";
  clearAll();

  if (globalWindow != nullptr) {
    delete globalWindow;
    globalWindow = nullptr;
  }

  std::cout << "[GameController] Cleanup complete.\n";
}

#include "GameController.h"

#include <cstring>
#include <iostream>

#include "Character.h"
#include "CountdownText.h"
#include "Sound.h"
#include "allignNav.h"
#include "font_data.h"
#include "pirateTask.h"
#include "railFix.h"
GameController::GameController()
    : runinng(false),
      globalWindow(nullptr),
      dismountAllRenderableNextFrame(false),
      dismountAllPhysicsNextFrame(false) {
  std::cout << "[GameController] Constructor called.\n";
  renderables.reserve(100);
  physicsItems.reserve(40);
  cargosRemaining = 3;
  cargo1 = nullptr;
  cargo2 = nullptr;
  cargo3 = nullptr;
  navComputer = nullptr;
  toolbox = nullptr;
  handrail = nullptr;
  won = false;
  hasTask = false;
  gameStarted = false;
  frameCounter = 0;
  framesRemaining = 9000;
  countdownExists = false;
  countdown = nullptr;
  lost = false;
}

void GameController::init() {
  globalWindow =
      new sf::RenderWindow(sf::VideoMode({900u, 500u}), "Spacefairer v0.1");
}

void GameController::physicsTick() {
  for (auto* element : physicsItems) {
    if (element) element->physicsTick();
  }
}

void GameController::drawAll() {
  for (auto* element : renderables)
    if (element) element->draw(globalWindow);

  for (auto* element : physicsItems)
    if (element) element->draw(globalWindow);
}

void GameController::stop() { runinng = false; }

int GameController::mountRenderable(RenderElement* element) {
  if (!element) {
    return -1;
  }
  renderables.push_back(element);
  return static_cast<int>(renderables.size() - 1);
}

int GameController::mountPhysicsElement(PhysicsElement* element) {
  if (!element) {
    return -1;
  }
  physicsItems.push_back(element);
  return static_cast<int>(physicsItems.size() - 1);
}

bool GameController::dismountRenderable(const RenderElement* element) {
  if (!element) {
    return false;
  }

  for (size_t i = 0; i < renderables.size(); ++i) {
    if (renderables[i] == element) {
      if (countdown == element) {
        countdown = nullptr;
        countdownExists = false;
      }

      renderables.erase(renderables.begin() + i);
      return true;
    }
  }
  return false;
}

bool GameController::dismountRenderable(int index) {
  if (index < 0 || index >= static_cast<int>(renderables.size())) {
    return false;
  }

  if (renderables[index] == countdown) {
    countdown = nullptr;
    countdownExists = false;
  }

  delete renderables[index];
  renderables.erase(renderables.begin() + index);
  return true;
}

bool GameController::dismountPhysicsElement(int index) {
  if (index < 0 || index >= static_cast<int>(physicsItems.size())) {
    return false;
  }
  delete physicsItems[index];
  physicsItems.erase(physicsItems.begin() + index);
  return true;
}

void GameController::clearAllRenderables() {
  dismountAllRenderableNextFrame = true;
}

void GameController::clearAllPhysicsElements() {
  dismountAllPhysicsNextFrame = true;
}

void GameController::clearAll() {
  dismountAllRenderableNextFrame = true;
  dismountAllPhysicsNextFrame = true;
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
  runinng = true;

  sf::Font font;
  bool fontLoaded = false;
  if (font.openFromMemory(fontData, fontData_len)) {
    fontLoaded = true;
  }

  sf::Text waitingText(font);
  if (fontLoaded) {
    waitingText.setCharacterSize(24);
    waitingText.setFillColor(sf::Color::Red);
    waitingText.setStyle(sf::Text::Bold);
    waitingText.setPosition({50, 50});
    waitingText.setString("Nothing to render");
  }

  sf::Text wonText(font);
  if (fontLoaded) {
    wonText.setCharacterSize(30);
    wonText.setFillColor(sf::Color::Green);
    wonText.setStyle(sf::Text::Bold);
    wonText.setString("YOU WON!");
  }

  sf::Text lostText(font);
  if (fontLoaded) {
    lostText.setCharacterSize(25);
    lostText.setFillColor(sf::Color::Red);
    lostText.setStyle(sf::Text::Bold);
    lostText.setString("You lost");
  }

  sf::Clock frameClock;
  sf::Time accumulator = sf::Time::Zero;
  sf::Time physicsStep = sf::seconds(1.f / 20.f);
  sf::Time frameLimit = sf::seconds(1.f / 60.f);
  MusicTrack* ga = new MusicTrack();
  ga->openFromFile("assets/Spacefairer ambient music.mp3");
  ga->play();
  ga->setLoop(true);
  while (runinng && globalWindow->isOpen()) {
    while (const std::optional event = globalWindow->pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        globalWindow->close();
      }

      if (event->is<sf::Event::KeyPressed>()) {
        sf::Keyboard::Key key = sf::Keyboard::Key::Unknown;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
          key = sf::Keyboard::Key::Left;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
          key = sf::Keyboard::Key::Right;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
          key = sf::Keyboard::Key::A;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
          key = sf::Keyboard::Key::D;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
          key = sf::Keyboard::Key::E;
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
          key = sf::Keyboard::Key::Space;

        for (auto* element : renderables) {
          if (!element) continue;
          sf::Keyboard::Key* listenedKeys = element->getKeyboardEventListners();
          size_t keyCount = element->getKeyboardEventListnersCount();
          for (size_t j = 0; j < keyCount; ++j) {
            if (listenedKeys[j] == key) {
              element->onKeyPress(key);
              if (element->keyPressCallback) element->keyPressCallback(key);
              break;
            }
          }
        }

        for (auto* element : physicsItems) {
          if (!element) continue;
          sf::Keyboard::Key* listenedKeys = element->getKeyboardEventListners();
          size_t keyCount = element->getKeyboardEventListnersCount();
          for (size_t j = 0; j < keyCount; ++j) {
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
        if (mousePos.x >= pos.x && mousePos.x <= pos.x + box.x &&
            mousePos.y >= pos.y && mousePos.y <= pos.y + box.y &&
            element->clickCallback) {
          element->clickCallback();
        }
      }
    }

    sf::Time frameTime = frameClock.restart();
    accumulator += frameTime;
    while (accumulator >= physicsStep) {
      physicsTick();
      accumulator -= physicsStep;
    }

    globalWindow->clear(sf::Color::Black);

    if (physicsItems.empty() && renderables.empty() || won || lost) {
      if (won) {
        ga->stop();
        wonText.setString("You successfully delivered " +
                          std::to_string(cargosRemaining) + "/3 cargo loads");
        globalWindow->draw(wonText);
        wonText.setPosition({250, 300});

      } else if (lost) {
        ga->stop();

        globalWindow->draw(lostText);

      } else if (fontLoaded) {
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

    if (gameStarted && countdownExists && countdown != nullptr) {
      bool found = false;
      for (const auto* r : renderables) {
        if (r == countdown) {
          found = true;
          break;
        }
      }

      if (found && framesRemaining >= 0) {
        int percent =
            static_cast<int>(((9000.0f - framesRemaining) / 9000.0f) * 100.0f);
        if (percent < 0) percent = 0;
        if (percent > 100) percent = 100;

        std::string newText =
            "Distance travelled: " + std::to_string(percent) + "%";

        countdown->setText(newText);
      } else if (!found) {
        std::cout << "[GameController] Countdown pointer invalid, disabling\n";
        countdown = nullptr;
        countdownExists = false;
      }
    }

    if (gameStarted && !won && !lost && !won) {
      frameCounter++;
      framesRemaining--;
    }
    if (framesRemaining == 0 && !won) {
      won = true;
      MusicTrack* s = new MusicTrack();
      s->openFromFile("assets/SFXSpacefairerer_YOUWIN.mp3");
      s->play();
    }
    if (hasTask && !lost) {
      currentTask->tick();
      if (currentTask->getIsCompleted()) {
        hasTask = false;
      } else if (currentTask->getTicksRemaining() <= 0) {
        if (currentTask->getTaskId() == 3) {
          this->removeCargo();

          currentTask->complete();
          MusicTrack* s = new MusicTrack();
          s->openFromFile("assets/cargo.mp3");
          s->play();
          hasTask = false;
          if (this->cargosRemaining == 0) {
            lost = true;
            MusicTrack* s = new MusicTrack();
            s->openFromFile("assets/YOULOSE.mp3");
            s->play();
            lostText.setString(
                "All cargo lost. Further operation is impractical.");

            lostText.setPosition({100, 230});
          }
        } else {
          lost = true;
          MusicTrack* s = new MusicTrack();
          s->openFromFile("assets/YOULOSE.mp3");
          s->play();
          switch (currentTask->getTaskId()) {
            case 1:
              lostText.setString(
                  "You didn't fix the handrail and violated space OSHA "
                  "standards");
              break;
            case 2:
              lostText.setString(
                  "You didn't realign navigation and collided with an "
                  "asteroid");
              break;
            default:
              break;
          }

          lostText.setPosition({100, 230});
        }
      }
      if (hasTask && currentTask->getTaskId()) {
        switch (currentTask->getTaskId()) {
          case 1:
            if (!handrail->getBlinking()) handrail->setBlinking(true);
            if (!toolbox->getBlinking()) toolbox->setBlinking(true);
            break;
          case 2:
            if (!navComputer->getBlinking()) navComputer->setBlinking(true);
            break;
          default:
            break;
        }

      } else {
        if (handrail->getBlinking()) handrail->setBlinking(false);
        if (toolbox->getBlinking()) toolbox->setBlinking(false);
        if (navComputer->getBlinking()) navComputer->setBlinking(false);
      }
    }

    if (frameCounter % 333 == 0 && !hasTask && gameStarted) {
      int randomInRange = rand() % 3;   // 0–2
      int randomInRange2 = rand() % 4;  // 0–3
      int randomInRange3 = rand() % 3;  // 0–2
      Task* t;
      std::string dirs[4] = {"up", "down", "left", "right"};

      std::string types[3] = {"empathetic", "money", "insecure"};

      switch (randomInRange) {
        case 0:
          t = new railFix(20, true, 1, this);
          break;
        case 1:
          t = new allignNav(20, dirs[randomInRange2], 2, this);
          break;
        case 2:
          t = new pirateTask(20, types[randomInRange3], 3, this);
          break;
        default:
          break;
      }

      setCurrentTask(t);
      MusicTrack* s = new MusicTrack();
      s->openFromFile("assets/SFXSpacefairerer_tasks_NewTask.mp3");
      s->play();
    }

    // Frame limiting
    sf::Time elapsed = frameClock.getElapsedTime();
    if (elapsed < frameLimit) {
      sf::sleep(frameLimit - elapsed);
    }

    for (auto* renderable : renderables) {
      auto* countdownText = dynamic_cast<CountdownText*>(renderable);
      if (countdownText && countdownText->getCountdownFinished()) {
        countdownText->runCountdownEndCallback();
      }
    }
  }
}

GameController::~GameController() {
  // Clear countdown pointer first
  countdown = nullptr;
  countdownExists = false;

  clearAll();
  drawAll();

  if (globalWindow) {
    delete globalWindow;
    globalWindow = nullptr;
  }
}

void GameController::setCargos(PhysicsElement* c1, PhysicsElement* c2,
                               PhysicsElement* c3) {
  cargo1 = c1;
  cargo2 = c2;
  cargo3 = c3;
}

void GameController::removeCargo() {
  if (cargosRemaining <= 0) {
    return;
  }

  PhysicsElement* cargo = nullptr;
  if (cargosRemaining == 3)
    cargo = cargo1;
  else if (cargosRemaining == 2)
    cargo = cargo2;
  else if (cargosRemaining == 1)
    cargo = cargo3;

  if (!cargo) {
    return;
  }

  cargo->setVelocity(15.0, -30.0);
  cargosRemaining--;
}

void GameController::setNavComputer(RenderElement* nav) { navComputer = nav; }
void GameController::setToolbox(RenderElement* box) { toolbox = box; }
void GameController::setHandrail(RenderElement* rail) { handrail = rail; }

void GameController::setWon(bool w) { won = w; }

bool GameController::getHasTask() { return hasTask; }
Task* GameController::getCurrentTask() { return currentTask; }

void GameController::setCurrentTask(Task* h) {
  currentTask = h;
  hasTask = true;
}

void GameController::setHasTask(bool t) { hasTask = t; }

bool GameController::getGameStarted() { return gameStarted; }
void GameController::setGameStarted(bool g) { gameStarted = g; }

int GameController::getFramesRemaining() { return framesRemaining; }
void GameController::setFramesRemaining(int h) { framesRemaining = h; }

void GameController::setCountdown(TextElement* h) {
  if (h == nullptr) {
    return;
  }

  bool found = false;
  for (const auto* r : renderables) {
    if (r == h) {
      found = true;
      break;
    }
  }

  if (!found) {
    return;
  }

  countdown = h;
  countdownExists = true;
}

void GameController::setLost(bool l) { lost = l; }

RenderElement* GameController::getToolbox() { return toolbox; }
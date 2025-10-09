#include "GameController.h"
#include <iostream>
#include <cstring>
#include "font_data.h"

GameController::GameController()
{
    std::cout << "[GameController] Constructor called.\n";

    renderablesCapacity = 50;
    renderables = new RenderElement*[renderablesCapacity];
    for (int i = 0; i < renderablesCapacity; i++) {
        renderables[i] = nullptr;
    }
    renderablesSize = 0;

    physicsItemsCapacity = 20;
    physicsItems = new PhysicsElement*[physicsItemsCapacity];
    for (int i = 0; i < physicsItemsCapacity; ++i) {
        physicsItems[i] = nullptr;
    }
    physicsItemsSize = 0;

    runinng = false;
}

void GameController::init()
{
    std::cout << "[GameController] Init called.\n";
    this->globalWindow = new sf::RenderWindow(sf::VideoMode({600u, 500u}), "Spacefairer v0.1");
}

void GameController::physicsTick()
{
    for (int i = 0; i < this->physicsItemsSize; i++)
    {
        this->physicsItems[i]->physicsTick();
    }
}

void GameController::drawAll()
{
    for (int i = 0; i < this->physicsItemsSize; i++)
    {
        this->physicsItems[i]->draw(this->globalWindow);
    }
    for (int i = 0; i < this->renderablesSize; i++)
    {
        if (this->renderables[i] != nullptr)
        {
            this->renderables[i]->draw(this->globalWindow);
        }
    }
}

void GameController::stop()
{
    std::cout << "[GameController] stop() called. Stopping game loop.\n";
    this->runinng = false;
}

int GameController::mountRenderable(RenderElement *element)
{
    if (element == nullptr)
    {
        std::cout << "[GameController] ERROR: Cannot mount null renderable!\n";
        return -1;
    }

    resizeRenderablesIfNeeded();

    if (renderablesSize >= renderablesCapacity)
    {
        std::cout << "[GameController] ERROR: Cannot mount renderable, array is full!\n";
        return -1;
    }

    renderables[renderablesSize] = element;
    renderablesSize++;
    std::cout << "[GameController] Mounted renderable. Total: " << renderablesSize << "\n";
    return (renderablesSize-1);
}

int GameController::mountPhysicsElement(PhysicsElement* element)
{
    if (element == nullptr)
    {
        std::cout << "[GameController] ERROR: Cannot mount null physics element!\n";
        return -1;
    }

    resizePhysicsItemsIfNeeded();

    if (physicsItemsSize >= physicsItemsCapacity)
    {
        std::cout << "[GameController] ERROR: Cannot mount physics element, array is full!\n";
        return -1;
    }

    physicsItems[physicsItemsSize++] = element;
    std::cout << "[GameController] Mounted physics element. Total: " << physicsItemsSize << "\n";
    return (physicsItemsSize-1);
}


bool GameController::dismountRenderable(int index)
{
    if (index < 0 || index >= renderablesSize)
    {
        std::cout << "[GameController] ERROR: Invalid renderable index: " << index << "\n";
        return false;
    }

    if (renderables[index] != nullptr)
    {
        delete renderables[index];
    }

    for (int i = index; i < renderablesSize - 1; i++)
    {
        renderables[i] = renderables[i + 1];
    }

    renderables[renderablesSize - 1] = nullptr;
    renderablesSize--;
    std::cout << "[GameController] Dismounted renderable at index " << index
              << ". Remaining: " << renderablesSize << "\n";
    return true;
}



bool GameController::dismountRenderable(const RenderElement *element)
{
    if (element == nullptr)
    {
        return false;
    }

    for (int i = 0; i < renderablesSize; i++)
    {
        if (renderables[i] == element)
        {
            return dismountRenderable(i);
        }
    }

    std::cout << "[GameController] WARNING: Renderable not found in array.\n";
    return false;
}

bool GameController::dismountPhysicsElement(int index)
{
    if (index < 0 || index >= physicsItemsSize)
    {
        std::cout << "[GameController] ERROR: Invalid physics element index: " << index << "\n";
        return false;
    }

    delete physicsItems[index];

    for (int i = index; i < physicsItemsSize - 1; i++)
    {
        physicsItems[i] = physicsItems[i + 1];
    }

    physicsItems[physicsItemsSize - 1] = nullptr;
    physicsItemsSize--;

    std::cout << "[GameController] Dismounted physics element at index " << index
              << ". Remaining: " << physicsItemsSize << "\n";
    return true;
}


void GameController::clearAllRenderables()
{
    for (int i = 0; i < renderablesSize; i++)
    {
        if (renderables[i] != nullptr)
        {
            delete renderables[i];
            renderables[i] = nullptr;
        }
    }
    renderablesSize = 0;
    std::cout << "[GameController] Cleared all renderables.\n";
}

void GameController::clearAllPhysicsElements()
{
    physicsItemsSize = 0;
    std::cout << "[GameController] Cleared all physics elements.\n";
}

void GameController::clearAll()
{
    clearAllRenderables();
    clearAllPhysicsElements();
    std::cout << "[GameController] Cleared all elements.\n";
}

RenderElement *GameController::getRenderableAt(int index)
{
    if (index < 0 || index >= renderablesSize)
    {
        return nullptr;
    }
    return renderables[index];
}

PhysicsElement* GameController::getPhysicsElementAt(int index)
{
    if (index < 0 || index >= physicsItemsSize)
    {
        return nullptr;
    }
    return physicsItems[index];
}

void GameController::resizeRenderablesIfNeeded()
{
    if (renderablesSize >= renderablesCapacity)
    {
        int newCapacity = renderablesCapacity * 2;
        RenderElement **newArray = new RenderElement *[newCapacity];

        for (int i = 0; i < newCapacity; i++)
        {
            newArray[i] = nullptr;
        }

        for (int i = 0; i < renderablesSize; i++)
        {
            newArray[i] = renderables[i];
        }

        delete[] renderables;
        renderables = newArray;
        renderablesCapacity = newCapacity;

        std::cout << "[GameController] Resized renderables array to capacity: "
                  << newCapacity << "\n";
    }
}

void GameController::resizePhysicsItemsIfNeeded()
{
    if (physicsItemsSize >= physicsItemsCapacity)
    {
        int newCapacity = physicsItemsCapacity * 2;
        PhysicsElement** newArray = new PhysicsElement*[newCapacity];

        for (int i = 0; i < newCapacity; i++)
        {
            newArray[i] = (i < physicsItemsSize) ? physicsItems[i] : nullptr;
        }

        delete[] physicsItems;
        physicsItems = newArray;
        physicsItemsCapacity = newCapacity;

        std::cout << "[GameController] Resized physics items array to capacity: "
                  << newCapacity << "\n";
    }
}


void GameController::run()
{
    std::cout << "[GameController] run() started.\n";
    this->runinng = true;

    sf::Font font;
    bool fontLoaded = false;

    if (font.openFromMemory(fontData, fontData_len))
    {
        fontLoaded = true;
        std::cout << "[GameController] Loaded font from memory.\n";
    }

    sf::Text waitingText(font);
    if (fontLoaded)
    {
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

    while (this->runinng && this->globalWindow->isOpen())
    {
        while (const std::optional event = this->globalWindow->pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                this->globalWindow->close();
            }
            else if (event->is<sf::Event::KeyPressed>())
            {
                sf::Keyboard::Key key;

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
                {
                    key = sf::Keyboard::Key::Left;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
                {
                    key = sf::Keyboard::Key::Right;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
                {
                    key = sf::Keyboard::Key::A;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                {
                    key = sf::Keyboard::Key::D;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
                {
                    key = sf::Keyboard::Key::E;
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
                {
                    key = sf::Keyboard::Key::Space;
                }
                else
                {
                    key = sf::Keyboard::Key::Unknown;
                }
                for (int i = 0; i < this->renderablesSize; ++i)
                {
                    if (this->renderables[i])
                    {
                        this->renderables[i]->onKeyPress(key);
                    }
                }
            }
        }

        this->globalWindow->clear(sf::Color::Black);

        sf::Time frameTime = frameClock.restart();
        accumulator += frameTime;

        while (accumulator >= physicsStep)
        {
            this->physicsTick();
            accumulator -= physicsStep;
        }

        if (this->physicsItemsSize == 0 && this->renderablesSize == 0)
        {
            if (fontLoaded)
            {
                this->globalWindow->draw(waitingText);
            }
            else
            {
                sf::CircleShape errorIndicator(50);
                errorIndicator.setFillColor(sf::Color::Red);
                errorIndicator.setPosition({275, 225});
                this->globalWindow->draw(errorIndicator);
            }
        }
        else
        {
            this->drawAll();
        }

        this->globalWindow->display();

        sf::Time elapsed = frameClock.getElapsedTime();
        if (elapsed < frameLimit)
        {
            sf::sleep(frameLimit - elapsed);
        }
    }

    std::cout << "[GameController] run() exited.\n";
}

GameController::~GameController()
{
    std::cout << "[GameController] Destructor called. Cleaning up.\n";

    for (int i = 0; i < renderablesSize; i++)
    {
        if (renderables[i] != nullptr)
        {
            delete renderables[i];
        }
    }
    delete[] renderables;

    delete[] physicsItems;

    if (globalWindow != nullptr)
    {
        delete globalWindow;
        globalWindow = nullptr;
    }

    std::cout << "[GameController] Cleanup complete.\n";
}
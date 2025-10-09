#include "GameController.h"
#include <iostream>
#include <cstring>
#include "font_data.h"

GameController::GameController() {
    std::cout << "[GameController] Constructor called.\n";

    renderablesCapacity = 50;
    renderables = new RenderElement*[renderablesCapacity];
    for (int i = 0; i < renderablesCapacity; i++) {
        renderables[i] = nullptr;
    }
    renderablesSize = 0;

    physicsItemsCapacity = 20;
    physicsItems = new PhysicsElement[physicsItemsCapacity];
    physicsItemsSize = 0;

    runinng = false;
}

void GameController::init() {
    std::cout << "[GameController] Init called.\n";
    this->globalWindow = new sf::RenderWindow(sf::VideoMode({600u, 500u}), "Spacefairer v0.1");
}

void GameController::physicsTick() {
    for (int i = 0; i < this->physicsItemsSize; i++) {
        this->physicsItems[i].physicsTick();
    }
}

void GameController::drawAll() {
    for (int i = 0; i < this->physicsItemsSize; i++) {
        this->physicsItems[i].draw(this->globalWindow);
    }
    for (int i = 0; i < this->renderablesSize; i++) {
        std::cout << "attempting to draw element " << i << "\n";
        if (this->renderables[i] != nullptr) {
            this->renderables[i]->draw(this->globalWindow);
        }
    }
}

void GameController::stop() {
    std::cout << "[GameController] stop() called. Stopping game loop.\n";
    this->runinng = false;
}

bool GameController::mountRenderable(RenderElement* element) {
    if (element == nullptr) {
        std::cout << "[GameController] ERROR: Cannot mount null renderable!\n";
        return false;
    }
    
    resizeRenderablesIfNeeded();
    
    if (renderablesSize >= renderablesCapacity) {
        std::cout << "[GameController] ERROR: Cannot mount renderable, array is full!\n";
        return false;
    }
    
    renderables[renderablesSize] = element;
    renderablesSize++;
    std::cout << "[GameController] Mounted renderable. Total: " << renderablesSize << "\n";
    return true;
}

bool GameController::mountPhysicsElement(const PhysicsElement& element) {
    resizePhysicsItemsIfNeeded();
    
    if (physicsItemsSize >= physicsItemsCapacity) {
        std::cout << "[GameController] ERROR: Cannot mount physics element, array is full!\n";
        return false;
    }
    
    physicsItems[physicsItemsSize] = element;
    physicsItemsSize++;
    std::cout << "[GameController] Mounted physics element. Total: " << physicsItemsSize << "\n";
    return true;
}

// Dismount renderable by index
bool GameController::dismountRenderable(int index) {
    if (index < 0 || index >= renderablesSize) {
        std::cout << "[GameController] ERROR: Invalid renderable index: " << index << "\n";
        return false;
    }
    
    // Delete the element
    if (renderables[index] != nullptr) {
        delete renderables[index];
    }
    
    // Shift elements down to fill the gap
    for (int i = index; i < renderablesSize - 1; i++) {
        renderables[i] = renderables[i + 1];
    }
    
    renderables[renderablesSize - 1] = nullptr;
    renderablesSize--;
    std::cout << "[GameController] Dismounted renderable at index " << index 
              << ". Remaining: " << renderablesSize << "\n";
    return true;
}

// Dismount physics element by index
bool GameController::dismountPhysicsElement(int index) {
    if (index < 0 || index >= physicsItemsSize) {
        std::cout << "[GameController] ERROR: Invalid physics element index: " << index << "\n";
        return false;
    }
    
    // Shift elements down to fill the gap
    for (int i = index; i < physicsItemsSize - 1; i++) {
        physicsItems[i] = physicsItems[i + 1];
    }
    
    physicsItemsSize--;
    std::cout << "[GameController] Dismounted physics element at index " << index 
              << ". Remaining: " << physicsItemsSize << "\n";
    return true;
}

// Dismount renderable by pointer
bool GameController::dismountRenderable(const RenderElement* element) {
    if (element == nullptr) {
        return false;
    }
    
    // Find the element in the array
    for (int i = 0; i < renderablesSize; i++) {
        if (renderables[i] == element) {
            return dismountRenderable(i);
        }
    }
    
    std::cout << "[GameController] WARNING: Renderable not found in array.\n";
    return false;
}

// Dismount physics element by pointer
bool GameController::dismountPhysicsElement(const PhysicsElement* element) {
    if (element == nullptr) {
        return false;
    }
    
    // Find the element in the array
    for (int i = 0; i < physicsItemsSize; i++) {
        if (&physicsItems[i] == element) {
            return dismountPhysicsElement(i);
        }
    }
    
    std::cout << "[GameController] WARNING: Physics element not found in array.\n";
    return false;
}

// Clear all renderables
void GameController::clearAllRenderables() {
    // Delete all elements
    for (int i = 0; i < renderablesSize; i++) {
        if (renderables[i] != nullptr) {
            delete renderables[i];
            renderables[i] = nullptr;
        }
    }
    renderablesSize = 0;
    std::cout << "[GameController] Cleared all renderables.\n";
}

// Clear all physics elements
void GameController::clearAllPhysicsElements() {
    physicsItemsSize = 0;
    std::cout << "[GameController] Cleared all physics elements.\n";
}

// Clear everything
void GameController::clearAll() {
    clearAllRenderables();
    clearAllPhysicsElements();
    std::cout << "[GameController] Cleared all elements.\n";
}

// Get renderable at index
RenderElement* GameController::getRenderableAt(int index) {
    if (index < 0 || index >= renderablesSize) {
        return nullptr;
    }
    return renderables[index];
}

// Get physics element at index
PhysicsElement* GameController::getPhysicsElementAt(int index) {
    if (index < 0 || index >= physicsItemsSize) {
        return nullptr;
    }
    return &physicsItems[index];
}

// Resize renderables array if needed (double capacity)
void GameController::resizeRenderablesIfNeeded() {
    if (renderablesSize >= renderablesCapacity) {
        int newCapacity = renderablesCapacity * 2;
        RenderElement** newArray = new RenderElement*[newCapacity];
        
        // Initialize new pointers to nullptr
        for (int i = 0; i < newCapacity; i++) {
            newArray[i] = nullptr;
        }
        
        // Copy existing pointers
        for (int i = 0; i < renderablesSize; i++) {
            newArray[i] = renderables[i];
        }
        
        delete[] renderables;  // Only delete the array, not the elements
        renderables = newArray;
        renderablesCapacity = newCapacity;
        
        std::cout << "[GameController] Resized renderables array to capacity: " 
                  << newCapacity << "\n";
    }
}

// Resize physics items array if needed (double capacity)
void GameController::resizePhysicsItemsIfNeeded() {
    if (physicsItemsSize >= physicsItemsCapacity) {
        int newCapacity = physicsItemsCapacity * 2;
        PhysicsElement* newArray = new PhysicsElement[newCapacity];
        
        // Copy existing elements
        for (int i = 0; i < physicsItemsSize; i++) {
            newArray[i] = physicsItems[i];
        }
        
        delete[] physicsItems;
        physicsItems = newArray;
        physicsItemsCapacity = newCapacity;
        
        std::cout << "[GameController] Resized physics items array to capacity: " 
                  << newCapacity << "\n";
    }
}

void GameController::run() {
    std::cout << "[GameController] run() started.\n";
    this->runinng = true;

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
        waitingText.setString("Waiting for content...");
    }

    sf::Clock frameClock;
    sf::Time accumulator = sf::Time::Zero;

    sf::Time physicsStep = sf::seconds(1.f / 20.f);
    sf::Time frameLimit = sf::seconds(1.f / 60.f);

    while (this->runinng && this->globalWindow->isOpen()) {
        while (const std::optional event = this->globalWindow->pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                this->globalWindow->close();
            }
        }

        this->globalWindow->clear(sf::Color::Black);
        
        sf::Time frameTime = frameClock.restart();
        accumulator += frameTime;

        while (accumulator >= physicsStep) {
            this->physicsTick();
            accumulator -= physicsStep;
        }

        if (this->physicsItemsSize == 0 && this->renderablesSize == 0) {
            if (fontLoaded) {
                this->globalWindow->draw(waitingText);
            } else {
                sf::CircleShape errorIndicator(50);
                errorIndicator.setFillColor(sf::Color::Red);
                errorIndicator.setPosition({275, 225});
                this->globalWindow->draw(errorIndicator);
            }
        } else {
            this->drawAll();
        }

        this->globalWindow->display();

        sf::Time elapsed = frameClock.getElapsedTime();
        if (elapsed < frameLimit) {
            sf::sleep(frameLimit - elapsed);
        }
    }

    std::cout << "[GameController] run() exited.\n";
}

GameController::~GameController() {
    std::cout << "[GameController] Destructor called. Cleaning up.\n";

    // Delete all renderable elements first
    for (int i = 0; i < renderablesSize; i++) {
        if (renderables[i] != nullptr) {
            delete renderables[i];
        }
    }
    // Then delete the array of pointers
    delete[] renderables;
    
    delete[] physicsItems;

    if (globalWindow != nullptr) {
        delete globalWindow;
        globalWindow = nullptr;
    }

    std::cout << "[GameController] Cleanup complete.\n";
}

#ifndef RENDERELEMENT_H
#define RENDERELEMENT_H

#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <functional>

class RenderElement {
protected:
    std::string spriteFilepath;
    int x;
    int y;
    int clickable;
    int lx;
    int ly;
    int storedKeyCount = 0;
    sf::Keyboard::Key* keybordEvents = nullptr;

public:
    RenderElement();
    RenderElement(std::string imageFilePath, int x, int y);
    virtual ~RenderElement();

    virtual void onMount();

    bool getClickable();
    void setClickable(bool clickable);
    void setClickboxSize(int lx, int ly);
    void setKeyPressCallback(std::function<void(sf::Keyboard::Key)> callback);
    void onKeyPress(sf::Keyboard::Key key);
    sf::Vector2i getPosition() const;
    sf::Vector2i getClickbox() const;
    void setOnClickCallback(std::function<void()> callback);
    void setKeyboardEventListners(const sf::Keyboard::Key* keys[], std::size_t length);
    std::function<void(sf::Keyboard::Key)> keyPressCallback;
    std::function<void()> clickCallback;

    sf::Keyboard::Key* getKeyboardEventListners();
    std::size_t getKeyboardEventListnersCount() const;

    virtual void draw(sf::RenderWindow* globalWindow) = 0;
};

#endif

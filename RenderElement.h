
#ifndef RENDERELEMENT_H
#define RENDERELEMENT_H

#include <string>
#include <SFML/Graphics.hpp>

class RenderElement{
    protected:
        std::string spriteFilepath;
        int x;
        int y;
    
    public:
        RenderElement();
        RenderElement(std::string imageFilePath, int x, int y);
        virtual void onMount();
        virtual void draw(sf::RenderWindow* globalWindow) =0;
        virtual ~RenderElement();
};


#endif 
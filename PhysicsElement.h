#ifndef PHYSICSELEMENT_H
#define PHYSICSELEMENT_H

#include <SFML/Graphics.hpp>
#include <string>

#include "RenderElement.h"

class PhysicsElement : public RenderElement {
 protected:
  int dx;
  int dy;
  int hitboxRadius;

 public:
  PhysicsElement();
  PhysicsElement(std::string imageFilePath, int x, int y, int hitboxR);
  void onMount() override;
  void draw(sf::RenderWindow* globalWindow) override;
  void setVelocity(double dx, double dy);
  virtual void physicsTick();
  ~PhysicsElement() override;
};

#endif
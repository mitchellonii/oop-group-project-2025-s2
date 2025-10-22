#ifndef PROGRESS_H
#define PROGRESS_H

#include "RenderElement.h"

class ProgressBar : public RenderElement {
 private:
  int progressPercentage;
  sf::Texture texture;
  int width;
  int height;

 public:
  ProgressBar(std::string imageFilePath, int x, int y, int width, int height);
  void setProgress(int percentage);
  void draw(sf::RenderWindow* globalWindow) override;
};

#endif
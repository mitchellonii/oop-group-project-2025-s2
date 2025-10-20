#ifndef PROGRESS_H
#define PROGRESS_H

#include "RenderElement.h"

class ProgressBar : public RenderElement {
 private:
  int progressPercentage;  // 0 to 100
  sf::Texture texture;
  int width;
  int height;

 public:
  ProgressBar(std::string imageFilePath, int x, int y, int width, int height);
  void setProgress(int percentage);  // Set progress percentage (0-100)
  void draw(sf::RenderWindow* globalWindow) override;
};

#endif
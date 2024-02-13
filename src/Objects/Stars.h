
#ifndef PLATFORMERSFML_STARS_H
#define PLATFORMERSFML_STARS_H

#include "Gameobjects.h"

class Stars: public Gameobjects
{
 public:
  Stars();

 private:
  void init();
  void update(float dt) override;
  sf::IntRect texture_rect;
};

#endif // PLATFORMERSFML_STARS_H

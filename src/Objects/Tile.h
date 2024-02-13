
#ifndef PLATFORMERSFML_TILE_H
#define PLATFORMERSFML_TILE_H

#include "Gameobjects.h"

class Tile: public Gameobjects
{
 public:
  Tile();
  void update(float dt) override;

 private:
  sf::IntRect texture_rect;

  void init();
};

#endif // PLATFORMERSFML_TILE_H

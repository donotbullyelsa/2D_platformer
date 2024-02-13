
#ifndef PLATFORMERSFML_BACKGROUNDS_H
#define PLATFORMERSFML_BACKGROUNDS_H

#include "Layout/Layout.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Backgrounds
{
 public:
  void init();
  void update(float dt, float playerX);

  sf::Sprite background[2];
  sf::Texture bg_texture[2];

 private:
  bool player_at; // the sprite that player is located at
  bool at_left; // is player at left/right part of the sprite?
};

#endif // PLATFORMERSFML_BACKGROUNDS_H

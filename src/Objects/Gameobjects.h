
#ifndef PLATFORMERSFML_GAMEOBJECTS_H
#define PLATFORMERSFML_GAMEOBJECTS_H

#include "../GameControlling/Layout/Layout.h"
#include "../Vector2.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Gameobjects
{
 public:
  Gameobjects(std::string link_to_texture);
  virtual void update(float dt) = 0;
  sf::Sprite* getSprite();

  bool existance;

 protected:
  sf::Texture texture;
  sf::Sprite sprite;

 private:
  std::string texture_link;
  void init();
};

#endif // PLATFORMERSFML_GAMEOBJECTS_H


#include "Gameobjects.h"

Gameobjects::Gameobjects(std::string link_to_texture)
{
  texture_link = link_to_texture;

  init();
}

void Gameobjects::init()
{
  if (!texture.loadFromFile(texture_link))
  {
    std::cout << "Error: Fail to load texture.";
  }
  sprite.setTexture(texture);
  existance = true;
}

sf::Sprite* Gameobjects::getSprite()
{
  return &sprite;
}
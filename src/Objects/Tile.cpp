
#include "Tile.h"

Tile::Tile(): Gameobjects("Data/Images/kenney_physicspack/Spritesheet/spritesheet_tiles.png")
{
  init();
}

void Tile::init()
{
  texture_rect = sf::IntRect(280, 70, 70, 70);
  sprite.setTextureRect(texture_rect);
  Layout::goto_middle(sprite);
}

void Tile::update(float dt)
{

}
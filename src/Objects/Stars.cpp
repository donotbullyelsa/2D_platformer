
#include "Stars.h"

Stars::Stars(): Gameobjects("Data/Images/kenney_physicspack/Spritesheet/spritesheet_tiles.png")
{
  init();
}

void Stars::init()
{
  texture_rect = sf::IntRect(140, 70, 70, 70);
  sprite.setTextureRect(texture_rect);
  Layout::goto_middle(sprite);
}
void Stars::update(float dt)
{

}

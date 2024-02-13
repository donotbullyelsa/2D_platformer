
#include "Bullet.h"

Bullet::Bullet() : Rigidbody("Data/Images/kenney_pixel-ui-pack/Spritesheet/UIpackSheet_transparent.png")
{
  init();
}

void Bullet::init()
{
  texture_rect1 = sf::IntRect(36, 18 * 27, 16, 16);
  sprite.setTextureRect(texture_rect1);
}

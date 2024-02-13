
#include "Rigidbody.h"

Rigidbody::Rigidbody(std::string link_to_texture) : Gameobjects(link_to_texture)
{

}

void Rigidbody::update(float dt)
{

}

bool Rigidbody::updateAnimation()
{
  if (in_walk)
  {
    sprite.setTextureRect(texture_rect2);
  }
  else
  {
    sprite.setTextureRect(texture_rect1);
  }
  if (animation_clock.getElapsedTime().asSeconds() > ANIMATION_UPDATE_TIME)
  {
    in_walk = !in_walk;
    animation_clock.restart();
    return true;
  }
  return false;
}



#include "Enemies.h"

Enemies::Enemies(float platform_length): Rigidbody("Data/kenney_pixelplatformer/Tilemap/characters_packed.png")
{
  return_distance = platform_length;
  init();
}

void Enemies::init()
{
  sprite.setScale(2.0f, 2.0f);
  texture_rect1 = sf::IntRect(148, 28, 15, 20);
  texture_rect2 = texture_rect1;
  texture_rect2.left += texture_rect1.width + 9;
  //texture_rect2.top -= 2;
  //texture_rect2.height += 2;
  sprite.setTextureRect(texture_rect1);
  sprite.setScale(sprite.getScale().x * -1, sprite.getScale().y);
  sprite.move(-sprite.getGlobalBounds().width, 2);
  facing_right = true;
  last_facing = true;
  in_walk = true;
  on_ground = nullptr;
  return_distance -= sprite.getGlobalBounds().width;
  return_distance_left = return_distance;
}

void Enemies::update(float dt)
{
  // update animation
  enemyAnimationHandle();

  // handle the motion of the enemy
  movementHandler(dt);
}

void Enemies::movementHandler(float dt)
{
  // move the character
  float offset_x;
  if (facing_right)
  {
    offset_x = dt * SPEED;
  }
  else
  {
    offset_x = -dt * SPEED;
  }
  sprite.move(offset_x, 0);

  return_distance_left -= abs(offset_x);
  if (return_distance_left <= 0)
  {
    facing_right = !facing_right;
    return_distance_left = return_distance;
  }
}

void Enemies::enemyAnimationHandle()
{
  updateAnimation();

  if (facing_right != last_facing)
  {
    sprite.setScale(sprite.getScale().x * -1, sprite.getScale().y);
    if (facing_right)
    {
      sprite.move(sprite.getGlobalBounds().width, 0);
    }
    else
    {
      sprite.move(-sprite.getGlobalBounds().width, 0);
    }
  }

  last_facing = facing_right;
}

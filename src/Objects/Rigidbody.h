
#ifndef PLATFORMERSFML_RIGIDBODY_H
#define PLATFORMERSFML_RIGIDBODY_H

#include "Gameobjects.h"
#include "Tile.h"

class Rigidbody: public Gameobjects
{
 public:
  Rigidbody(std::string link_to_texture);
  void update(float dt) override;

  bool facing_right;
  bool last_facing;
  Tile* on_ground;
  Vector2 direction = Vector2(0, 0);

  sf::IntRect texture_rect1;
  sf::IntRect texture_rect2;
  bool in_walk;

 protected:
  bool updateAnimation();
  sf::Clock animation_clock;
  const float ANIMATION_UPDATE_TIME = 0.1;
};

#endif // PLATFORMERSFML_RIGIDBODY_H

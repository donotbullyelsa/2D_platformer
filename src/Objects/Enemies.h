
#ifndef PLATFORMERSFML_ENEMIES_H
#define PLATFORMERSFML_ENEMIES_H

#include "Rigidbody.h"

class Enemies: public Rigidbody
{
 public:
  Enemies(float platform_length);
  void init();

  void update(float dt) override;

 private:
  const int SPEED = 200;
  float return_distance;
  float return_distance_left;
  void movementHandler(float dt);

  void enemyAnimationHandle();
};

#endif // PLATFORMERSFML_ENEMIES_H

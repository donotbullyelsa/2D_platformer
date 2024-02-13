
#ifndef PLATFORMERSFML_BULLET_H
#define PLATFORMERSFML_BULLET_H

#include "Rigidbody.h"

class Bullet: public Rigidbody
{
 public:
  Bullet();
  void init();
};

#endif // PLATFORMERSFML_BULLET_H

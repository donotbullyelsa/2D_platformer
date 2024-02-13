
#ifndef PLATFORMERSFML_VECTOR2_H
#define PLATFORMERSFML_VECTOR2_H

#include <math.h>

class Vector2
{
 public:
  Vector2(float x_, float y_);
  float x;
  float y;
  float magnitude;

  Vector2 normalise();

};

#endif // PLATFORMERSFML_VECTOR2_H

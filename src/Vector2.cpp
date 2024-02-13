
#include "Vector2.h"

Vector2::Vector2(float x_, float y_)
{
  x = x_;
  y = y_;
  magnitude = sqrt((x * x) + (y * y));
}

Vector2 Vector2::normalise()
{
  return Vector2(x / magnitude, y / magnitude);
}
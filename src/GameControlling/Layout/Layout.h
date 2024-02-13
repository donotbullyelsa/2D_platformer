
#ifndef PLATFORMERSFML_LAYOUT_H
#define PLATFORMERSFML_LAYOUT_H

#include <SFML/Graphics.hpp>

enum class CollisionState
{
  // sprite2 is at the ___ of sprite1 in the function
  None = 0,
  Top = 1,
  Bottom = 2,
  Left = 3,
  Right = 4
};

namespace Layout
{
  const int WINX = 1080;
  const int WINY = 720;
  void goto_middle(sf::Sprite& sprite);
  void goto_middle(sf::Text& text);
  sf::Vector2f getCenter(const sf::Sprite& sprite);
  bool collisionDetection(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
  CollisionState collisionDetectionSide(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
  bool isBetweenX(const sf::Sprite& target, const sf::Sprite& detected);
  bool isBetweenX(sf::Vector2f vertex, const sf::Sprite& detected);
  bool isBetweenY(const sf::Sprite& target, const sf::Sprite& detected);
}

#endif // PLATFORMERSFML_LAYOUT_H


#include "Layout.h"

void Layout::goto_middle(sf::Sprite& sprite)
{
  sprite.setPosition((WINX - sprite.getGlobalBounds().width) / 2, (WINY - sprite.getGlobalBounds().height) / 2);
}

void Layout::goto_middle(sf::Text& text)
{
  text.setPosition((WINX - text.getGlobalBounds().width) / 2, (WINY - text.getGlobalBounds().height) / 2);
}

sf::Vector2f Layout::getCenter(const sf::Sprite& sprite)
{
  return {sprite.getPosition().x + sprite.getGlobalBounds().width / 2, sprite.getPosition().y + sprite.getGlobalBounds().height / 2};
}

bool Layout::collisionDetection(const sf::Sprite& sprite1, const sf::Sprite& sprite2)
{
  // get sprite bounds
  sf::FloatRect bounds1 = sprite1.getGlobalBounds();
  sf::FloatRect bounds2 = sprite2.getGlobalBounds();

  // check if they intersect
  bool collisionX = bounds1.left < bounds2.left + bounds2.width && bounds1.left + bounds1.width > bounds2.left;
  bool collisionY = bounds1.top < bounds2.top + bounds2.height && bounds1.top + bounds1.height > bounds2.top;

  return collisionX && collisionY;
}

CollisionState Layout::collisionDetectionSide(const sf::Sprite& sprite1, const sf::Sprite& sprite2)
{
  // simple collision check
  if (!collisionDetection(sprite1, sprite2))
  {
    return CollisionState::None;
  }
  
  // calculate the relative positions of the sprites
  float overlapTop = sprite2.getGlobalBounds().top + sprite2.getGlobalBounds().height - sprite1.getGlobalBounds().top;
  float overlapBottom = sprite1.getGlobalBounds().top + sprite1.getGlobalBounds().height - sprite2.getGlobalBounds().top;
  float overlapLeft = sprite2.getGlobalBounds().left + sprite2.getGlobalBounds().width - sprite1.getGlobalBounds().left;
  float overlapRight = sprite1.getGlobalBounds().left + sprite1.getGlobalBounds().width - sprite2.getGlobalBounds().left;

  // determine the side of collision
  CollisionState side = CollisionState::None;
  float minOverlap = std::min({overlapTop, overlapBottom, overlapLeft, overlapRight});
  if (minOverlap == overlapTop)
  {
    side = CollisionState::Top;
  }
  else if (minOverlap == overlapBottom)
  {
    side = CollisionState::Bottom;
  }
  else if (minOverlap == overlapLeft)
  {
    side = CollisionState::Left;
  }
  else if (minOverlap == overlapRight)
  {
    side = CollisionState::Right;
  }

  return side;
}

bool Layout::isBetweenX(const sf::Sprite& target, const sf::Sprite& detected)
{
  if ((target.getGlobalBounds().width + target.getGlobalBounds().left < detected.getPosition().x) || (target.getGlobalBounds().left > detected.getGlobalBounds().left + detected.getGlobalBounds().width))
  {
    return false;
  }
  return true;
}

bool Layout::isBetweenX(sf::Vector2f vertex, const sf::Sprite& detected)
{
  if ((vertex.x < detected.getPosition().x) || (vertex.x > detected.getGlobalBounds().left + detected.getGlobalBounds().width))
  {
    return false;
  }
  return true;
}

bool Layout::isBetweenY(const sf::Sprite& target, const sf::Sprite& detected)
{
  if ((target.getGlobalBounds().height + target.getGlobalBounds().top < detected.getPosition().y) || (target.getGlobalBounds().top > detected.getGlobalBounds().top + detected.getGlobalBounds().height))
  {
    return false;
  }
  return true;
}
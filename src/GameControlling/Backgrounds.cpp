
#include "Backgrounds.h"

void Backgrounds::init()
{
  for (int i=0; i<2; i++)
  {
    if (!bg_texture[i].loadFromFile("Data/Images/lvl1.png"))
    {
      std::cout << "Error: Failed to load background.";
    }
    background[i] = sf::Sprite();
    background[i].setTexture(bg_texture[i]);
    background[i].setPosition(0, 0);
  }
  background[1].move(-background[0].getGlobalBounds().width, 0);

  player_at = 0;
  at_left = true;
}
void Backgrounds::update(float dt, float playerX)
{
  // calculate the player_at
  if (Layout::isBetweenX({playerX, 0}, background[0]))
  {
    player_at = 0;
  }
  else
  {
    player_at = 1;
  }

  // calculate the at_left
  if (playerX < background[player_at].getPosition().x + background[player_at].getGlobalBounds().width / 2)
  {
    at_left = true;
  }
  else
  {
    at_left = false;
  }

  if ((at_left) && (background[!player_at].getPosition().x > background[player_at].getPosition().x))
  {
    background[!player_at].move(-background[!player_at].getGlobalBounds().width * 2, 0);
  }
  else if ((!at_left) && (background[!player_at].getPosition().x < background[player_at].getPosition().x))
  {
    background[!player_at].move(background[!player_at].getGlobalBounds().width * 2, 0);
  }
}

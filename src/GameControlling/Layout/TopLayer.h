
#ifndef PLATFORMERSFML_TOPLAYER_H
#define PLATFORMERSFML_TOPLAYER_H

#include "Layout.h"
#include "Time.h"
#include "../Setting.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class TopLayer
{
 public:
  void init();
  void update(int score, int lives_num, int time, sf::Vector2f view);
  void render(sf::RenderWindow& window);

 private:
  const static Setting game_setting;

  sf::Text scoreboard;
  sf::Font std_font;
  void initScoreboard();

  sf::Sprite lives[Setting::PLAYER_LIVES];
  sf::Texture lives_texture;
  sf::IntRect lives_texture_rect;
  sf::IntRect death_texture_rect;
  int lives_left;
  void initLives();

  sf::Text time_text;
  void initClock();
};

#endif // PLATFORMERSFML_TOPLAYER_H

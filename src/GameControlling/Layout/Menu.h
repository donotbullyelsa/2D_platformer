
#ifndef PLATFORMERSFML_MENU_H
#define PLATFORMERSFML_MENU_H

#include "Layout.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Menu
{
 public:
  void init();
  void update();
  void render(sf::RenderWindow& window);
  int keyPressed(sf::Event event);

  bool choose_ability;

 private:
  sf::Font std_font;

  void initChoices();
  void initTitle();
  sf::Text title_text;
  sf::Text choices_text[3];
  int choice;

  void initBG();
  sf::Sprite bg;
  sf::Texture bg_texture;
  sf::IntRect bg_texture_rect;
  sf::View menu_view;
};

#endif // PLATFORMERSFML_MENU_H

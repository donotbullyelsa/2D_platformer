
#ifndef PLATFORMERSFML_ENDSTATE_H
#define PLATFORMERSFML_ENDSTATE_H

#include "Menu.h"
#include "../../FileHandling.h"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

class EndState
{
 public:
  EndState(bool won_, int score, std::string time);
  EndState();
  void init();
  void update();
  void render(sf::RenderWindow& window);
  int keyPressed(sf::Event event);

  std::string user_input;

 private:
  bool won;
  sf::Font std_font;

  void initChoices();
  void initScore();
  void initTitle();
  sf::Text state_text;
  sf::Text score_text;
  int final_score;
  sf::Text time_text;
  std::string time_used;

  sf::Text choices_text[2];
  int choice;

  void initBG();
  sf::Sprite bg;
  sf::Texture bg_texture;
  sf::IntRect bg_texture_rect;
  sf::View end_view;

  void initTextInput();
  sf::Text text_input;
};

#endif // PLATFORMERSFML_ENDSTATE_H


#ifndef PLATFORMERSFML_HIGHSCORE_H
#define PLATFORMERSFML_HIGHSCORE_H

#include "Layout.h"
#include "../../FileHandling.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Highscore
{
 public:
  ~Highscore();
  void init();
  void update();
  void render(sf::RenderWindow& window);

  void deleteAll();
  int page_num;

 private:
  sf::Font std_font;

  void initTitle();
  sf::Text title_text;

  void initBG();
  sf::Sprite bg;
  sf::Texture bg_texture;
  sf::IntRect bg_texture_rect;
  sf::View menu_view;

  void initScores();
  void updateScores();
  int score_count;
  const static int MAX_RECORD_NUM = 9999;
  int* scores[MAX_RECORD_NUM];
  std::string* names[MAX_RECORD_NUM];
  sf::Text scores_texts[21];

  void sort();
  void swap(int index1, int index2);
};

#endif // PLATFORMERSFML_HIGHSCORE_H

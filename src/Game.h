
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include "GameControlling/Backgrounds.h"
#include "GameControlling/Gamestates.h"
#include "GameControlling/Setting.h"
#include "GameControlling/Layout/Level.h"
#include "GameControlling/Layout/Menu.h"
#include "GameControlling/Layout/TopLayer.h"
#include "GameControlling/Layout/EndState.h"
#include "GameControlling/Layout/Highscore.h"
#include "Objects/Player.h"
#include "Objects/Tile.h"
#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void keyReleased(sf::Event event);
  void textEntered(sf::Event event);

 private:
  sf::RenderWindow& window;
  void halt();
  void reset();

  Backgrounds bg_controller;
  sf::View view;
  void updateCamera();

  Player player;
  void playerCollideHandler();
  bool bringBackHandler(Player& character, Tile& terrain);
  bool playerBringBackX(Player& character, Tile& terrain);
  bool playerBringBackY(Player& character, Tile& terrain);
  void playerDieHandler();
  void starCollector();
  void enemyCollideHandler();
  void boundaryHandler();

  Menu menu;
  TopLayer top_layer;
  EndState end_state;
  Highscore highscore_board;

  sf::Clock level_clock;
  Level level;
  Gamestates gamestates;
  Setting game_setting;
};

#endif // PLATFORMER_GAME_H

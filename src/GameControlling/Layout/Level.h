
#ifndef PLATFORMERSFML_LEVEL_H
#define PLATFORMERSFML_LEVEL_H

#include "../../Objects/Enemies.h"
#include "../../Objects/Bullet.h"
#include "../../Objects/Player.h"
#include "../../Objects/Stars.h"
#include "../../Objects/Tile.h"
#include <SFML/Graphics.hpp>

class Level
{
 public:
  Level();
  ~Level();

  const int GROUND_POSITION = 960;
  void init();
  void initGround();
  void initLevel();
  void initEnemies();

  void update(float dt, Bullet* &bullet);
  void updateBullet(float dt, Bullet* &bullet);
  const int BULLET_SPEED = 1000;
  void render(sf::RenderWindow& window);

  Tile* getTile(const sf::Sprite& player);
  static const int BLOCK_NUM = 80; // total num of blocks = 57
  Tile block[BLOCK_NUM];
  const int BLOCK_SIZE = 70;

  static const int GROUND_NUM = 12;
  Tile ground[GROUND_NUM];

  static const int STAR_NUM = 30; // total num of stars = 25
  static const int STAR_SCORE = 100;
  Stars stars[STAR_NUM];

  static const int ENEMY_NUM = 20;
  Enemies* enemies[ENEMY_NUM];
  void deleteTempMemory();
};

#endif // PLATFORMERSFML_LEVEL_H

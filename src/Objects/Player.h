
#ifndef PLATFORMERSFML_PLAYER_H
#define PLATFORMERSFML_PLAYER_H

#include "Gameobjects.h"
#include "Rigidbody.h"
#include "Bullet.h"
#include "../GameControlling/Setting.h"
#include "../GameControlling/Abilities.h"
#include "Tile.h"

class Player: public Rigidbody
{
 public:
  Player();
  ~Player();
  void init();
  void update(float dt) override;
  void lateUpdate(float dt);

  Tile* collide_wall;
  bool can_jump;
  bool pressed_walk;
  bool to_be_stopped;

  bool invisible;
  void addInvisTime(int time);

  Bullet* bullet;
  const int BULLET_SPEED = 1000;
  sf::Clock ability_clock;
  bool use_ability_flag;
  void abilityHandler(float dt);

  int score;
  int lives;
  Abilities ability;
  bool first_flag;
  Setting game_setting;

 private:
  void playerUpdateAnimation();
  void invisHandler(float dt);
  sf::Clock invis_clock;
  float invis_limit;
  float invis_time;

  void wallCollideHandler();
  void gravityHandler(float dt);
  const int PLAYER_SPEED = 500;
  const float GRAVITY = 8.0f;
};

#endif // PLATFORMERSFML_PLAYER_H

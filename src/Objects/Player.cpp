
#include "Player.h"

Player::Player(): Rigidbody("Data/kenney_pixelplatformer/Tilemap/characters_packed.png")
{
  this->init();
}

void Player::init()
{
  sprite.setScale(2.0f, 2.0f);
  Layout::goto_middle(sprite);
  texture_rect1 = sf::IntRect(145, 0, 22, 24);
  texture_rect2 = texture_rect1;
  texture_rect2.left += texture_rect1.width + 3;
  sprite.setTextureRect(texture_rect1);
  facing_right = false;
  last_facing = false;
  in_walk = false;
  pressed_walk = false;
  on_ground = nullptr;
  collide_wall = nullptr;
  can_jump = false;
  to_be_stopped = false;
  direction.y = 1;
  score = 0;
  lives = Setting::PLAYER_LIVES;
  invisible = false;
  invis_time = 0;
  ability_clock.restart();
  use_ability_flag = false;
  bullet = nullptr;
  first_flag = true;
}

Player::~Player()
{
  delete bullet;
}

void Player::update(float dt)
{
  // update the walking animation
  playerUpdateAnimation();

  // update ability cooldown clock
  abilityHandler(dt);

  // update invisibility state
  invisHandler(dt);

  // check if the player has left the wall it was colliding
  wallCollideHandler();

  // update the position
  sprite.move(direction.x * PLAYER_SPEED * dt, direction.y * PLAYER_SPEED * dt);

  // if player on ground then reset gravity
  gravityHandler(dt);
}

void Player::lateUpdate(float dt)
{
  can_jump = false;
  // if player leave the platform
  if (on_ground != nullptr)
  {
    if (
      (Layout::isBetweenX(sprite, *on_ground->getSprite())) &&
      (sprite.getPosition().y + sprite.getGlobalBounds().height ==
       on_ground->getSprite()->getPosition().y))
    {
      can_jump = true;
    }
  }
}

void Player::playerUpdateAnimation()
{
  // handling if player face left or right
  if (last_facing != facing_right)
  {
    sprite.setScale(sprite.getScale().x * -1, sprite.getScale().y);
    if (facing_right)
    {
      if (collide_wall != nullptr)
      {
        if (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width * 2 > collide_wall->getSprite()->getPosition().x)
        {
          sprite.setPosition(
            collide_wall->getSprite()->getPosition().x,
            sprite.getPosition().y);
        }
      }
      else
      {
        sprite.move(sprite.getGlobalBounds().width, 0);
      }
    }
    else
    {
      if (collide_wall != nullptr)
      {
        if (sprite.getPosition().x + sprite.getGlobalBounds().width > collide_wall->getSprite()->getPosition().x)
        {
          sprite.setPosition(
            collide_wall->getSprite()->getPosition().x - sprite.getGlobalBounds().width,
            sprite.getPosition().y);
        }
      }
      else
      {
        sprite.move(-sprite.getGlobalBounds().width, 0);
      }
    }
    collide_wall = nullptr;
  }

  // if player moving, update the animation
  if (direction.x != 0)
  {
    updateAnimation();
  }
  else
  {
    sprite.setTextureRect(texture_rect1);
    in_walk      = false;
    animation_clock.restart();
  }

  // update the value of facing_right in the last frame
  last_facing = facing_right;
}

void Player::abilityHandler(float dt)
{
  // update bullet
  if (bullet != nullptr)
  {
    bullet->getSprite()->move(dt * BULLET_SPEED * bullet->direction.x, 0);
    if (abs(bullet->getSprite()->getPosition().x - sprite.getPosition().x) > Layout::WINX / 2 + 20)
    {
      delete bullet;
      bullet = nullptr;
    }
  }

  // use ability
  if (use_ability_flag)
  {
    switch (ability)
    {
      case Abilities::BULLET:
      {
        if (((ability_clock.getElapsedTime().asSeconds() >= Setting::BULLET_COOLDOWN) || (first_flag)) && (bullet == nullptr))
        {
          first_flag = false;
          bullet = new Bullet();
          bullet->getSprite()->setPosition(sprite.getPosition());
          bullet->getSprite()->move(0, 20);
          if (facing_right)
          {
            bullet->direction.x = 1;
          }
          else
          {
            bullet->direction.x = -1;
          }
          ability_clock.restart();
        }
        break;
      }
      case Abilities::INVIS:
      {
        if ((ability_clock.getElapsedTime().asSeconds() >= Setting::INVIS_COOLDOWN) || (first_flag))
        {
          first_flag = false;
          addInvisTime(Setting::INVIS_ABILITY_TIME);
          ability_clock.restart();
        }
        break;
      }
    }
  }

  use_ability_flag = false;
}

void Player::invisHandler(float dt)
{
  if (invis_limit > 0)
  {
    if (invis_clock.getElapsedTime().asSeconds() > invis_limit)
    {
      invis_clock.restart();
      invis_limit = 0;
      invis_time = 0;
      invisible = false;

      sf::Color sprite_colour = sprite.getColor();
      sprite_colour.a = 255;
      sprite.setColor(sprite_colour);
    }
    else
    {
      invisible = true;
      invis_time += dt;
      sf::Color sprite_colour = sprite.getColor();
      if (invis_time > 0.5)
      {
        invis_time = 0;
        sprite_colour.a = 0;
      }
      else
      {
        sprite_colour.a += dt / 0.5 * 255;
      }
      sprite.setColor(sprite_colour);
    }
  }
  else
  {
    invisible = false;
    invis_clock.restart();
    invis_time = 0;
  }
}

void Player::addInvisTime(int time)
{
  invis_limit += time;
}

void Player::wallCollideHandler()
{
  if (collide_wall != nullptr)
  {
    if (!Layout::isBetweenY(sprite, *collide_wall->getSprite()))
    {
      collide_wall = nullptr;
      if (pressed_walk)
      {
        if (facing_right)
        {
          direction.x = 1;
        }
        else
        {
          direction.x = -1;
        }
      }
    }
  }
}

void Player::gravityHandler(float dt)
{
  if (can_jump)
  {
    if (!Layout::isBetweenX(sprite, *on_ground->getSprite()))
    {
      // add gravity
      can_jump = false;
      direction.y += GRAVITY * dt;
    }
    else
    {
      // stop gravity
      direction.y = 0.0f;

      // handling the curve motion
      // if touched the floor, horizontal motion stopped (friction)
      if (to_be_stopped)
      {
        direction.x   = 0;
        to_be_stopped = false;
      }
    }
  }
  else
  {
    // add gravity
    direction.y += GRAVITY * dt;
  }
}

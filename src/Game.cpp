
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{

}

bool Game::init()
{
  gamestates = Gamestates::IN_MENU;

  reset();
  return true;
}

void Game::reset()
{
  menu.init();
  end_state.init();

  level.deleteTempMemory();
  level.init();

  player.init();
  player.getSprite()->setPosition(-50, level.GROUND_POSITION - player.getSprite()->getGlobalBounds().height);

  bg_controller.init();
  view = sf::View(sf::FloatRect(0.f, 0.f, window.getSize().x, window.getSize().y));
  view.setCenter(Layout::getCenter(*player.getSprite()).x, Layout::getCenter(*player.getSprite()).y - 300);

  top_layer.init();
  highscore_board.init();
}

void Game::update(float dt)
{
  switch (gamestates)
  {
    case Gamestates::IN_MENU:
    {
      menu.update();
      break;
    }
    case Gamestates::IN_GAME:
    {
      // update the objects
      player.update(dt);
      level.update(dt, player.bullet);
      bg_controller.update(dt, player.getSprite()->getPosition().x);

      // check if player step on something
      player.on_ground = level.getTile(*player.getSprite());

      // check if player collide on something
      playerCollideHandler();

      // check if player is out of the level boundary
      if (Setting::BOUNDARY_ENABLED)
      {
        boundaryHandler();
      }

      // check if player is dead (or win)
      playerDieHandler();

      // check if player collide with a star
      starCollector();

      // update the camera
      updateCamera();

      // update scoreboard
      top_layer.update(player.score, player.lives, level_clock.getElapsedTime().asMilliseconds(), view.getCenter());

      // some data of player have to be updated here
      player.lateUpdate(dt);

      break;
    }
    case Gamestates::WON:
    case Gamestates::LOST:
    {
      end_state.update();
      break;
    }
    case Gamestates::HS:
    {
      highscore_board.update();
      break;
    }
  }
}

void Game::updateCamera()
{
  view.setCenter(Layout::getCenter(*player.getSprite()).x, view.getCenter().y);
  window.setView(view);
}

bool Game::playerBringBackX(Player& character, Tile& terrain)
{
  if (character.direction.x > 0)
  {
    character.getSprite()->setPosition(
      terrain.getSprite()->getGlobalBounds().left,
      character.getSprite()->getPosition().y);
    character.direction.x = 0;
    character.collide_wall = &terrain;
    return true;
  }
  else if (character.direction.x < 0)
  {
    character.getSprite()->setPosition(
      terrain.getSprite()->getGlobalBounds().left +
        terrain.getSprite()->getGlobalBounds().width,
      character.getSprite()->getPosition().y);
    character.direction.x = 0;
    character.collide_wall = &terrain;
    return true;
  }
  return false;
}

bool Game::playerBringBackY(Player& character, Tile& terrain)
{
  if (character.direction.y > 0)
  {
    character.getSprite()->setPosition(
      character.getSprite()->getPosition().x,
      terrain.getSprite()->getGlobalBounds().top -
        character.getSprite()->getGlobalBounds().height);
    character.direction.y = 0;
    return true;
  }
  else if (character.direction.y < 0)
  {
    character.getSprite()->setPosition(
      character.getSprite()->getPosition().x,
      terrain.getSprite()->getGlobalBounds().top +
        terrain.getSprite()->getGlobalBounds().height);
    character.direction.y = 0;
    return true;
  }
  return false;
}

void Game::playerCollideHandler()
{
  bool collided_flag = false;
  for (int i=0; i<level.BLOCK_NUM; i++)
  {
    if (!collided_flag)
    {
      collided_flag = bringBackHandler(player, level.block[i]);
    }
  }
  for (int i=0; i<level.GROUND_NUM; i++)
  {
    if (!collided_flag)
    {
      collided_flag = bringBackHandler(player, level.ground[i]);
    }
  }
}

bool Game::bringBackHandler(Player& character, Tile& terrain)
{
  {
    if ((Layout::collisionDetection(*terrain.getSprite(), *character.getSprite())) && (terrain.existance))
    {
      // if collided with the block, bring the player back to the position
      // that it belongs to
      CollisionState state = Layout::collisionDetectionSide(
        *terrain.getSprite(), *character.getSprite());
      bool done_flag = false;
      if ((state == CollisionState::Bottom) || (state == CollisionState::Top))
      {
        done_flag = playerBringBackY(character, terrain);
        if (done_flag)
        {
          return done_flag;
        }
        done_flag = playerBringBackX(character, terrain);
        if (done_flag)
        {
          return done_flag;
        }
      }
      else
      {
        done_flag = playerBringBackX(character, terrain);
        if (done_flag)
        {
          return done_flag;
        }
        done_flag = playerBringBackY(character, terrain);
        if (done_flag)
        {
          return done_flag;
        }
      }
    }
  }
  return false;
}

void Game::boundaryHandler()
{
  if (player.getSprite()->getPosition().x < level.ground[0].getSprite()->getPosition().x)
  {
    player.getSprite()->setPosition(level.ground[0].getSprite()->getPosition().x, player.getSprite()->getPosition().y);
  }
}

void Game::playerDieHandler()
{
  // fall into void
  if (player.getSprite()->getPosition().y > view.getCenter().y + Layout::WINY / 2)
  {
    int time_used = level_clock.getElapsedTime().asMilliseconds();
    end_state = EndState(false, player.score - time_used / 100, Time::time_to_string(time_used));
    reset();
    gamestates = Gamestates::LOST;
  }

  // collide with enemy
  else if (Setting::DAMAGE_ENABLED)
  {
    enemyCollideHandler();
  }

  // collect all stars
  bool flag = false;
  for (int i = 0; i < level.STAR_NUM; i++)
  {
    if (level.stars[i].existance)
    {
      flag = true;
    }
  }
  if (!flag)
  {
    int time_used = level_clock.getElapsedTime().asMilliseconds();
    end_state = EndState(true, player.score - time_used / 100, Time::time_to_string(time_used));
    reset();
    gamestates = Gamestates::WON;
  }
}

void Game::starCollector()
{
  for (int i=0; i<level.STAR_NUM; i++)
  {
    if ((Layout::collisionDetection(*level.stars[i].getSprite(), *player.getSprite())) && (level.stars[i].existance))
    {
      level.stars[i].existance = false;
      player.score += level.STAR_SCORE;
    }
  }
}

void Game::enemyCollideHandler()
{
  bool flag = false;
  for (int i=0; i<level.ENEMY_NUM; i++)
  {
    if ((level.enemies[i] != nullptr))
    {
      if ((Layout::collisionDetection(*level.enemies[i]->getSprite(), *player.getSprite())) && (level.enemies[i]->existance) && (!player.invisible))
      {
        player.lives--;
        if (player.lives <= 0)
        {
          flag = true;
        }
        else
        {
          player.addInvisTime(Setting::PLAYER_INVIS_TIME);
        }
      }
    }
  }
  if (flag)
  {
    int time_used = level_clock.getElapsedTime().asMilliseconds();
    end_state = EndState(false, player.score - time_used / 100, Time::time_to_string(time_used));
    reset();
    gamestates = Gamestates::LOST;
  }
}

void Game::render()
{
  switch (gamestates)
  {
    case Gamestates::IN_MENU:
    {
      menu.render(window);
      break;
    }
    case Gamestates::IN_GAME:
    {
      for (int i=0; i<2; i++)
      {
        window.draw(bg_controller.background[i]);
      }
      level.render(window);
      if (player.existance)
      {
        window.draw(*player.getSprite());
      }
      if (player.bullet != nullptr)
      {
        window.draw(*player.bullet->getSprite());
      }
      top_layer.render(window);
      break;
    }
    case Gamestates::WON:
    case Gamestates::LOST:
    {
      end_state.render(window);
      break;
    }
    case Gamestates::HS:
    {
      highscore_board.render(window);
      break;
    }
  }
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);
}

void Game::keyPressed(sf::Event event)
{
  switch (gamestates)
  {
    case Gamestates::IN_MENU:
    {
      int n = menu.keyPressed(event);
      switch (n)
      {
        case 0:
        {
          menu.choose_ability = true;
          break;
        }
        case 1:
        {
          halt();
          break;
        }
        case 2:
        {
          highscore_board.init();
          gamestates = Gamestates::HS;
          break;
        }
        case 3:
        {
          gamestates = Gamestates::IN_GAME;
          level_clock.restart();
          player.ability = Abilities::BULLET;
          break;
        }
        case 4:
        {
          gamestates = Gamestates::IN_GAME;
          level_clock.restart();
          player.ability = Abilities::INVIS;
          break;
        }
      }
      break;
    }

    case Gamestates::IN_GAME:
    {
      if (
        (event.key.code == sf::Keyboard::A) ||
        (event.key.code == sf::Keyboard::Left))
      {
        player.direction.x  = -1;
        player.facing_right = false;
        player.pressed_walk = true;
        player.in_walk      = true;
      }
      else if (
        (event.key.code == sf::Keyboard::D) ||
        (event.key.code == sf::Keyboard::Right))
      {
        player.direction.x  = 1;
        player.facing_right = true;
        player.pressed_walk = true;
        player.in_walk      = true;
      }
      else if (event.key.code == sf::Keyboard::Space)
      {
        if (player.can_jump)
        {
          player.direction.y = -3;
          player.can_jump    = false;
        }
      }
      else if (event.key.code == sf::Keyboard::K)
      {
        player.use_ability_flag = true;
      }
      break;
    }

    case Gamestates::WON:
    case Gamestates::LOST:
    {
      int n = end_state.keyPressed(event);
      if (n == 0)
      {
        gamestates = Gamestates::IN_GAME;
        level_clock.restart();
      }
      else if (n == 1)
      {
        gamestates = Gamestates::IN_MENU;
      }
      break;
    }
    case Gamestates::HS:
    {
      if (event.key.code == sf::Keyboard::Enter)
      {
        highscore_board.deleteAll();
        gamestates = Gamestates::IN_MENU;
      }
      else if (event.key.code == sf::Keyboard::Up)
      {
        highscore_board.page_num--;
      }
      else if (event.key.code == sf::Keyboard::Down)
      {
        highscore_board.page_num++;
      }
      break;
    }
  }
}

void Game::keyReleased(sf::Event event)
{
  if (
    ((event.key.code == sf::Keyboard::A) ||
     (event.key.code == sf::Keyboard::Left)) ||
    ((event.key.code == sf::Keyboard::D) ||
     (event.key.code == sf::Keyboard::Right)))
  {
    // FOR TESTING
    player.direction.x = 0;
    player.pressed_walk = false;
    player.in_walk = false;

    if (player.on_ground)
    {
      player.direction.x = 0;
    }
    else
    {
      player.to_be_stopped = true;
    }
  }
}

void Game::halt()
{
  level.deleteTempMemory();
  std::exit(4);
}

void Game::textEntered(sf::Event event)
{
  if ((gamestates == Gamestates::WON) || (gamestates == Gamestates::LOST))
  {
    if (event.text.unicode < 128)
    {
      // get text input to std::string
      if (event.text.unicode == 8)
      {
        end_state.user_input.pop_back();
      }
      else if (event.text.unicode != 27)
      {
        end_state.user_input += static_cast<char>(event.text.unicode);
      }
    }
  }
}

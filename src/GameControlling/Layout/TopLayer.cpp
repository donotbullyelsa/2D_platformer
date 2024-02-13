
#include "TopLayer.h"

void TopLayer::init()
{
  initScoreboard();
  initLives();
  initClock();
}

void TopLayer::initScoreboard()
{
  if (!std_font.loadFromFile("Data/Fonts/open-sans/OpenSans-BoldItalic.ttf"))
  {
    std::cout << "Error: Fail to load font.";
  }

  scoreboard.setFillColor(sf::Color::Red);
  scoreboard.setFont(std_font);
}

void TopLayer::initLives()
{
  if (!lives_texture.loadFromFile("Data/kenney_pixelplatformer/Tilemap/tiles_packed.png"))
  {
    std::cout << "Error: Fail to load life images.";
  }

  lives_texture_rect = sf::IntRect(72, 36, 18, 18);
  death_texture_rect = lives_texture_rect;
  death_texture_rect.left += 18 * 2;

  for (int i=0; i<game_setting.PLAYER_LIVES; i++)
  {
    lives[i].setTexture(lives_texture);
    lives[i].setTextureRect(lives_texture_rect);
    lives[i].setScale(2.0f, 2.0f);
  }

  lives_left = Setting::PLAYER_LIVES;
}

void TopLayer::initClock()
{
  time_text.setFont(std_font);
  time_text.setFillColor(scoreboard.getFillColor());
}

void TopLayer::update(int score, int lives_num, int time, sf::Vector2f view)
{
  lives_left = lives_num;

  scoreboard.setPosition(view.x + Layout::WINX / 2 - 50 - scoreboard.getGlobalBounds().width, view.y - Layout::WINY / 2 + 50);
  scoreboard.setString("Score:" + std::to_string(score));

  for (int i=0; i<game_setting.PLAYER_LIVES; i++)
  {
    lives[i].setPosition(scoreboard.getPosition());
    lives[i].move(-lives[i].getGlobalBounds().width * (i + 1) + scoreboard.getGlobalBounds().width, 50);
    if (i + 1 > lives_left)
    {
      lives[i].setTextureRect(death_texture_rect);
    }
    else
    {
      lives[i].setTextureRect(lives_texture_rect);
    }
  }

  time_text.setPosition(scoreboard.getPosition());
  time_text.move(scoreboard.getGlobalBounds().width - time_text.getGlobalBounds().width, -time_text.getGlobalBounds().height - 20);
  time_text.setString("Time used: " + Time::time_to_string(time));
}

void TopLayer::render(sf::RenderWindow& window)
{
  window.draw(scoreboard);
  window.draw(time_text);
  for (int i=0; i<game_setting.PLAYER_LIVES; i++)
  {
    window.draw(lives[i]);
  }
}
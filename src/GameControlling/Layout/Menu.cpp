
#include "Menu.h"

void Menu::init()
{
  // loaf font
  if (!std_font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Error: Fail to load font.";
  }

  // init title
  initTitle();

  // init choices
  initChoices();

  // init background
  initBG();

  menu_view = sf::View(sf::FloatRect(0.f, 0.f, Layout::WINX, Layout::WINY));
}

void Menu::initChoices()
{
  for (int i=0; i<3; i++)
  {
    choices_text[i].setFont(std_font);
    choices_text[i].setCharacterSize(30);
    choices_text[i].setFillColor(sf::Color::Red);
  }
  choices_text[0].setString("Start! <<");
  choices_text[1].setString("Quit!");
  choices_text[2].setString("High scores!");
  Layout::goto_middle(choices_text[0]);

  choice = 0;
  choose_ability = false;
}

void Menu::initTitle()
{
  title_text.setFont(std_font);
  title_text.setString("The Platformer Game");
  title_text.setCharacterSize(80);
  title_text.setFillColor(sf::Color::Blue);
  Layout::goto_middle(title_text);
  title_text.move(0, -100);
}

void Menu::initBG()
{
  if (!bg_texture.loadFromFile("Data/Images/lvl1.png"))
  {
    std::cout << "Error: Fail to load menu background.";
  }
  bg_texture_rect = {0, 0, Layout::WINX, Layout::WINY};
  bg.setTextureRect(bg_texture_rect);
  bg.setTexture(bg_texture);
}

void Menu::update()
{
  if (!choose_ability)
  {
    choices_text[0].setString("Start!");
    choices_text[1].setString("Quit!");
    choices_text[2].setString("High scores!");
    title_text.setString("The Platformer Game");
    Layout::goto_middle(title_text);
    title_text.move(0, -100);
  }

  else
  {
    choices_text[0].setString("Shoot a bullet. Cooldown: 3s");
    choices_text[1].setString("Invisibility. Cooldown: 10s");
    title_text.setString("Choose your ability.");
    Layout::goto_middle(title_text);
    title_text.move(0, -100);
  }

  Layout::goto_middle(choices_text[0]);
  choices_text[0].setFillColor(sf::Color::Red);
  for (int i=1; i<3; i++)
  {
    Layout::goto_middle(choices_text[i]);
    choices_text[i].setPosition(choices_text[i].getPosition().x, choices_text[i - 1].getPosition().y);
    choices_text[i].move(0, 40);
    choices_text[i].setFillColor(sf::Color::Red);
  }
  choices_text[choice].setString(choices_text[choice].getString() + " <<");
  choices_text[choice].setFillColor(sf::Color::Yellow);

  menu_view.setCenter(Layout::WINX / 2, Layout::WINY / 2);
}

void Menu::render(sf::RenderWindow& window)
{
  window.draw(bg);
  window.draw(title_text);
  for (int i=0; i<3; i++)
  {
    if (i == 2)
    {
      if (!choose_ability)
      {
        window.draw(choices_text[i]);
      }
    }
    else
    {
      window.draw(choices_text[i]);
    }
  }
  window.setView(menu_view);
}

int Menu::keyPressed(sf::Event event)
{
  if ((event.key.code == sf::Keyboard::Up) || (event.key.code == sf::Keyboard::W))
  {
    choice -= 1;
    if (choose_ability)
    {
      if (choice < 0)
      {
        choice = 1;
      }
    }
    else
    {
      if (choice < 0)
      {
        choice = 2;
      }
    }
  }
  else if ((event.key.code == sf::Keyboard::Down) || (event.key.code == sf::Keyboard::S))
  {
    choice += 1;
    if (choose_ability)
    {
      if (choice > 1)
      {
        choice = 0;
      }
    }
    else
    {
      if (choice > 2)
      {
        choice = 0;
      }
    }
  }
  else if (event.key.code == sf::Keyboard::Enter)
  {
    if (!choose_ability)
    {
      return choice;
    }
    else
    {
      return choice + 3;
    }
  }
  return -1;
}


#include "EndState.h"

EndState::EndState(bool won_, int score, std::string time)
{
  won = won_;
  final_score = score;
  time_used = time;
}

EndState::EndState()
{
  won = true;
  final_score = 0;
  time_used = 0.0f;
}

void EndState::init()
{
  // loaf font
  if (!std_font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Error: Fail to load font.";
  }

  // init text input
  initTextInput();

  // init title
  initTitle();

  // init score and time used
  initScore();

  // init background
  initBG();

  // init choices
  initChoices();

  end_view = sf::View(sf::FloatRect(0.f, 0.f, Layout::WINX, Layout::WINY));
}

void EndState::initTextInput()
{
  user_input = "";
  text_input = sf::Text(user_input, std_font, 30);
  text_input.setFillColor(sf::Color::Blue);
  text_input.setPosition(choices_text[1].getPosition());
  text_input.move(0, text_input.getGlobalBounds().height + 10);
}

void EndState::initTitle()
{
  state_text.setFont(std_font);
  state_text.setCharacterSize(60);
  state_text.setFillColor(sf::Color::Blue);
  state_text.setPosition(100, 100);
  if (won)
  {
    state_text.setString("You win!");
  }
  else
  {
    state_text.setString("You lose.");
  }
}

void EndState::initChoices()
{
  for (int i=0; i<2; i++)
  {
    choices_text[i].setFont(std_font);
    choices_text[i].setCharacterSize(30);
    choices_text[i].setFillColor(sf::Color::Red);
  }
  choices_text[0].setString("Start! <<");
  choices_text[1].setString("Quit!");
  choices_text[0].setPosition(time_text.getPosition());
  choices_text[0].move(0, time_text.getGlobalBounds().height + 20);
  choices_text[1].setPosition(choices_text[0].getPosition());
  choices_text[1].move(0, choices_text[0].getGlobalBounds().height + 20);
  choice = 0;
}

void EndState::initScore()
{
  // init score text
  score_text.setFont(std_font);
  score_text.setCharacterSize(40);
  score_text.setFillColor(sf::Color::Blue);
  score_text.setPosition(state_text.getPosition());
  score_text.move(0, 20 + state_text.getGlobalBounds().height);
  score_text.setString("Score: " + std::to_string(final_score));

  // init time text
  time_text.setFont(std_font);
  time_text.setCharacterSize(40);
  time_text.setFillColor(sf::Color::Blue);
  time_text.setPosition(score_text.getPosition());
  time_text.move(0, 20 + score_text.getGlobalBounds().height);
  time_text.setString("Time: " + time_used);
}

void EndState::initBG()
{
  if (!bg_texture.loadFromFile("Data/Images/lvl1.png"))
  {
    std::cout << "Error: Fail to load menu background.";
  }
  bg_texture_rect = {0, 0, Layout::WINX, Layout::WINY};
  bg.setTextureRect(bg_texture_rect);
  bg.setTexture(bg_texture);
}

void EndState::update()
{
  choices_text[0].setString("Replay");
  choices_text[1].setString("Back To Menu");
  for (int i=0; i<2; i++)
  {
    choices_text[i].setFillColor(sf::Color::Red);
  }
  choices_text[choice].setString(choices_text[choice].getString() + " <<");
  choices_text[choice].setFillColor(sf::Color::Yellow);

  end_view.setCenter(Layout::WINX / 2, Layout::WINY / 2);

  text_input.setString("Please enter your name: " + user_input);
  text_input.setPosition(choices_text[1].getPosition());
  text_input.move(0, text_input.getGlobalBounds().height + 10);
}

void EndState::render(sf::RenderWindow& window)
{
  window.draw(bg);
  window.draw(state_text);
  window.draw(score_text);
  window.draw(time_text);
  for (int i=0; i<2; i++)
  {
    window.draw(choices_text[i]);
  }
  window.draw(text_input);
  window.setView(end_view);
}

int EndState::keyPressed(sf::Event event)
{
  if (event.key.code == sf::Keyboard::Up)
  {
    choice -= 1;
    if (choice < 0)
    {
      choice = 1;
    }
  }
  else if (event.key.code == sf::Keyboard::Down)
  {
    choice += 1;
    if (choice > 1)
    {
      choice = 0;
    }
  }
  else if (event.key.code == sf::Keyboard::Enter)
  {
    FileHandling::writeFile("../game_record.txt", user_input + '\n');
    FileHandling::writeFile("../game_record.txt", std::to_string(final_score) + '\n');
    return choice;
  }
  return -1;
}


#include "Highscore.h"

Highscore::~Highscore()
{
  deleteAll();
}

void Highscore::init()
{
  deleteAll();

  // loaf font
  if (!std_font.loadFromFile("Data/Fonts/OpenSans-Bold.ttf"))
  {
    std::cout << "Error: Fail to load font.";
  }

  // init title
  initTitle();

  // init background
  initBG();

  // read the scores
  initScores();
}

void Highscore::initScores()
{
  for (int i=0; i<MAX_RECORD_NUM; i++)
  {
    scores[MAX_RECORD_NUM] = nullptr;
    names[MAX_RECORD_NUM] = nullptr;
  }

  // get the records
  score_count = 0;
  std::ifstream file;
  file.open("../game_record.txt");
  std::string line_string;
  while (getline(file, line_string))
  {
    names[score_count] = new std::string(line_string);
    getline(file, line_string);
    scores[score_count] = new int(std::stoi(line_string));
    score_count++;
  }
  file.close();

  // sort the scores
  sort();

  // init the texts
  page_num = 1;
  for (int i=0; i<10; i++)
  {
    scores_texts[i + 1].setFont(std_font);
    scores_texts[i + 1].setCharacterSize(30);
    scores_texts[i + 1].setString("");
    scores_texts[i + 1].setFillColor(sf::Color::Green);
    if (i < score_count)
    {
      scores_texts[i + 1].setString(std::to_string(i + 1) + ". " + *names[i]);
      if (i == 0)
      {
        scores_texts[i + 1].setPosition(title_text.getPosition());
        scores_texts[i + 1].move(0, 60);
      }
      else
      {
        scores_texts[i + 1].setPosition(scores_texts[i].getPosition());
        scores_texts[i + 1].move(0, 50);
      }
    }

    scores_texts[i + 11] = scores_texts[i + 1];
    scores_texts[i + 11].setString(std::to_string(*scores[i]));
    scores_texts[i + 11].setPosition(menu_view.getCenter().x + 20, scores_texts[i + 11].getPosition().y);
  }
}

void Highscore::initTitle()
{
  title_text.setFont(std_font);
  title_text.setString("High score:");
  title_text.setCharacterSize(40);
  title_text.setFillColor(sf::Color::Green);
  title_text.setPosition(100, 100);
}

void Highscore::initBG()
{
  if (!bg_texture.loadFromFile("Data/Images/lvl1.png"))
  {
    std::cout << "Error: Fail to load menu background.";
  }
  bg_texture_rect = {0, 0, Layout::WINX, Layout::WINY};
  bg.setTextureRect(bg_texture_rect);
  bg.setTexture(bg_texture);
}

void Highscore::update()
{
  updateScores();
  menu_view.setCenter(Layout::WINX / 2, Layout::WINY / 2);
}

void Highscore::updateScores()
{
  if (scores[(page_num - 1) * 10] == nullptr)
  {
    page_num = 1;
  }
  else if (page_num < 1)
  {
    do
    {
      page_num++;
    }
    while (scores[(page_num - 1) * 10] != nullptr);
    page_num--;
  }
  for (int i=0; i<10; i++)
  {
    if (names[i + (page_num - 1) * 10] == nullptr)
    {
      scores_texts[i + 1].setString("");
      scores_texts[i + 11].setString("");
    }
    else
    {
      scores_texts[i + 1].setString(std::to_string((page_num - 1) * 10 + i + 1) + ". " + *names[i + (page_num - 1) * 10]);
      scores_texts[i + 11].setString(std::to_string(*scores[i + (page_num - 1) * 10]));
    }
  }
}

void Highscore::render(sf::RenderWindow& window)
{
  window.draw(bg);
  window.draw(title_text);
  for (int i=0; i<20; i++)
  {
    window.draw(scores_texts[i + 1]);
  }
}

void Highscore::deleteAll()
{
  for (int i=0; i<MAX_RECORD_NUM; i++)
  {
    if (scores[i] != nullptr)
    {
      delete scores[i];
      scores[i] = nullptr;
    }
    if (names[i] != nullptr)
    {
      delete names[i];
      names[i] = nullptr;
    }
  }
}

void Highscore::sort()
{
  for (int i=0; i<MAX_RECORD_NUM; i++)
  {
    if (scores[i] != nullptr)
    {
      for (int j=score_count-1; j>i; j--)
      {
        if (*scores[j - 1] < *scores[j])
        {
          swap(j - 1, j);
        }
      }
    }
  }
}

void Highscore::swap(int index1, int index2)
{
  int* t = scores[index1];
  scores[index1] = scores[index2];
  scores[index2] = t;

  std::string* ts = names[index1];
  names[index1] = names[index2];
  names[index2] = ts;
}

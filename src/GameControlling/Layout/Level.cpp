
#include "Level.h"

Level::Level()
{

}

Level::~Level()
{
  deleteTempMemory();
}

Tile* Level::getTile(const sf::Sprite& player)
{
  // get all the tiles in the same vertical axis as player
  Tile* temp_list[GROUND_NUM + BLOCK_NUM];
  int t_num = 0;
  for (int i=0; i<GROUND_NUM; i++)
  {
    temp_list[i] = nullptr;

    if (Layout::isBetweenX(player, *ground[i].getSprite()))
    {
      if (ground[i].getSprite()->getPosition().y >= player.getPosition().y)
      {
        if (ground[i].existance)
        {
          temp_list[t_num] = &ground[i];
          t_num++;
        }
      }
    }
  }

  for (int i=0; i<BLOCK_NUM; i++)
  {
    if (Layout::isBetweenX(player, *block[i].getSprite()))
    {
      if (block[i].getSprite()->getPosition().y >= player.getPosition().y)
      {
        if (block[i].existance)
        {
          temp_list[t_num] = &block[i];
          t_num++;
        }
      }
    }
  }

  // if no target, return null pointer
  if (t_num == 0)
  {
    return nullptr;
  }

  // calculate the tile exactly below the player
  Tile* highest_tile = temp_list[0];
  for (int i=0; i<t_num; i++)
  {
    if (temp_list[i]->getSprite()->getPosition().y < highest_tile->getSprite()->getPosition().y)
    {
      highest_tile = temp_list[i];
    }
    else if (temp_list[i]->getSprite()->getPosition().y == highest_tile->getSprite()->getPosition().y)
    {
      if (Layout::isBetweenX(Layout::getCenter(player), *temp_list[i]->getSprite()))
      {
        highest_tile = temp_list[i];
      }
    }
  }

  return highest_tile;
}

void Level::init()
{
  initEnemies();
  initGround();
  initLevel();
}

void Level::initEnemies()
{
  for (int i=0; i<ENEMY_NUM; i++)
  {
    enemies[i] = nullptr;
  }
}

void Level::initGround()
{
  for (int i=0; i<GROUND_NUM; i++)
  {
    ground[i].getSprite()->setScale(5.0f, 5.0f);
    ground[i].getSprite()->setPosition(-100, GROUND_POSITION);
    ground[i].getSprite()->move(
      ground[i].getSprite()->getGlobalBounds().width * i, 0);
  }
  ground[2].existance = false;
  ground[5].existance = false;
  ground[7].existance = false;
}

void Level::initLevel()
{
  for (int i=0; i<BLOCK_NUM; i++)
  {
    block[i].getSprite()->setScale(1.0f, 1.0f);
    block[i].getSprite()->setPosition(0, 0);
  }
  block[0].getSprite()->setPosition(ground[1].getSprite()->getGlobalBounds().width + ground[1].getSprite()->getPosition().x - BLOCK_SIZE * 4, ground[0].getSprite()->getPosition().y - block[0].getSprite()->getGlobalBounds().height);

  for (int i=0; i<STAR_NUM; i++)
  {
    stars[i].getSprite()->setPosition(0, 0);
  }

  int set_block = 1;
  int set_stars = 0;
  int set_enemies = 0;

  /**

      0
     00
    000
   0000

   **/
  while (set_block < 10)
  {
    for (int i=1; i<4; i++)
    {
      for (int j=0; j<i+1; j++)
      {
        block[set_block].getSprite()->setPosition(block[0].getSprite()->getPosition());
        block[set_block].getSprite()->move(BLOCK_SIZE * i, -(j) * BLOCK_SIZE);
        set_block++;
      }
    }
  }

  stars[set_stars].getSprite()->setPosition(block[set_block - 1].getSprite()->getPosition());
  stars[set_stars].getSprite()->move(BLOCK_SIZE * 1.5, BLOCK_SIZE * -3);
  set_stars++;
  for (int i=1; i<4; i++)
  {
    stars[set_stars].getSprite()->setPosition(stars[set_stars - 1].getSprite()->getPosition());
    stars[set_stars].getSprite()->move(BLOCK_SIZE, 0);
    if (set_stars == 3)
    {
      stars[set_stars].getSprite()->move(0, BLOCK_SIZE);
    }
    else if (set_stars == 1)
    {
      stars[set_stars].getSprite()->move(0, -BLOCK_SIZE);
    }
    set_stars++;
  }

  /**

   0
   00
   000
   0000

   **/
  for (int i=10; i<20; i++)
  {
    block[i].getSprite()->setPosition(block[i - 10].getSprite()->getPosition());
    block[i].getSprite()->move(BLOCK_SIZE * (ground[0].getSprite()->getScale().x + 4), 0);
  }

  int x = 0;
  int y = 0;
  while (set_block < 20)
  {
    block[set_block].getSprite()->move(-y * BLOCK_SIZE, 0);
    set_block++;
    y++;
    if (y > x)
    {
      x++;
      y = 0;
    }
    if ((y == 0) && (x == 3))
    {
      enemies[set_enemies] = new Enemies(BLOCK_SIZE * 4);
      enemies[set_enemies]->getSprite()->setPosition(block[set_block].getSprite()->getPosition());
      enemies[set_enemies]->getSprite()->move(BLOCK_SIZE + enemies[set_enemies]->getSprite()->getGlobalBounds().width, BLOCK_SIZE - enemies[set_enemies]->getSprite()->getGlobalBounds().height);
      set_enemies++;
      for (int i=0; i<2; i++)
      {
        enemies[set_enemies] = new Enemies(BLOCK_SIZE * 4);
        enemies[set_enemies]->getSprite()->setPosition(enemies[set_enemies - 1]->getSprite()->getPosition());
        enemies[set_enemies]->getSprite()->move(BLOCK_SIZE, 0);
        set_enemies++;
      }
    }
  }

  /**

            0
   000

   **/
  for (int i=0; i<3; i++)
  {
    block[set_block].getSprite()->setPosition(block[16].getSprite()->getPosition());
    block[set_block].getSprite()->move(BLOCK_SIZE * (i + 1), -BLOCK_SIZE * 5);
    set_block++;
  }

  enemies[set_enemies] = new Enemies(3 * BLOCK_SIZE);
  enemies[set_enemies]->getSprite()->setPosition(block[set_block - 3].getSprite()->getPosition());
  enemies[set_enemies]->getSprite()->move(enemies[set_enemies]->getSprite()->getGlobalBounds().width, -enemies[set_enemies]->getSprite()->getGlobalBounds().height);
  set_enemies++;

  block[set_block].getSprite()->setPosition(block[set_block - 1].getSprite()->getPosition());
  block[set_block].getSprite()->move(BLOCK_SIZE * 5, BLOCK_SIZE * 2);
  set_block++;

  stars[set_stars].getSprite()->setPosition(block[set_block - 2].getSprite()->getPosition());
  stars[set_stars].getSprite()->move(BLOCK_SIZE * 2, -BLOCK_SIZE * 3);
  set_stars++;
  stars[set_stars].getSprite()->setPosition(stars[set_stars - 1].getSprite()->getPosition());
  stars[set_stars].getSprite()->move(BLOCK_SIZE,0);
  set_stars++;

  /** pillar **/
  block[set_block].getSprite()->setPosition(block[set_block - 1].getSprite()->getPosition());
  block[set_block].getSprite()->move(BLOCK_SIZE * 4, BLOCK_SIZE * 3);
  set_block++;

  for (int i=0; i<10; i++)
  {
    block[set_block].getSprite()->setPosition(block[set_block - 1].getSprite()->getPosition());
    block[set_block].getSprite()->move(0, -BLOCK_SIZE);
    if (i == 6)
    {
      block[set_block].getSprite()->move(0, -BLOCK_SIZE);
      stars[set_stars].getSprite()->setPosition(block[set_block -1].getSprite()->getPosition());
      stars[set_stars].getSprite()->move(0, -BLOCK_SIZE);
      set_stars++;
    }
    set_block++;
  }

  /**

       00

   0000000000

   **/
  for (int i=0; i<10; i++)
  {
    if (i > 0)
    {
      block[set_block].getSprite()->setPosition(block[set_block - 1].getSprite()->getPosition());
      block[set_block].getSprite()->move(BLOCK_SIZE, 0);
    }
    else
    {
      block[set_block].getSprite()->setPosition(block[set_block - 10].getSprite()->getPosition());
      block[set_block].getSprite()->move(BLOCK_SIZE * 3, -BLOCK_SIZE);

      enemies[set_enemies] = new Enemies(BLOCK_SIZE * 6);
      enemies[set_enemies]->getSprite()->setPosition(block[set_block].getSprite()->getPosition());
      enemies[set_enemies]->getSprite()->move(enemies[set_enemies]->getSprite()->getGlobalBounds().width, -enemies[set_enemies]->getSprite()->getGlobalBounds().height);
      set_enemies++;
      for (int j=0; j<4; j++)
      {
        enemies[set_enemies] = new Enemies(BLOCK_SIZE * 6);
        enemies[set_enemies]->getSprite()->setPosition(enemies[set_enemies - 1]->getSprite()->getPosition());
        enemies[set_enemies]->getSprite()->move(BLOCK_SIZE, 0);
        set_enemies++;
      }
    }
    if ((i == 2) || (i == 6))
    {
      stars[set_stars].getSprite()->setPosition(block[set_block].getSprite()->getPosition());
      stars[set_stars].getSprite()->move(0, BLOCK_SIZE);
      set_stars++;
    }
    set_block++;
  }

  for (int i=0; i<2; i++)
  {
    block[set_block].getSprite()->setPosition(block[set_block - 6].getSprite()->getPosition());
    block[set_block].getSprite()->move(0, -BLOCK_SIZE * 4);
    set_block++;
  }

  for (int i=0; i<4; i++)
  {
    stars[set_stars].getSprite()->setPosition(block[set_block - 1].getSprite()->getPosition());
    switch (i)
    {
      case 0:
        stars[set_stars].getSprite()->move(-BLOCK_SIZE * 3, 0);
        break;
      case 1:
        stars[set_stars].getSprite()->move(-BLOCK_SIZE * 2, -BLOCK_SIZE);
        break;
      case 2:
        stars[set_stars].getSprite()->move(BLOCK_SIZE, -BLOCK_SIZE);
        break;
      case 3:
        stars[set_stars].getSprite()->move(BLOCK_SIZE * 2, 0);
        break;
    }
    set_stars++;
  }

  /**

                 00
          00
   00

   **/
  for (int i=0; i<3; i++)
  {
    block[set_block].getSprite()->setPosition(block[set_block - 1].getSprite()->getPosition());
    if (i == 0)
    {
      block[set_block].getSprite()->move(BLOCK_SIZE * 5, BLOCK_SIZE * 1);

      enemies[set_enemies] = new Enemies(18 * BLOCK_SIZE);
      enemies[set_enemies]->getSprite()->setPosition(block[set_block].getSprite()->getPosition());
      enemies[set_enemies]->getSprite()->move(-BLOCK_SIZE * 3 + enemies[set_enemies]->getSprite()->getGlobalBounds().width, BLOCK_SIZE * 6 - enemies[set_enemies]->getSprite()->getGlobalBounds().height);
      set_enemies++;
      for (int j=0; j<2; j++)
      {
        enemies[set_enemies] = new Enemies(18 * BLOCK_SIZE);
        enemies[set_enemies]->getSprite()->setPosition(enemies[set_enemies - 1]->getSprite()->getPosition());
        enemies[set_enemies]->getSprite()->move(BLOCK_SIZE, 0);
        set_enemies++;
      }
    }
    block[set_block].getSprite()->move(BLOCK_SIZE * 3, -BLOCK_SIZE * 1);
    set_block++;
    block[set_block].getSprite()->setPosition(block[set_block - 1].getSprite()->getPosition());
    block[set_block].getSprite()->move(BLOCK_SIZE, 0);
    set_block++;

    stars[set_stars].getSprite()->setPosition(block[set_block - 1].getSprite()->getPosition());
    stars[set_stars].getSprite()->move(-BLOCK_SIZE * 0.5, -BLOCK_SIZE);
    set_stars++;
  }

  for (int i=0; i<4; i++)
  {
    for (int j=0; j<2; j++)
    {
      stars[set_stars].getSprite()->setPosition(block[set_block - 4].getSprite()->getPosition());
      stars[set_stars].getSprite()->move(BLOCK_SIZE * (i - 1), BLOCK_SIZE * (3 + j));
      set_stars++;
    }
  }

  for (int i=0; i<3; i++)
  {
    stars[set_stars].getSprite()->setPosition(block[set_block - 1].getSprite()->getPosition());
    if (i % 2 == 0)
    {
      stars[set_stars].getSprite()->move(BLOCK_SIZE, 0);
    }
    if (i > 0)
    {
      stars[set_stars].getSprite()->move(0, BLOCK_SIZE);
    }
    set_stars++;
  }

  /**

   0000

   **/
  block[set_block].getSprite()->setPosition(block[set_block - 1].getSprite()->getPosition());
  block[set_block].getSprite()->move(0, BLOCK_SIZE * 6);
  set_block++;
  enemies[set_enemies] = new Enemies(4 * BLOCK_SIZE);
  enemies[set_enemies]->getSprite()->setPosition(block[set_block - 1].getSprite()->getPosition());
  enemies[set_enemies]->getSprite()->move(enemies[set_enemies]->getSprite()->getGlobalBounds().width, -enemies[set_enemies]->getSprite()->getGlobalBounds().height);
  set_enemies++;
  for (int i=0; i<3; i++)
  {
    block[set_block].getSprite()->setPosition(block[set_block - 1].getSprite()->getPosition());
    block[set_block].getSprite()->move(BLOCK_SIZE, 0);
    set_block++;
  }

  // make the spare objects invisible
  for (int i=0; i<BLOCK_NUM; i++)
  {
    if (i < set_block)
    {
      block[i].existance = true;
    }
    else
    {
      block[i].existance = false;
    }
  }

  for (int i=0; i<STAR_NUM; i++)
  {
    if (i < set_stars)
    {
      stars[i].existance = true;
    }
    else
    {
      stars[i].existance = false;
    }
  }
}

void Level::deleteTempMemory()
{
  for (int i=0; i<ENEMY_NUM; i++)
  {
    enemies[i] = nullptr;
    delete enemies[i];
  }
}

void Level::update(float dt, Bullet* &bullet)
{
  for (int i=0; i<GROUND_NUM; i++)
  {
    ground[i].update(dt);
  }

  for (int i=0; i<BLOCK_NUM; i++)
  {
    block[i].update(dt);
  }

  for (int i=0; i<ENEMY_NUM; i++)
  {
    if (enemies[i] != nullptr)
    {
      enemies[i]->update(dt);
    }
  }

  updateBullet(dt, bullet);
}

void Level::updateBullet(float dt, Bullet* &bullet)
{
  for (int i=0; i<BLOCK_NUM; i++)
  {
    if ((block[i].existance) && (bullet != nullptr))
    {
      if (Layout::collisionDetection(*block[i].getSprite(), *bullet->getSprite()))
      {
        delete bullet;
        bullet = nullptr;
      }
    }
  }

  for (int i=0; i<ENEMY_NUM; i++)
  {
    if (enemies[i] != nullptr)
    {
      if (enemies[i]->existance)
      {
        if ((bullet != nullptr))
        {
          if (Layout::collisionDetection(*enemies[i]->getSprite(), *bullet->getSprite()))
          {
            enemies[i]->existance = false;
          }
        }
      }
    }
  }
}

void Level::render(sf::RenderWindow& window)
{
  for (int i=0; i<GROUND_NUM; i++)
  {
    if (ground[i].existance)
    {
      window.draw(*ground[i].getSprite());
    }
  }

  for (int i=0; i<BLOCK_NUM; i++)
  {
    if (block[i].existance)
    {
      window.draw(*block[i].getSprite());
    }
  }

  for (int i=0; i<STAR_NUM; i++)
  {
    if (stars[i].existance)
    {
      window.draw(*stars[i].getSprite());
    }
  }

  for (int i=0; i<ENEMY_NUM; i++)
  {
    if (enemies[i] != nullptr)
    {
      if (enemies[i]->existance)
      {
        window.draw(*enemies[i]->getSprite());
      }
    }
  }
}

#include "Enemy.hpp"
#include "Player.hpp"


Enemy::Enemy(float setPV, float setSpeed, sf::Vector2f setSize, sf::Color setColor): 
	Character{ setPV, setSpeed }
{
  enemy.setFillColor(sf::Color::Transparent);
  enemy.setSize(setSize);

  this->setSpriteTexture("res/Sprites/Enemy.png");
  this->setSpritePos(enemy.getPosition());
}

sf::RectangleShape Enemy::getShape(void)
{
	return enemy;
}

void Enemy::setPosition(sf::Vector2f pos) 
{ 
	enemy.setPosition(pos);
	this->setSpritePos(enemy.getPosition());
}

//Enemy stupide va vers player en ligne droite et lui tire dessus
int Enemy::enemyBehavior(Player* aim) 
{
  //float stopDistance = 200.f;

  sf::Vector2f direction = aim->getPosition() - enemy.getPosition();

  //Gun pistolet(2, 5, sf::Color::Black, 10);

  // Normalize direction
  float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);

  sf::Vector2f normDir = {direction.x / mag, direction.y / mag};
  sf::Vector2f velocity = {normDir.x * getSpeed(), normDir.y * getSpeed()};

  enemy.move(velocity);

  this->setSpritePos(enemy.getPosition());

  if (enemy.getGlobalBounds().intersects(aim->getShape().getGlobalBounds()))
  {
    aim->getDamage(1);
    return 1;
  }
  return 0;
  }
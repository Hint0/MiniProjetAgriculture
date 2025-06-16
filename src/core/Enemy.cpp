#include "Enemy.hpp"

Enemy::Enemy(float setPV, float setSpeed, sf::Vector2f setSize, sf::Color setColor): 
	Character{ setPV, setSpeed }
{
  enemy.setFillColor(setColor);
  enemy.setSize(setSize);
}

sf::RectangleShape Enemy::getShape(void)
{
	return enemy;
}

void Enemy::setPosition(sf::Vector2f pos) 
{ 
	enemy.setPosition(pos);
}

//Enemy stupide va vers player en ligne droite
void Enemy::enemyBehavior(sf::Vector2f aim)
{
  sf::Vector2f direction = aim - enemy.getPosition();

  // Normalize direction
  float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);
  if (mag != 0) 
  {
    sf::Vector2f normDir = {direction.x / mag, direction.y / mag};
    sf::Vector2f velocity = {normDir.x * getSpeed(), normDir.y * getSpeed()};

	enemy.move(velocity);
  }

  }
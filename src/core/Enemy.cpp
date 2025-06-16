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
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

//Enemy stupide va vers player en ligne droite et lui tire dessus
void Enemy::enemyBehavior(sf::Vector2f aim) 
{
  float stopDistance = 200.f;

  sf::Vector2f direction = aim - enemy.getPosition();

  //Gun pistolet(2, 5, sf::Color::Black, 10);

  // Normalize direction
  float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);
  if (mag > stopDistance) 
  {
    sf::Vector2f normDir = {direction.x / mag, direction.y / mag};
    sf::Vector2f velocity = {normDir.x * getSpeed(), normDir.y * getSpeed()};

	enemy.move(velocity);
  }
  else
  {
	//pistolet.fire(enemy.getPosition(), aim);
	  //Logique pour tirer
  }

  }
#include "SFML/Graphics.hpp"
#include "Bullet.hpp"

Bullet::Bullet(float radius, sf::Vector2f currVelocity, float max, sf::Color color) : 
	currentVelocity{currVelocity}, 
	maxSpeed{max} 
	{
	  bullet.setFillColor(color);
	  bullet.setRadius(radius);
	}

sf::CircleShape& Bullet::getBullet(void) 
{ 
	return bullet;
}

sf::Vector2f Bullet::getVelocity(void) 
{
	return currentVelocity;
}

void Bullet::setVelocity(sf::Vector2f newVelocity) 
{
	currentVelocity.x = newVelocity.x;
	currentVelocity.y = newVelocity.y;
}

float Bullet::getMaxSpeed(void) 
{
	return maxSpeed;
}

void Bullet::setPosition(sf::Vector2f pos) 
{ 
	bullet.setPosition(pos);
}
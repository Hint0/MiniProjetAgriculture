#include "Character.hpp"

Character::Character(float setSpeed, float setPV) :
	Speed{ setSpeed },
	PV {setPV}
	{}

float Character::getPV(void)
{ 
	return PV;
}

float Character::getSpeed(void)
{ 
	return Speed;
}

void Character::setSpriteTexture(const std::string& path) 
{
  texture.loadFromFile(path);
  std::cout << path << std::endl;
  sprite.setTexture(texture);
}

void Character::setSpritePos(sf::Vector2f setPos)
{
	sprite.setPosition(setPos);
  sprite.setScale({4, 4});
}

sf::Sprite Character::getSprite(void) 
{ 
	return sprite;
}

int Character::getDamage(float damage)
{ 
	PV = PV - damage;
	if (PV < 1)
	{
          Speed = 0;
          std::cout << "Mort" << std::endl;
          return 0;
	}
	return 1;
}

void Character::setPV(float setPV)
{
	PV = setPV;
}

void Character::setSpeed(float setSpeed)
{
	Speed = setSpeed;
}

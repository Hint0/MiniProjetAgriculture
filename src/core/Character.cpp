#include "Character.hpp"

Character::Character(float setSpeed, float setPV) : 
	Speed {setSpeed}, 
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

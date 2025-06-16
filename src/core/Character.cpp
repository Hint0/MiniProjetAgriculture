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
	if (PV < 0)
	{
          Speed = 0;
          return 0;
	}
	return 1;
}
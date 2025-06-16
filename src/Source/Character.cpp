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
#pragma once

#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <math.h>
#include <cstdlib>

#include "Bullet.hpp"

class Character {
 public:
  Character(float setSpeed, float setPV);
  float getPV(void);
  float getSpeed(void);
  int getDamage(float damage); //1 = Vivant. 0 = Mort


 private:
  float Speed;
  float PV;

};


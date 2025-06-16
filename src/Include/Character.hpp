#pragma once

#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <math.h>
#include <cstdlib>

class Character {
 public:
  Character(float setSpeed, float setPV);
  float getPV(void);
  float getSpeed(void);


 private:
  float Speed;
  float PV;

};


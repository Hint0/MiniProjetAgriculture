#pragma once

#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <math.h>
#include <cstdlib>

class Bullet {
 public:
  Bullet(float radius, sf::Vector2f currVelocity, float max, sf::Color color);
  sf::CircleShape& getBullet(void);
  sf::Vector2f getVelocity(void);
  void setVelocity(sf::Vector2f newVelocity);
  void setPosition(sf::Vector2f pos);
  float getMaxSpeed(void);

 private:
  sf::CircleShape bullet;
  sf::Vector2f currentVelocity;
  float maxSpeed;
};


#pragma once

#include "Character.hpp"

class Enemy : public Character {
 public:
  Enemy(float setPV, float setSpeed, sf::Vector2f setSize, sf::Color setColor);
  sf::RectangleShape getShape(void);
  void setPosition(sf::Vector2f pos);

 private:
  sf::RectangleShape enemy;
};



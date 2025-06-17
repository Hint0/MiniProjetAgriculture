#pragma once

#include "Character.hpp"

//Je te promet qu'elle existe, trust me
class Gun;

class Enemy : public Character {
 public:
  Enemy(float setPV, float setSpeed, sf::Vector2f setSize, sf::Color setColor);
  sf::RectangleShape getShape(void);
  void setPosition(sf::Vector2f pos);
  void enemyBehavior(sf::Vector2f aim);

 private:
  sf::RectangleShape enemy;
};



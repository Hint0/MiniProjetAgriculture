#pragma once

#include "SFML/Graphics.hpp"
#include "Character.hpp"
//#include "Weapon.hpp"

class Player : public Character {
 public:
  Player(float setPV, float setSpeed, float setRadius, sf::Color setColor);
  void playerMovement(void);
  sf::CircleShape getShape(void);
  sf::Vector2f getPosition(void);


 private:
  sf::CircleShape player;


};



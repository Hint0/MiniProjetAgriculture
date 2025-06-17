#pragma once

#include "SFML/Graphics.hpp"
#include "Character.hpp"


class Player : public Character {
 public:
  Player(float setPV, float setSpeed, float setRadius, sf::Color setColor);
  void playerMovement(void);
  sf::CircleShape getShape(void);
  sf::Vector2f getPosition(void);
  void setPosition(sf::Vector2f pos);
  void drawPV(sf::RenderWindow* window);



 private:
  sf::CircleShape player;


};



#pragma once

#include "Weapon.hpp"

class Gun : public Weapon {
 public:
  Gun(float fireRate, float bulletSpeed, sf::Color bulletColor,
      float bulletRadius);

  std::vector<Bullet> fire(const sf::Vector2f& position,
                           const sf::Vector2f& cible) override;


 private:

  sf::Clock cooldownCounter;

};
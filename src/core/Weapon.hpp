#pragma once

#include <ctime>
#include "Bullet.hpp"

class Enemy;

class Player;

class Weapon {
 public:
  Weapon(float fireRate, float bulletSpeed, sf::Color bulletColor, float bulletRadius);

  void updateBullet(sf::RenderWindow* window, std::vector<std::unique_ptr<Enemy>> &enemies, Player player);

  void updateBullets(Bullet bullet);

  std::vector<Bullet> getBullets(void);

  virtual ~Weapon() = default;

  virtual std::vector<Bullet> fire(const sf::Vector2f& position,
                                   const sf::Vector2f& cible) = 0;

  float getFireRate(void);

  void ClearBullets();

 protected:
  std::vector<Bullet> bullets;
  float fireRate;
  float bulletSpeed;
  sf::Color bulletColor;
  float bulletRadius;
};
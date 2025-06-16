#include "Gun.hpp"

#include <cmath>

Gun::Gun(float fireRate, float bulletSpeed, sf::Color bulletColor,float bulletRadius):
    Weapon{fireRate, bulletSpeed, bulletColor, bulletRadius}
{}

std::vector<Bullet> Gun::fire(const sf::Vector2f& position,const sf::Vector2f& cible) 
{

  sf::Vector2f direction = cible - position;

  // Normalize direction
  float mag = std::sqrt(direction.x * direction.x + direction.y * direction.y);
  if (mag == 0) return getBullets();

  sf::Vector2f normDir = {direction.x / mag, direction.y / mag};
  sf::Vector2f velocity = {normDir.x * bulletSpeed, normDir.y * bulletSpeed};

  if (cooldownCounter.getElapsedTime().asSeconds() > fireRate)
  {
      Bullet b(bulletRadius, velocity, bulletSpeed, bulletColor);
      b.setPosition(position);
      //Fait un pushback dans bullets
      updateBullets(b);
      //Relance l'horloge
      cooldownCounter.restart();
      return getBullets();
  }
  return getBullets();
}



#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/System.hpp"
#include <math.h>
#include <cstdlib>

#include "Bullet.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Gun.hpp"



int main(void)
{ 
    srand(std::time(nullptr));
	
  sf::RenderWindow window(sf::VideoMode({800, 600}), "Mini Shooter");
  window.setFramerateLimit(30);

  //Player
  float playerRadius = 25;
  sf::Color playerColor = sf::Color::Red;

  float setPV = 10;
  float setSpeed = 10;

  Player playerClass(setPV, setSpeed, playerRadius, playerColor);
  sf::CircleShape player = playerClass.getShape();

  //Bullets
  float bulletRadius = 5.f;
  sf::Vector2f bulletSpeed = {0.f, 0.f};
  float bulletMaxSpeed = 10.f;
  sf::Color bulletColor = sf::Color::Yellow;
  Bullet bullet1(bulletRadius, bulletSpeed, bulletMaxSpeed, bulletColor);


  //Gun
  float fireRate = 0.5f;

  //Gun a la liste des bullets qu'il tire !!!!
  Gun pistolet(fireRate, bulletMaxSpeed, bulletColor, bulletRadius);




  //Enemy

  sf::Vector2f setEnemySize = {50.f, 50.f};
  sf::Color setEnemyColor = sf::Color::Magenta;

  Enemy enemy(setPV, setSpeed, setEnemySize, setEnemyColor);

  std::vector<Enemy> enemies;
  int spawnCounter = 10;

  //Vectors
  sf::Vector2f playerCenter;
  sf::Vector2f posMouse;

  while (window.isOpen())
  {
    
    while (const std::optional event = window.pollEvent())
    {
      if (event->is<sf::Event::Closed>()) 
          window.close();
    }

    //Update
    // Enemies
    
    if (spawnCounter < 20)
    {
      spawnCounter++;
    }
    else if (spawnCounter >= 20 && enemies.size()<50)
    {
      enemy.setPosition(sf::Vector2f(rand()%window.getSize().x, rand()%window.getSize().y));
      enemies.push_back(enemy);
    }
    //Vectors
    playerCenter = playerClass.getPosition();
    posMouse = sf::Vector2f(sf::Mouse::getPosition(window));

    //Player
    //fé bouger le player
    playerClass.playerMovement();


    //Shooting
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
      pistolet.fire(playerCenter, posMouse);

    }
    //Fait partie de l'arme, ici on update tout
    sf::RenderWindow* window_ptr = &window;
    std::vector<Enemy>* enemies_ptr = &enemies;
    pistolet.updateBullet(window_ptr, enemies_ptr);


    //Draw
    window.clear();

    window.draw(playerClass.getShape());

    for (size_t i = 0; i < enemies.size(); i++) 
    {
      window.draw(enemies[i].getShape());
    }
    std::vector<Bullet> bulletsUsed = pistolet.getBullets();
    for (size_t i = 0; i < bulletsUsed.size(); i++)
    {
      window.draw(bulletsUsed[i].getBullet());
    }


    window.display();
  }
  std::printf("\n fin de la simulation\n");
  return (0);
}
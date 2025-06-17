#include <gtest/gtest.h>

#include <string>

#include "Player.hpp"
#include "Enemy.hpp"
#include "Gun.hpp"
#include "Bullet.hpp"

//Test si les PV sont bien modifiés
TEST(PlayerTest, SetPVWorks) 
{
  Player player(10, 10, 10, sf::Color::Magenta);
  player.setPV(4);
  EXPECT_EQ(4, player.getPV());
  player.getDamage(2);
  EXPECT_EQ(2, player.getPV());
}

//Test si les balles sont bien compté et si le clear fonctionne
TEST(EmptyBullets, bulletsClearWorks) 
{ 
  Gun pistolet(2, 2, sf::Color::Red, 2);
  Bullet bullet(2, {0, 0}, 2, sf::Color::Red);
  pistolet.updateBullets(bullet);
  pistolet.updateBullets(bullet);
  pistolet.updateBullets(bullet);
  EXPECT_EQ(3, pistolet.getBullets().size());
  pistolet.ClearBullets();
  EXPECT_EQ(0, pistolet.getBullets().size());
}

//Erreur logique par rapport au load des sprites
//Test si le enemy peut bouger vers le player et lui infliger 1 dégât
//Test maybe error prone dû au fait que sur une machine peu puissante
//Le framerate casse le deplacement de l'enemy
TEST(EnemyBehavior, enemyBehaviorWorks)
{
  Player player(10, 10, 10, sf::Color::Magenta);
  player.setPosition({10, 0});
  Enemy enemy(10, 10, {10,10}, sf::Color::Magenta);
  enemy.setPosition({0, 0});
  int i = enemy.enemyBehavior(&player);
  //Il se dirige vers le player
  EXPECT_LT(0, enemy.getShape().getPosition().x);
  //Il signale qu'il a infligé des dégats au joueur
  EXPECT_EQ(i, 1);
  //Le player a reçu 1 dégât
  EXPECT_EQ(9, player.getPV());
}
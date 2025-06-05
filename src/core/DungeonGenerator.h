#pragma once
#include "Room.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>

class DungeonGenerator
{
 private:
  sf::Vector2f scoreRange;
  sf::Vector2f longestPathRange;
  std::vector<std::unique_ptr<Room>> rooms;
 public:
  DungeonGenerator(sf::Vector2f score, sf::Vector2f longestPath);
  void GenerateLayout();
  bool GenerateNextRoom(Room* previousRoom, sf::Vector2i direction, float chanceModifier);
  float RandomPercent();
  void Draw(sf::RenderWindow* window);
};
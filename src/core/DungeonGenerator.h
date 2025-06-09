#pragma once
#include "Room.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <memory>

class DungeonGenerator
{
 private:
  int maxRooms;
  int longestPath;
  std::vector<std::unique_ptr<Room>> rooms;
  bool bExitRoomGenerated;
  unsigned int seed;

  int exitRoomIndex;

 public:
  DungeonGenerator(unsigned int seed, int maxRooms, int longestPath);
  void GenerateLayout();
  bool GenerateNextRoom(Room* previousRoom, sf::Vector2i direction, float baseChance);
  float RandomPercent();
  void Draw(sf::RenderWindow* window);
};
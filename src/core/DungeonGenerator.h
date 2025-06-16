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
  unsigned int seed;
  int exitRoomIndex;
  Room* currentRoom;
  sf::Vector2f layoutSize;

 public:
  DungeonGenerator(unsigned int seed, int maxRooms, int longestPath);
  void GenerateLayout();
  bool GenerateNextRoom(Room* previousRoom, sf::Vector2i direction, float baseChance);
  float RandomPercent();
  void DrawLayout(sf::RenderWindow* window);
  void DrawMap(sf::RenderWindow* window, sf::Vector2f offset);
  bool TryMoveToAdjacentRoom(sf::Vector2i position);
};
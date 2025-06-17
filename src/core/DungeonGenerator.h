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
  int exitRoomIndex;
  sf::Vector2f layoutSize;
  bool hasWin;

 public:
  DungeonGenerator(int maxRooms, int longestPath);
  void GenerateLayout();
  bool GenerateNextRoom(Room* previousRoom, sf::Vector2i direction, float baseChance);
  void DrawLayout(sf::RenderWindow* window);
  void DrawMap(sf::RenderWindow* window, sf::Vector2f offset);
  bool TryMoveToAdjacentRoom(sf::Vector2i position);
  void DrawWin(sf::RenderWindow* window) const;
  void DrawDefeat(sf::RenderWindow* window) const;
  void Reset();

  Room* currentRoom;
};
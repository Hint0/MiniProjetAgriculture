#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <SMFLOrthogonalLayer.h>
#include <Enemy.hpp>


enum RoomShape {Basic, Big, Corridor, Small };

class Room 
{
 private:
  RoomShape shape;

  tmx::Map map;
  MapLayer* LayerTerrain;
  MapLayer* LayerCrops;

 public:
  Room(int x, int y, int distFromStart);
  void DrawLayout(sf::RenderWindow* window, int index, sf::Color color, sf::Vector2f maxSize) const;
  void DrawRoom(sf::RenderWindow* window, int index, sf::Vector2f offset);
  void AddAdjacentRoom(int index, sf::Vector2i position);
  void InitializeMap();
  std::string GetMapFileNameByDoors();
  void SpawnEnemies();
  void DrawEnemies(sf::RenderWindow* window);
  void SetEnemiesTarget(sf::Vector2f target);
  void CheckRemainingEnemies();

  static std::vector<sf::Vector2i> GetDoorPositionsByShape(RoomShape shape);
  static sf::Vector2i GetRoomSizeByShape(RoomShape shape);

  int x, y;
  int distFromStart;
  std::vector<std::pair<int, sf::Vector2i>> adjacentRooms;
  std::vector<sf::Vector2i> avalaibleDoors;
  bool isCleared;
  std::vector<Enemy>* enemies;

  static const int MIN_ENEMIES = 6;
  static const int MAX_ENEMIES = 12;
};
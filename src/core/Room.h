#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>
#include <SMFLOrthogonalLayer.h>

enum RoomShape {Basic, Big, Corridor, Small };

class Room 
{
 private:
  RoomShape shape;
 public:
  Room(int x, int y, int distFromStart);
  void DrawLayout(sf::RenderWindow* window, int index, sf::Color color) const;
  void DrawRoom(sf::RenderWindow* window, int index, sf::Vector2f offset);
  void AddAdjacentRoom(int index, sf::Vector2i position);
  void InitializeMap();
  std::string GetMapFileNameByDoors();

  static std::vector<sf::Vector2i> GetDoorPositionsByShape(RoomShape shape);
  static sf::Vector2i GetRoomSizeByShape(RoomShape shape);

  int x, y;
  int distFromStart;
  std::vector<int> adjacentRoomsIndexes;
  std::vector<sf::Vector2i> avalaibleDoors;
  static sf::Vector2i Size;

  tmx::Map map;
  MapLayer* LayerTerrain;
  MapLayer* LayerCrops;
};
#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include <tmxlite/Map.hpp>

enum RoomShape {Basic, Big, Corridor, small };

class Room 
{
 private:
  std::vector<int> adjacentRoomsIndexes;
  RoomShape shape;
 public:
  Room(int x, int y, int distFromStart);
  void DrawLayout(sf::RenderWindow* window, int index, sf::Color color) const;
  void DrawRoom(sf::RenderWindow* window, int index, sf::Vector2f offset) const;
  std::vector<sf::Vector2i> GetDoorPositions();
  void AddAdjacentRoom(int index, sf::Vector2i position);

  static std::vector<sf::Vector2i> GetDoorPositionsByShape(RoomShape shape);

  int x, y;
  int distFromStart;
  std::vector<sf::Vector2i> avalaibleDoors;
  static sf::Vector2i Size;
  tmx::Map map;
};
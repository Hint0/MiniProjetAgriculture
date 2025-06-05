#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

enum RoomShape {Basic, Big, Corridor, small };

class Room 
{
 private:
  std::vector<Room*> adjacentRooms;
  RoomShape shape;
 public:
  Room(int x, int y, int distFromStart);
  void Draw(sf::RenderWindow* window) const;
  std::vector<sf::Vector2i> GetDoorPositions();
  void AddAdjacentRoom(Room* room, sf::Vector2i position);

  int x, y;
  int distFromStart;
  std::vector<sf::Vector2i> avalaibleDoors;
  static sf::Vector2i Size;
};
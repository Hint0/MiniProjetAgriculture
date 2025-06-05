#include "Room.h"

sf::Vector2i Room::Size = sf::Vector2i(40, 30);

Room::Room(int x, int y, int distFromStart)
    : x{x},
      y{y},
      distFromStart{distFromStart},
      shape{Basic},
      avalaibleDoors{{1, 0}, {0, -1}, {-1, 0}, {0, 1}} {}

void Room::Draw(sf::RenderWindow* window) const {
  sf::RectangleShape shape(
      sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
  shape.setFillColor(sf::Color::Red);
  float xPos = static_cast<float>(x + window->getSize().x / 2.);
  float yPos = static_cast<float>(window->getSize().y / 2. - y);

  shape.setPosition({xPos, yPos});
  shape.setSize(sf::Vector2f(Room::Size.x, Room::Size.y));
  shape.setOutlineThickness(2);
  shape.setOutlineColor(sf::Color::Black);
  window->draw(shape);

  sf::Font font("res/arial.ttf");
  sf::Text text(font, std::to_string(distFromStart));
  text.setFillColor(sf::Color::Black);
  text.setPosition({xPos, yPos});
  window->draw(text);
}

std::vector<sf::Vector2i> Room::GetDoorPositions() {
  switch (shape) {
    case Basic:
      return std::vector<sf::Vector2i>{{1, 0}, {0, -1}, {-1, 0}, {0, 1}};
    case Big:
    case Corridor:
    case small:
    default:
      return std::vector<sf::Vector2i>{{0, 0}};
  }
}

void Room::AddAdjacentRoom(Room* room, sf::Vector2i position)  
{  
   adjacentRooms.push_back(room);  

   std::erase_if(avalaibleDoors, [position](const auto& d) {  
       return d.x == position.x && d.y == position.y;  
   });  
}
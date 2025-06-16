#include "Room.h"
#include <DungeonGenerator.h>
#include <RandomHelper.h>

Room::Room(int x, int y, int distFromStart)
	: x{ x },
	y{ y },
	distFromStart{ distFromStart },
	shape{ Basic },
	avalaibleDoors{ {1, 0}, {0, -1}, {-1, 0}, {0, 1} },
	LayerTerrain{ nullptr },
	LayerCrops{ nullptr },
	isCleared{ false },
	enemies{ new std::vector<Enemy>() }
{
}

void Room::DrawLayout(sf::RenderWindow* window, int index, sf::Color color, sf::Vector2f offset) const
{
	sf::RectangleShape shape(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)));
	shape.setFillColor(color);
	float xPos = static_cast<float>(x / 36. - offset.x / 36. + 5.);
	float yPos = static_cast<float>(-y / 32. + offset.y / 32. + 5.);

	shape.setPosition({ xPos, yPos });
	shape.setSize(sf::Vector2f(35, 25));
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color(0, 0, 0, 100));
	window->draw(shape);

	/*sf::Font font;
	font.loadFromFile("res/arial.ttf");
	sf::Text text(std::to_string(index), font);
	text.setFillColor(sf::Color::Black);
	text.setPosition({ xPos, yPos });
	text.setCharacterSize(26);
	window->draw(text);*/
}

void Room::DrawRoom(sf::RenderWindow* window, int index, sf::Vector2f offset)
{
	offset.x += x;
	offset.y -= y;

	LayerTerrain->setOffset(offset);
	window->draw(*LayerTerrain);

	LayerCrops->setOffset(offset);
	window->draw(*LayerCrops);

	DrawEnemies(window);
}

void Room::AddAdjacentRoom(int index, sf::Vector2i position)
{
	for (const auto& room : adjacentRooms)
	{
		if (room.first == index)
			return;
	}

	adjacentRooms.push_back({ index, position });

	std::erase_if(avalaibleDoors, [position](const auto& d)
	{
		return d.x == position.x && d.y == position.y;
	});
}

void Room::InitializeMap()
{
	map.load(GetMapFileNameByDoors());

	LayerTerrain = new MapLayer(map, 0);
	LayerCrops = new MapLayer(map, 1);
}

std::string Room::GetMapFileNameByDoors()
{
	std::string fileName = "res/maps/Default_";

	bool right = false;
	bool left = false;
	bool up = false;
	bool down = false;

	for (const auto& door : avalaibleDoors)
	{
		if (door.x == 1 && door.y == 0)
			right = true;
		else if (door.x == 0 && door.y == 1)
			up = true;
		else if (door.x == -1 && door.y == 0)
			left = true;
		else if (door.x == 0 && door.y == -1)
			down = true;
	}

	if (!right) fileName += "Right";
	if (!up) fileName += "Up";
	if (!left) fileName += "Left";
	if (!down) fileName += "Down";

	fileName += ".tmx";
	return fileName;
}

void Room::SpawnEnemies()
{
	// Don't spawn enemies if the room is already cleared
	if (isCleared) return;

	int number = RandomHelper::GetRandomInt(MIN_ENEMIES, MAX_ENEMIES);

	for (int i = 0; i < number; ++i)
	{
		Enemy enemy(10.f, 10.f, sf::Vector2f(50.f, 50.f), sf::Color::Magenta);
		enemy.setPosition({ RandomHelper::GetRandomFloat(0, 1440), RandomHelper::GetRandomFloat(0, 960) });
		enemies->push_back(enemy);
	}
}

void Room::DrawEnemies(sf::RenderWindow* window)
{
	if (enemies == nullptr || enemies->empty())
	{
		return; // No enemies to draw
	}

	for (auto& enemy : *enemies)
	{
		if (enemy.getPV() <= 0) continue; // Skip dead enemies

		window->draw(enemy.getShape());
	}
}

void Room::SetEnemiesTarget(sf::Vector2f target)
{
	for (auto& enemy : *enemies)
	{
		enemy.enemyBehavior(target);
	}
}

void Room::CheckRemainingEnemies()
{
	if (enemies == nullptr || enemies->empty())
	{
		isCleared = true;
	}
}

std::vector<sf::Vector2i> Room::GetDoorPositionsByShape(RoomShape shape)
{
	switch (shape)
	{
	case Basic:
		return std::vector<sf::Vector2i>{{1, 0}, { 0, -1 }, { -1, 0 }, { 0, 1 }};
	case Big:
	case Corridor:
	case Small:
	default:
		return std::vector<sf::Vector2i>{{0, 0}};
	}
}

sf::Vector2i Room::GetRoomSizeByShape(RoomShape shape)
{
	switch (shape)
	{
	case Basic:
		return  sf::Vector2i{ 1440, 960 };
	case Big:
	case Corridor:
	case Small:
	default:
		return sf::Vector2i{ 0, 0 };
	}
}

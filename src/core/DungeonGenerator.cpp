#include "DungeonGenerator.h"

#include <iostream>
#include <random>
#include <RandomHelper.h>

using namespace std;
using namespace sf;

DungeonGenerator::DungeonGenerator(int maxRooms, int longestPath)
	: maxRooms{ maxRooms },
	longestPath{ longestPath },
	exitRoomIndex{ -1 },
	currentRoom{ nullptr },
	hasWin{ false }
{
}

void DungeonGenerator::GenerateLayout()
{
	// Generate first room
	rooms.push_back(make_unique<Room>(0, 0, 0));

	//Initialize the current room to the first one
	currentRoom = rooms.back().get();

	//Set the first room to cleared by default, so that the player can move to adjacent rooms
	currentRoom->isCleared = true;

	float chanceToGenerate = 0.25;

	for (const auto& pos : currentRoom->avalaibleDoors)
	{
		if (GenerateNextRoom(currentRoom, pos, chanceToGenerate))
		{
			chanceToGenerate = 0.25;
		}
		else
		{
			chanceToGenerate += 0.25;
		}
	}

	for (size_t i = 0; i < rooms.size(); ++i)
	{
		rooms[i]->InitializeMap();
	}

	cout << "END OF GENERATION / " << RandomHelper::SEED << " / Total rooms : " << rooms.size() << endl;
}

bool DungeonGenerator::GenerateNextRoom(Room* previousRoom,
	Vector2i direction, float baseChance)
{
	//First check the distance from the starting room
	//The exit room of the dungeon should be the farest from the start
	if (exitRoomIndex == -1)
	{
		if (previousRoom->distFromStart + 1 > longestPath)
		{
			exitRoomIndex = rooms.size() - 1;
			previousRoom->isExit = true;
			return false;
		}
	}
	else if (previousRoom->distFromStart + 1 > longestPath - 1 || rooms.size() >= maxRooms)
	{
		return false;
	}

	// Make sure the door of the previous room is actually avalaible
	// as it may not be up to date, if not don't try to create the room
	bool avalaible = false;
	for (const auto& door : previousRoom->avalaibleDoors)
	{
		if (door == direction)
		{
			avalaible = true;
			break;
		}
	}

	if (!avalaible) return false;

	Vector2i size = Room::GetRoomSizeByShape(RoomShape::Basic);

	//Compute wanted room's coordinate
	int x = previousRoom->x + (direction.x * size.x);
	int y = previousRoom->y + (direction.y * size.y);

	//Get the wanted room's adjacent rooms
	vector<pair<int, Vector2i>> adjacents;

	for (int i = 0; i < rooms.size(); ++i)
	{
		Room* room = rooms[i].get();
		for (const auto& pos : Room::GetDoorPositionsByShape(RoomShape::Basic))
		{
			if (room->x == x + (pos.x * size.x) &&
				room->y == y + (pos.y * size.y) &&
				adjacents.size() < 4)
			{
				// Exit room shouldn't have more than one adjacent room
				// So if it is found as return do not create the room
				if (exitRoomIndex == i) return false;

				int index = i;
				adjacents.push_back({ index, pos });
			}
		}
	}

	float chanceToGenerate = baseChance;
	float rd = RandomHelper::GetRandomFloat(0.f, 1.f);

	if (exitRoomIndex > -1)
	{
		// If the exit room has been created, we modify the chance of generation to
		// prevent having a dungeon layout which is too much compact

		// Modify chance based on number of adjacents room
		chanceToGenerate += (adjacents.size() > 0) ? adjacents.size() * -0.2 : 0.2;

		// Modify chance based on total number of room
		chanceToGenerate += 1. - (static_cast<double>(rooms.size()) / maxRooms);
	}
	else
	{
		// If the exit hasn't been created, we want to have 100% chance to generate
		// a room on the last door possible
		chanceToGenerate += 1. / (4 - adjacents.size());
	}

	if (rd > chanceToGenerate) return false;

	// Update layout size, used to draw mini map correctly
	if (layoutSize.x > x) layoutSize.x = x;
	if (layoutSize.y < y) layoutSize.y = y;

	unique_ptr<Room> r = make_unique<Room>(x, y, previousRoom->distFromStart + 1);

	int lowestDistance = r->distFromStart - 1;

	for (int i = 0; i < adjacents.size(); i++)
	{
		//Rectify the distance from the start by finding the lowest distance in the adjacent rooms
		if (lowestDistance > rooms[adjacents[i].first]->distFromStart)
			lowestDistance = rooms[adjacents[i].first]->distFromStart;

		// Add the adjacents rooms to the new room & notify these room that they have a new adjacent room
		r->AddAdjacentRoom(adjacents[i].first, adjacents[i].second);
		rooms[adjacents[i].first]->AddAdjacentRoom(rooms.size(), -adjacents[i].second);
	}

	r->distFromStart = lowestDistance + 1;

	Room* room = r.get();

	rooms.push_back(move(r));

	baseChance = exitRoomIndex == -1 ? 0.25 : baseChance;

	for (const auto& pos : room->avalaibleDoors)
	{
		if (GenerateNextRoom(room, pos, baseChance))
		{
			baseChance = 0.34;
		}
		else if (exitRoomIndex == -1)
		{
			baseChance += 0.33;
		}
	}

	return true;
}

void DungeonGenerator::DrawLayout(sf::RenderWindow* window)
{
	sf::Color roomColor(200, 200, 200, 100);
	sf::Color currentRoomColor(50, 50, 50, 100);

	for (int i = 0; i < rooms.size(); ++i)
	{
		if (currentRoom == rooms[i].get())
		{
			rooms[i]->DrawLayout(window, i, currentRoomColor, layoutSize);
		}
		else
		{
			rooms[i]->DrawLayout(window, i, roomColor, layoutSize);
		}
	}
}

void DungeonGenerator::DrawMap(sf::RenderWindow* window, sf::Vector2f offset)
{
	int counter = 0;
	for (const auto& room : rooms)
	{
		room->DrawRoom(window, counter, offset);
		counter++;
	}
}

bool DungeonGenerator::TryMoveToAdjacentRoom(sf::Vector2i position)
{
	// All ennemies in the current room must be cleared before moving to an adjacent room
	if (!currentRoom->isCleared) return false;

	// If  the current room is the exit, locked the player inside (so he can't go back)
	// and toggle win display message
	if (currentRoom->isExit)
	{
		hasWin = true;
		return false;
	}

	// Check if there is an adjacent room at this position
	for (const auto& adjacent : currentRoom->adjacentRooms)
	{
		if (adjacent.second == position)
		{
			currentRoom = rooms[adjacent.first].get();
			return true;
		}
	}

	return false;
}

void DungeonGenerator::DrawWin(sf::RenderWindow* window) const
{
	if (!hasWin) return;

	sf::Font font;
	font.loadFromFile("res/arial.ttf");
	sf::Text text("YOU ARE \n   FREE!", font);
	text.setFillColor(sf::Color(50, 200, 50, 230));
	text.setPosition({ 60, 100 });
	text.setCharacterSize(300);
	window->draw(text);
}

void DungeonGenerator::DrawDefeat(sf::RenderWindow* window) const {
        sf::Font font;
        font.loadFromFile("res/arial.ttf");
        sf::Text text("YOU ARE \n   DEAD!", font);
        text.setFillColor(sf::Color::Red);
        text.setPosition({60, 100});
        text.setCharacterSize(300);
        window->draw(text);
}

void DungeonGenerator::Reset()
{
	rooms.clear();
	exitRoomIndex = -1;
	hasWin = false;
	currentRoom = nullptr;
	layoutSize = sf::Vector2f(0.f, 0.f);
}

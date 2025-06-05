#include "DungeonGenerator.h"

#include <iostream>
#include <random>

using namespace std;

DungeonGenerator::DungeonGenerator(sf::Vector2f score, sf::Vector2f longestPath)
	: scoreRange{ score }, longestPathRange{ longestPath }
{
}

void DungeonGenerator::GenerateLayout()
{
	// Generate first room
	rooms.push_back(make_unique<Room>(0, 0, 0));

	Room* room = rooms.back().get();

	float chanceToGenerate = 0.25;

	for (const auto& pos : room->GetDoorPositions())
	{
		if (GenerateNextRoom(room, pos, chanceToGenerate))
		{
			chanceToGenerate = 0.25;
		}
		else
		{
			chanceToGenerate += 0.25;
		}
	}
}

bool DungeonGenerator::GenerateNextRoom(Room* previousRoom,
	sf::Vector2i direction, float chanceModifier)
{
	if (previousRoom->distFromStart + 1 > longestPathRange.y) return false;

	cout << "---------- Generating new room ----------" << endl;

	int x = previousRoom->x + (direction.x * Room::Size.x);
	int y = previousRoom->y + (direction.y * Room::Size.y);

	cout << "Position : (" << x << "," << y << ")" << endl;

	rooms.push_back(make_unique<Room>(x, y, previousRoom->distFromStart + 1));

	Room* currentRoom = rooms.back().get();

	int lowestDistance = currentRoom->distFromStart - 1;

	for (const auto& room : rooms)
	{
		for (const auto& pos : currentRoom->GetDoorPositions())
		{
			if (room->x == currentRoom->x + (pos.x * Room::Size.x) &&
				room->y == currentRoom->y + (pos.y * Room::Size.y))
			{
				currentRoom->AddAdjacentRoom(room.get(), pos);
				cout << "(" << room.get()->x << "," << room.get()->y << ") pos("
					<< pos.x << "," << pos.y << ")" << endl;
				room->AddAdjacentRoom(currentRoom, pos * -1);

				if (room.get()->distFromStart < lowestDistance)
				{
					// Propager le changement de distance aux autres adjacent room
					// Qui ensuite le propagront à leurs adjacent rooms
					lowestDistance = room.get()->distFromStart;
				}
			}
		}
	}

	currentRoom->distFromStart = lowestDistance + 1;

	cout << "Distance from start : " << currentRoom->distFromStart << endl;

	cout << "Avalaible doors : " << currentRoom->avalaibleDoors.size() << endl;

	float changeToGenerate = 0.34;

	cout << "-----------------------------------------" << endl << endl;

	for (const auto& pos : currentRoom->avalaibleDoors)
	{
		if (GenerateNextRoom(currentRoom, pos, changeToGenerate))
		{
			changeToGenerate = 0.34;
		}
		else
		{
			changeToGenerate += 0.33;
		}
	}

	return true;
}

float DungeonGenerator::RandomPercent()
{
	static random_device rd;
	static default_random_engine engine(rd());
	uniform_int_distribution distribution(0, 100);
	return distribution(engine) / 100.0;
}

void DungeonGenerator::Draw(sf::RenderWindow* window)
{
	for (const auto& room : rooms)
	{
		room->Draw(window);
	}
}

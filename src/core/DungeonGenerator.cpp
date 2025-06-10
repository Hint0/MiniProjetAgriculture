#include "DungeonGenerator.h"

#include <iostream>
#include <random>

using namespace std;

DungeonGenerator::DungeonGenerator(unsigned int seed, int maxRooms, int longestPath)
	: seed{ seed }, maxRooms{ maxRooms }, longestPath{ longestPath }, bExitRoomGenerated{ false }, exitRoomIndex{ -1 }
{
}

void DungeonGenerator::GenerateLayout()
{
	// Generate first room
	rooms.push_back(make_unique<Room>(0, 0, 0));

	Room* room = rooms.back().get();

	float chanceToGenerate = 0.25;

	for (const auto& pos : room->avalaibleDoors)
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

	cout << "END OF GENERATION / " << seed << " / Total rooms : " << rooms.size() << endl;
}

bool DungeonGenerator::GenerateNextRoom(Room* previousRoom,
	sf::Vector2i direction, float baseChance)
{
	//First check the distance from the starting room
	//The exit room of the dungeon should be the farest from the start
	if (!bExitRoomGenerated)
	{
		if (previousRoom->distFromStart + 1 > longestPath)
		{
			cout << "Exit Room ! " << previousRoom->distFromStart << endl;
			exitRoomIndex = rooms.size() - 1;
			bExitRoomGenerated = true;
			return false;
		}
	}
	else
	{
		if (previousRoom->distFromStart + 1 > longestPath - 1 || rooms.size() >= maxRooms)
			return false;
	}

	// retrun false if rooms.size() >= scoreRange.y

	//Compute wanted room's coordinate
	int x = previousRoom->x + (direction.x * Room::Size.x);
	int y = previousRoom->y + (direction.y * Room::Size.y);

	//Get the wanted room's adjacent rooms
	vector<pair<int, sf::Vector2i>> adjacents;

	for (int i = 0; i < rooms.size(); ++i)
	{
		Room* room = rooms[i].get();
		for (const auto& pos : Room::GetDoorPositionsByShape(RoomShape::Basic))
		{
			if (room->x == x + (pos.x * Room::Size.x) &&
				room->y == y + (pos.y * Room::Size.y) &&
				adjacents.size() < 4)
			{
				int index = i;
				adjacents.push_back({ index, pos });
			}
		}
	}

	float chanceToGenerate = baseChance;
	float rd = RandomPercent();

	cout << endl << "adjacent rooms pos: " << endl;
	for (const auto& ad : adjacents)
	{
		cout << ad.second.x << ad.second.y << endl;
	}
	cout << "--------------------" << endl;

	if (bExitRoomGenerated)
	{
		// Modify chance based on number of adjacents room
		chanceToGenerate += (adjacents.size() > 0) ? adjacents.size() * -0.2 : 0.2;

		// Modify chance based on total number of room
		chanceToGenerate += 1. - (static_cast<double>(rooms.size()) / maxRooms);
	}
	else
	{
		cout << chanceToGenerate << " + " << 1. / (4 - adjacents.size()) << " | " << adjacents.size() << " ";
		chanceToGenerate += 1. / (4 - adjacents.size());
	}

	

	cout << "Chance : " << chanceToGenerate << " < " << rd << " For pos : " << direction.x << ":" << direction.y << endl;
	if (rd > chanceToGenerate) return false;

	cout << "---------- Generating new room ----------" << endl;

	cout << "Position : (" << x << "," << y << ")" << endl;

	unique_ptr<Room> r = make_unique<Room>(x, y, previousRoom->distFromStart + 1);

	int lowestDistance = r->distFromStart - 1;

	for (int i = 0; i < adjacents.size(); i++)
	{
		if (lowestDistance > rooms[adjacents[i].first]->distFromStart)
			lowestDistance = rooms[adjacents[i].first]->distFromStart;

		r->AddAdjacentRoom(adjacents[i].first, adjacents[i].second);
	}

	r->distFromStart = lowestDistance + 1;

	cout << "Distance from start : " << r->distFromStart << endl;

	cout << "Avalaible doors : " << r->avalaibleDoors.size() << endl;

	for (const auto& pos : r->avalaibleDoors)
	{
		cout << pos.x << ":" << pos.y << +" |";
	}

	cout << endl << "-----------------------------------------" << endl << endl;

	Room* room = r.get();

	rooms.push_back(move(r));

	if (!bExitRoomGenerated)
		chanceToGenerate = 0.25;

	for (const auto& pos : room->avalaibleDoors)
	{
		if (GenerateNextRoom(room, pos, chanceToGenerate))
		{
			chanceToGenerate = 0.34;
		}
		else if (!bExitRoomGenerated)
		{
			chanceToGenerate += 0.33;
		}
	}

	return true;
}

float DungeonGenerator::RandomPercent()
{
	static default_random_engine engine(seed);
	uniform_int_distribution distribution(0, 100);
	return distribution(engine) / 100.0;
}

void DungeonGenerator::Draw(sf::RenderWindow* window)
{
	rooms[0]->DrawLayout(window, 0, sf::Color::Green);

	for (int i = 1; i < rooms.size(); ++i)
	{
		rooms[i]->DrawLayout(window, i, i == exitRoomIndex ? sf::Color::Red : sf::Color::Blue);
	}
}

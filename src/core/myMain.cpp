#include "myMain.h"

#include <DungeonGenerator.h>

#include <iostream>
#include <random>
#include <tmxlite/Map.hpp>
#include <SMFLOrthogonalLayer.h>
#include "Player.hpp"
#include "Gun.hpp"
#include <RandomHelper.h>

unsigned int RandomHelper::SEED = 0;

int myMain()
{
	std::random_device rd;
	RandomHelper::SEED = rd();

	DungeonGenerator generator(30, 8);
	generator.GenerateLayout();

	bool drawMiniMap = true;

	sf::RenderWindow window{ sf::VideoMode({1440, 960}), "Dungeon Generator" };
	window.setFramerateLimit(30);

	Player player(10.f, 10.f, 25.f, sf::Color::Red);
	Gun gun(5, 10, sf::Color::Yellow, 5);

	sf::Vector2f offset(0.f, 0.f);

	player.setPosition(sf::Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));

	std::vector<Enemy>* enemies = nullptr;

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last
		// iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Tab)
				{
					drawMiniMap = !drawMiniMap;
				}
			}

			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed) window.close();

			// Catch the resize events
			if (event.type == sf::Event::Resized)
			{
				// Update the view to the new size of the window, so that contents is
				// not distorted by resizing See
				// https://www.sfml-dev.org/tutorials/3.0/graphics/view/#using-a-view
				sf::FloatRect visibleArea({ 0.f, 0.f }, sf::Vector2f(event.size.width, event.size.height));
				window.setView(sf::View(visibleArea));
			}
		}

		//Player
		//fé bouger le player
		player.playerMovement();

		// Check Collisions with room's borders
		if (player.getPosition().x + player.getShape().getRadius() > window.getSize().x)
		{
			if (generator.TryMoveToAdjacentRoom({ 1, 0 }))
			{
				offset.x -= window.getSize().x;
				generator.currentRoom->SpawnEnemies();
				player.setPosition({ player.getShape().getRadius(), player.getPosition().y });
				gun.ClearBullets();
			}
			else
			{
				player.setPosition({ window.getSize().x - player.getShape().getRadius(), player.getPosition().y });
			}
		}
		else if (player.getPosition().x < 0)
		{
			if (generator.TryMoveToAdjacentRoom({ -1, 0 }))
			{
				offset.x += window.getSize().x;
				generator.currentRoom->SpawnEnemies();
				player.setPosition({ window.getSize().x - player.getShape().getRadius(), player.getPosition().y });
				gun.ClearBullets();	
			}
			else
			{
				player.setPosition({ player.getShape().getRadius(), player.getPosition().y });
			}
		}
		else if (player.getPosition().y > window.getSize().y)
		{
			if (generator.TryMoveToAdjacentRoom({ 0, -1 }))
			{
				offset.y -= window.getSize().y;
				generator.currentRoom->SpawnEnemies();
				player.setPosition({ player.getPosition().x, player.getShape().getRadius() });
				gun.ClearBullets();
			}
			else
			{
				player.setPosition({ player.getPosition().x, window.getSize().y - player.getShape().getRadius() });
			}
		}
		else if (player.getPosition().y < 0)
		{
			if (generator.TryMoveToAdjacentRoom({ 0, 1 }))
			{
				offset.y += window.getSize().y;
				generator.currentRoom->SpawnEnemies();
				player.setPosition({ player.getPosition().x, window.getSize().y - player.getShape().getRadius() });
				gun.ClearBullets();
			}
			else
			{
				player.setPosition({ player.getPosition().x, player.getShape().getRadius() });
			}
			
		}

		generator.currentRoom->CheckRemainingEnemies();
		generator.currentRoom->SetEnemiesTarget(player.getPosition());

		//Shooting
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			gun.fire(player.getPosition(), sf::Vector2f(sf::Mouse::getPosition(window)));
		}

		gun.updateBullet(&window, generator.currentRoom->enemies);

		window.clear(sf::Color::Black);

		generator.DrawMap(&window, offset);
		window.draw(player.getShape());

		std::vector<Bullet> bulletsUsed = gun.getBullets();
		for (size_t i = 0; i < bulletsUsed.size(); i++)
		{
			window.draw(bulletsUsed[i].getBullet());
		}

		if (drawMiniMap) generator.DrawLayout(&window);

		window.display();
	}

	return EXIT_SUCCESS;
}

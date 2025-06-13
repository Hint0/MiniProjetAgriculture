#include "myMain.h"

#include <DungeonGenerator.h>

#include <iostream>
#include <random>
#include <tmxlite/Map.hpp>
#include <SMFLOrthogonalLayer.h>

int myMain()
{
	std::random_device rd;
	DungeonGenerator generator(2462855252/*rd()*/, 30, 8);
	generator.GenerateLayout();

	sf::RenderWindow window{ sf::VideoMode({1440, 960}), "Dungeon Generator" };
	window.setFramerateLimit(30);

	sf::Vector2f offset( 0.f, 0.f );
	
	while (window.isOpen())
	{
		window.setFramerateLimit(30);

		// check all the window's events that were triggered since the last
		// iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Up)
				{
					offset.y += 100.f;
				}
				else if (event.key.code == sf::Keyboard::Down)
				{
					offset.y -= 100.f;
				}
				else if (event.key.code == sf::Keyboard::Left)
				{
					offset.x += 100.f;
				}
				else if (event.key.code == sf::Keyboard::Right)
				{
					offset.x -= 100.f;
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
		window.clear(sf::Color::Black);
		generator.DrawMap(&window, offset);
		generator.DrawLayout(&window);
		window.display();
	}

	return EXIT_SUCCESS;
}

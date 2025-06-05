#include "myMain.h"

#include <DungeonGenerator.h>

#include <iostream>

int myMain()
{
	DungeonGenerator generator(sf::Vector2f{ 75, 100 }, sf::Vector2f{ 5, 5 });
	generator.GenerateLayout();

	sf::RenderWindow window{ sf::VideoMode({800, 600}), "Dungeon Generator" };
	window.setFramerateLimit(30);

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last
		// iteration of the loop
		while (const std::optional event = window.pollEvent())
		{
			// "close requested" event: we close the window
			if (event->is<sf::Event::Closed>()) window.close();

			// Catch the resize events
			if (const auto* resized = event->getIf<sf::Event::Resized>())
			{
				// Update the view to the new size of the window, so that contents is
				// not distorted by resizing See
				// https://www.sfml-dev.org/tutorials/3.0/graphics/view/#using-a-view
				sf::FloatRect visibleArea({ 0.f, 0.f }, sf::Vector2f(resized->size));
				window.setView(sf::View(visibleArea));
			}
		}
		window.clear(sf::Color::White);
		generator.Draw(&window);
		window.display();
	}

	return EXIT_SUCCESS;
}

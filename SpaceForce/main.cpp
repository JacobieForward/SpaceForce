#include <SFML/Graphics.hpp>
#include "ship.h"
#include "player.h"
#include "GameController.h"
#include "Constants.h"

int main()
{
	float xWindowSize = 1000;
	float yWindowSize = 600;
	sf::RenderWindow window(sf::VideoMode(xWindowSize, yWindowSize), "SFML works!");
	sf::RectangleShape background(sf::Vector2f(xWindowSize, yWindowSize));
	background.setFillColor(sf::Color::Black);
	player *mainPlayer = new player();
	GameController *controller = new GameController();
	ship *newship = new ship(50.0f, 50.0f);
	controller->addShip(newship);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.button == sf::Mouse::Left) {
						// Left Mouse is for selecting/deselecting ships on the map
						ship *newSelectedShip = controller->findShipAtPosition(event.mouseButton.x, event.mouseButton.y);
						if (newSelectedShip != NULL) {
							mainPlayer->selectShip(newSelectedShip);
						}
						else {
							mainPlayer->deselectShip();
						}
					}
					if (event.mouseButton.button == sf::Mouse::Right) {
						// Right button is for moving ships on the map
						mainPlayer->setShipMovementWaypoint(event.mouseButton.x, event.mouseButton.y);
					}
					break;
			}
		}
		window.clear();
		controller->updateAllShips();
		window.draw(background);
		controller->displayAllShips(&window);
		window.display();
	}

	return 0;
}
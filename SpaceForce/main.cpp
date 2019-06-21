#include <SFML/Graphics.hpp>
#include "ship.h"
#include "player.h"
#include "GameController.h"
#include "Constants.h"

// TODO: For performance declare variables const in classes when they can be and see which functions work well as inlines
// TODO: Come up with better naming schema for class variables vs instance variables called in constructors
// i.e. (playerNum and playerNumber are not great side by side)

int main()
{
	float xWindowSize = 1000;
	float yWindowSize = 600;
	sf::RenderWindow window(sf::VideoMode(xWindowSize, yWindowSize), "SpaceForce");
	sf::RectangleShape background(sf::Vector2f(xWindowSize, yWindowSize));
	background.setFillColor(sf::Color::Black);
	player *mainPlayer = new player(1);
	player *enemyPlayer = new player(2);
	GameController *controller = new GameController();

	controller->spawnShip(50.0f, 50.0f, 1);
	controller->spawnShip(300.0f, 300.0f, 2);

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
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Enter) {
						mainPlayer->selectedShipLaunchTorpedo();
					}
					break;
				case sf::Event::MouseMoved:
					if (event.type == sf::Event::MouseMoved) {
						if () {

						}
					}
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
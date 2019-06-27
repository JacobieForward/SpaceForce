#include <SFML/Graphics.hpp>
#include "ship.h"
#include "player.h"
#include "GameController.h"
#include "Constants.h"
#include <iostream>

// TODO: For performance declare variables const in classes when they can be and see which functions work well as inlines
// TODO: Come up with better naming schema for class variables vs instance variables called in constructors
// i.e. (playerNum and playerNumber are not great side by side)
// TODO: Forward declare functions in next refactor, make forward declaration part of development process going forwards
// TODO: Overall the implementation of the torpedo aiming seems sloppy so far, might be worth at least taking a peak at later for refactor

int main()
{
	float xWindowSize = 1000;
	float yWindowSize = 600;
	sf::RenderWindow window(sf::VideoMode(xWindowSize, yWindowSize), "SpaceForce");
	sf::RectangleShape background(sf::Vector2f(xWindowSize, yWindowSize));
	background.setFillColor(sf::Color::Black);
	player *mainPlayer = new player(1);
	player *enemyPlayer = new player(2);
	GameController *controller = new GameController(mainPlayer);

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
						if (!mainPlayer->getSelectTorpedoDirectionMode() && mainPlayer->shipIsSelected()) {
							mainPlayer->selectTorpedoDirection();
							std::cout << "selecting torpedo direction";
						} else {
							// launch torpedo
							// TODO: Make sure to also add this for left clicking when selecting torpedo
						}
					}
					if (event.key.code == sf::Keyboard::Escape) {
						if (mainPlayer->getSelectTorpedoDirectionMode()) {
							mainPlayer->cancelSelectTorpedoDirection();
							std::cout << "not selecting torpedo direction";
						}
					}
					break;
			}
		}
		window.clear();

		window.draw(background);

		controller->updateAllShips();
		controller->displayAllShips(&window);

		if (mainPlayer->getSelectTorpedoDirectionMode()) {
			controller->updatePlayerTorpedoAimingLine(&window);
			controller->displayPlayerTorpedoAimingLine(&window);
		}
		window.display();
	}
	return 0;
}
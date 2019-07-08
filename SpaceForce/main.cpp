#include <SFML/Graphics.hpp>
#include "ship.h"
#include "player.h"
#include "Unit.h"
#include "GameController.h"
#include "Constants.h"
#include <iostream>

// TODO: For performance declare variables const in classes when they can be and see which functions work well as inlines
// TODO: Come up with better naming schema for class variables vs instance variables called in constructors
// i.e. (playerNum and playerNumber are not great side by side)
// TODO: Forward declare functions in next refactor, make forward declaration part of development process going forwards
// TODO: Overall the implementation of the torpedo aiming seems sloppy so far, might be worth at least taking a peak at later for refactor
// TODO: During refactor replace all places where coordinates are passed seperately to instead pass a Vector2f?
// TODO: Maybe I've corrupted the responsibilities of each class (i.e. torpedo launching contained in player when
// maybe it should be contained in GameController, should take a look at that during refactor)
// TODO: Set methods to private as needed, particularily in Player.h and Unit.h

int main()
{
	int xWindowSize = 1000;
	int yWindowSize = 600;
	sf::RenderWindow window(sf::VideoMode(xWindowSize, yWindowSize), "SpaceForce");
	sf::RectangleShape background(sf::Vector2f(xWindowSize, yWindowSize));
	background.setFillColor(sf::Color::Black);
	Player *mainPlayer = new Player(1);
	Player *enemyPlayer = new Player(2);
	GameController *controller = new GameController(mainPlayer);

	controller->spawnShip(50.0f, 50.0f, 1);
	controller->spawnShip(150.0f, 50.0f, 1);
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
						// When in torpedo direction selection mode it is for placing waypoints for the torpedo to follow
						if (mainPlayer->getSelectTorpedoDirectionMode()) {
							// Place torpedo waypoint
							mainPlayer->placeTorpedoWaypoint(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y));
						} else {
							// We are not in torpedo selection, attempt to select/deselect ship
							Unit* newSelectedShip = controller->findUnitAtPosition((float)event.mouseButton.x, (float)event.mouseButton.y);
							if (newSelectedShip != NULL) {
								mainPlayer->selectUnit(newSelectedShip);
							} else {
								mainPlayer->deselectUnit();
							}
						}
					}
					if (event.mouseButton.button == sf::Mouse::Right) {
						// Right button is for moving ships on the map
						mainPlayer->setUnitMovementWaypoint((float)event.mouseButton.x, (float)event.mouseButton.y);
					}
					break;
				case sf::Event::KeyPressed:
					if (event.key.code == sf::Keyboard::Enter) {
						if (!mainPlayer->getSelectTorpedoDirectionMode() && mainPlayer->unitIsSelected()) {
							mainPlayer->selectTorpedoDirection();
						} else {
							// launch torpedo
							controller->spawnTorpedo(mainPlayer->getSelectedUnitPosition().x, mainPlayer->getSelectedUnitPosition().y,
								mainPlayer->getPlayerNumber(), mainPlayer->confirmTorpedoLaunch());
						}
					}
					if (event.key.code == sf::Keyboard::Escape) {
						if (mainPlayer->getSelectTorpedoDirectionMode()) {
							mainPlayer->cancelSelectTorpedoDirection();
						}
					}
					break;
			}
		}
		window.clear();

		window.draw(background);

		controller->updateAllUnits();
		controller->checkForUnitCollisions();
		controller->displayAllUnits(&window);

		if (mainPlayer->getSelectTorpedoDirectionMode()) {
			controller->updatePlayerTorpedoAimingLine(&window);
			controller->displayPlayerTorpedoAimingLine(&window);
		}
		window.display();
	}
	return 0;
}
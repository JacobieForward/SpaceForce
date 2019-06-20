#pragma once
#include "ship.h"
#include <list>
#include <SFML/Network.hpp>
#include <iostream>

class GameController {
public:
	GameController();
	void spawnShip(float xPosition, float yPosition, int playerNumber);
	void addShip(ship* shipToAdd);
	ship* findShipAtPosition(float xPosition, float yPosition);
	void displayAllShips(sf::RenderWindow* window);
	void updateAllShips();

private:
	std::list<ship *> shipList;
	sf::Clock controllerClock;
	sf::UdpSocket socket;
};
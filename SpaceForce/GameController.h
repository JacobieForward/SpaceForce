#pragma once
#include "ship.h"
#include <list>
#include <SFML/Network.hpp>
#include <iostream>

class GameController {
public:
	GameController() {
		
	}

	void updateReceiveMessage() {

	}

	void addShip(ship *shipToAdd) {
		shipList.push_front(shipToAdd);
	}

	ship *findShipAtPosition(float xPosition, float yPosition) {
		for (ship *eachShip: shipList) {
			// If the x and y positions passed are within the bounds the a ship then that is the ship found
			if (eachShip->getIconBounds().contains(xPosition, yPosition)) {
				return eachShip;
			}
		}
		return NULL;
	}

	void displayAllShips(sf::RenderWindow *window) {
		for (ship* eachShip : shipList) {
			eachShip->display(window);
		}
	}

	void updateAllShips() {
		for (ship* eachShip : shipList) {
			eachShip->updateMove(controllerClock);
		}
	}

private:
	std::list<ship *> shipList;
	sf::Clock controllerClock;
	sf::UdpSocket socket;
};
#include "GameController.h"
#include "ship.h"

GameController::GameController() {
}

void GameController::spawnShip(float xPosition, float yPosition, int playerNumber) {
	ship* newship = new ship(xPosition, yPosition, playerNumber);
	addShip(newship);
}

void GameController::addShip(ship* shipToAdd) {
	shipList.push_front(shipToAdd);
}

ship* GameController::findShipAtPosition(float xPosition, float yPosition) {
	for (ship* eachShip : shipList) {
		// If the x and y positions passed are within the bounds the a ship then that is the ship found
		if (eachShip->getIconBounds().contains(xPosition, yPosition)) {
			return eachShip;
		}
	}
	return NULL;
}

void GameController::displayAllShips(sf::RenderWindow* window) {
	for (ship* eachShip : shipList) {
		eachShip->display(window);
	}
}

void GameController::updateAllShips() {
	for (ship* eachShip : shipList) {
		eachShip->updateMove(controllerClock);
	}
}
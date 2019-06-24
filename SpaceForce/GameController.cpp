#include "GameController.h"

GameController::GameController() {
	primaryPlayer = NULL;
}

GameController::GameController(player* userPlayer) {
	// Declared in header as well as in Constructor, will this be a problem?
	primaryPlayer = userPlayer;
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

void GameController::displayPlayerTorpedoAimingLine(sf::RenderWindow* window) {
	primaryPlayer->displayAimingLine(window);
}

void GameController::displayAllShips(sf::RenderWindow* window) {
	for (ship* eachShip : shipList) {
		eachShip->display(window);
	}
}

void GameController::updatePlayerTorpedoAimingLine(sf::RenderWindow& window) {
	primaryPlayer->updateTorpedoAimingLine(sf::Vector2f(sf::Mouse::getPosition(window)));
}

void GameController::updateAllShips() {
	for (ship* eachShip : shipList) {
		eachShip->updateMove(controllerClock);
	}
}
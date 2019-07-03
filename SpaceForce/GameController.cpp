#include "GameController.h"

GameController::GameController() {
	primaryPlayer = NULL;
	targetedShip = NULL;
}

GameController::GameController(player* userPlayer) {
	// Declared in header as well as in Constructor, will this be a problem?
	primaryPlayer = userPlayer;
	targetedShip = NULL;
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
		// If two ships are in the same location whichever happens to be first in the list will be selected
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

void GameController::updatePlayerTorpedoAimingLine(sf::RenderWindow* window) {
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window));
	primaryPlayer->updateTorpedoAimingLine(mousePosition);
	//This functionalty is kind of buried here and not very visible from main(), not super readable but workable
	ship* newTarget = findShipAtPosition(mousePosition.x, mousePosition.y);
	//targetedship should technically belong under the ship class, for now I'll leave it here
	if (targetedShip) {
		if (!newTarget) {
			targetedShip->unTargetShip();
			targetedShip = NULL;
		}
	} else if (newTarget) {
		targetedShip = newTarget;
		targetedShip->targetShip();
	}
}

void GameController::updateAllShips() {
	for (ship* eachShip : shipList) {
		eachShip->updateMove(controllerClock);
	}
}
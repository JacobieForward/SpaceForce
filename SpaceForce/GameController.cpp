#include "GameController.h"

GameController::GameController() {
	primaryPlayer = NULL;
	targetedUnit = NULL;
}

GameController::GameController(Player* userPlayer) {
	// Declared in header as well as in Constructor, will this be a problem?
	primaryPlayer = userPlayer;
	targetedUnit = NULL;
}

void GameController::spawnShip(float xPosition, float yPosition, int playerNumber) {
	Ship* newShip = new Ship(xPosition, yPosition, playerNumber);
	addUnit(newShip);
}

void GameController::spawnTorpedo(float xPosition, float yPosition, int playerNumber, sf::VertexArray waypointVertex) {
	Torpedo* newTorpedo = new Torpedo(xPosition, yPosition, playerNumber, waypointVertex);
	addUnit(newTorpedo);
}

void GameController::addUnit(Unit* unitToAdd) {
	unitList.push_front(unitToAdd);
}

Unit* GameController::findUnitAtPosition(float xPosition, float yPosition) {
	for (Unit* eachUnit : unitList) {
		// If the x and y positions passed are within the bounds the a unit then that is the unit found
		// If two units are in the same location whichever happens to be first in the list will be selected
		if (eachUnit->getIconBounds().contains(xPosition, yPosition)) {
			return eachUnit;
		}
	}
	return NULL;
}

void GameController::displayPlayerTorpedoAimingLine(sf::RenderWindow* window) {
	primaryPlayer->displayAimingLine(window);
}

void GameController::displayAllUnits(sf::RenderWindow* window) {
	for (Unit* eachUnit : unitList) {
		eachUnit->display(window);
	}
}

void GameController::updatePlayerTorpedoAimingLine(sf::RenderWindow* window) {
	sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window));
	primaryPlayer->updateTorpedoAimingLine(mousePosition);
	//This functionalty is kind of buried here and not very visible from main(), not super readable but workable
	Unit* newTarget = findUnitAtPosition(mousePosition.x, mousePosition.y);
	
	if (targetedUnit) {
		if (!newTarget) {
			targetedUnit->unTargetUnit();
			targetedUnit = NULL;
		}
	} else if (newTarget) {
		targetedUnit = newTarget;
		targetedUnit->targetUnit();
	}
}

void GameController::updateAllUnits() {
	for (Unit* eachUnit : unitList) {
		eachUnit->updateMove(controllerClock);
	}
}
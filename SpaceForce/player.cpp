#include "player.h"

player::player(int playerNumber) {
	playerNum = playerNumber;
	torpedoAimingLine[0].color = sf::Color::White;
	torpedoAimingLine[1].color = sf::Color::White;
}

void player::selectShip(ship* newShip) {
	if (playerNum == newShip->getPlayerNumber()) {
		selectedShip = newShip;
		newShip->selectShip();
	}
}

void player::deselectShip() {
	selectedShip->deSelectShip();
	if (selectedShip != NULL && !selectTorpedoDirectionMode) {
		selectedShip = NULL;
	}
}

void player::setShipMovementWaypoint(float xPosition, float yPosition) {
	if (selectedShip != NULL) {
		selectedShip->setMovementWaypoint(xPosition, yPosition);
	}
}

bool player::getSelectTorpedoDirectionMode() {
	return player::selectTorpedoDirectionMode;
}

void player::cancelSelectTorpedoDirection() {
	selectTorpedoDirectionMode = false;
}

void player::selectTorpedoDirection() {
	// Is the defensive coding here with checking for selectTorpedoDirectionMode being true worth it at all?
	// Or is it simply good to code defensively out of habit?
	if (selectedShip == NULL || selectTorpedoDirectionMode) {
		return;
	} else {
		selectTorpedoDirectionMode = true;
	}
}

void player::updateTorpedoAimingLine(sf::Vector2f destinationPosition) {
	torpedoAimingLine[0].position = selectedShip->getShipPosition();
	torpedoAimingLine[1].position = destinationPosition;
}

void player::displayAimingLine(sf::RenderWindow* win) {
	win->draw(torpedoAimingLine, 2, sf::Lines);
}
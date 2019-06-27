#include "player.h"

player::player(int playerNumber) {
	playerNum = playerNumber;
	torpedoAimingLine[0].color = sf::Color::White;
	torpedoAimingLine[1].color = sf::Color::White;
	selectTorpedoDirectionMode = NULL;
}

void player::selectShip(ship* newShip) {
	if (playerNum == newShip->getPlayerNumber()) {
		selectedShip = newShip;
		newShip->selectShip();
	}
}

void player::deselectShip() {
	if (selectTorpedoDirectionMode) {
		return;
	} else if (selectedShip) {
		selectedShip->deSelectShip();
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

bool player::shipIsSelected() {
	if (selectedShip) {
		return true;
	} else {
		return false;
	}
}

void player::cancelSelectTorpedoDirection() {
	selectTorpedoDirectionMode = false;
}

void player::selectTorpedoDirection() {
	if (!selectedShip) {
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
#include "player.h"

player::player(int playerNumber) {
	playerNum = playerNumber;
	torpedoAimingLines.setPrimitiveType(sf::Lines);
	torpedoAimingLines.resize(2);
	selectTorpedoDirectionMode = NULL;
	currentTorpedoWaypoint.x = -100.0f;
	currentTorpedoWaypoint.y = -100.0f;
}

void player::selectShip(ship* newShip) {
	if (playerNum == newShip->getPlayerNumber()) {
		if (selectedShip) {
			selectedShip->deSelectShip();
		}
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
	torpedoAimingLines[0].position = selectedShip->getShipPosition();
	torpedoAimingLines[torpedoAimingLines.getVertexCount() - 1].position = destinationPosition;
}

void player::displayAimingLine(sf::RenderWindow* win) {
	win->draw(torpedoAimingLines);
}

void player::placeTorpedoWaypoint(sf::Vector2f newWaypointPosition) {
	torpedoAimingLines.append(newWaypointPosition);
	torpedoAimingLines.append(sf::Vector2f(0.0f, 0.0f));
}
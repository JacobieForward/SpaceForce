#include "player.h"

player::player(int playerNumber) {
	playerNum = playerNumber;
}

void player::selectShip(ship* newShip) {
	if (playerNum == newShip->getPlayerNumber()) {
		selectedShip = newShip;
		newShip->selectShip();
	}
}

void player::deselectShip() {
	selectedShip->deSelectShip();
	if (selectedShip != NULL) {
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

void player::selectTorpedoDirection() {
	// Is the defensive coding here with checking for selectTorpedoDirectionMode being true worth it at all?
	// Or is it simply good to code defensively out of habit?
	if (selectedShip == NULL || selectTorpedoDirectionMode) {
		return;
	} else {
		selectTorpedoDirectionMode = true;
	}
}

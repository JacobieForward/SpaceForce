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

void selectedShipLaunchTorpedo() {

}

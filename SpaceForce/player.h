#pragma once
#include "ship.h"

class player {
public:
	player() {

	}

	void selectShip(ship *newShip) {
		selectedShip = newShip;
		newShip->selectShip();
	}

	void deselectShip() {
		selectedShip->deSelectShip();
		selectedShip = NULL;
	}

	void setShipMovementWaypoint(float xPosition, float yPosition) {
		if (selectedShip != NULL) {
			selectedShip->setMovementWaypoint(xPosition, yPosition);
		}
	}

private:
	ship *selectedShip = NULL;
};
#pragma once
#include "ship.h"

class player {
public:
	player(int);
	void selectShip(ship* newShip);
	void deselectShip();
	void setShipMovementWaypoint(float xPosition, float yPosition);

private:
	ship *selectedShip = NULL;
	int playerNum;
};
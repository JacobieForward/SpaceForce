#pragma once
#include "ship.h"

class player {
public:
	player(int);
	void selectShip(ship* newShip);
	void deselectShip();
	void setShipMovementWaypoint(float xPosition, float yPosition);
	void selectTorpedoDirection();
	bool getSelectTorpedoDirectionMode();

private:
	ship *selectedShip = NULL;
	bool selectTorpedoDirectionMode = false;
	int playerNum;
};
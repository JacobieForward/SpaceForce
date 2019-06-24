#pragma once
#include "ship.h"
#include <SFML\graphics.hpp>

class player {
public:
	player(int);
	void selectShip(ship* newShip);
	void deselectShip();
	void setShipMovementWaypoint(float xPosition, float yPosition);
	void selectTorpedoDirection();
	void cancelSelectTorpedoDirection();
	bool getSelectTorpedoDirectionMode();
	void updateTorpedoAimingLine(sf::Vector2f destinationPosition);
	void displayAimingLine(sf::RenderWindow* win);

private:
	ship *selectedShip = NULL;
	bool selectTorpedoDirectionMode = false;
	int playerNum;
	sf::Vertex torpedoAimingLine[2];
};
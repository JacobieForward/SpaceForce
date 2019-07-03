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
	bool shipIsSelected();
	void updateTorpedoAimingLine(sf::Vector2f destinationPosition);
	void displayAimingLine(sf::RenderWindow* win);
	void placeTorpedoWaypoint(sf::Vector2f newWaypointPosition);

private:
	ship *selectedShip = NULL;
	bool selectTorpedoDirectionMode;
	int playerNum;
	sf::Vector2f currentTorpedoWaypoint;
	sf::VertexArray torpedoAimingLines;
};
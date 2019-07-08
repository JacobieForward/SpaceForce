#pragma once
#include "Unit.h"
#include <SFML\graphics.hpp>

class Player {
public:
	Player(int);
	void selectUnit(Unit* newUnit);
	void deselectUnit();
	void setUnitMovementWaypoint(float xPosition, float yPosition);
	void selectTorpedoDirection();
	void cancelSelectTorpedoDirection();
	sf::VertexArray confirmTorpedoLaunch();
	bool getSelectTorpedoDirectionMode();
	bool unitIsSelected();
	void updateTorpedoAimingLine(sf::Vector2f destinationPosition);
	void displayAimingLine(sf::RenderWindow* win);
	void placeTorpedoWaypoint(sf::Vector2f newWaypointPosition);
	int getPlayerNumber();
	sf::Vector2f getSelectedUnitPosition();

private:
	Unit* selectedUnit = NULL;
	bool selectTorpedoDirectionMode;
	int playerNum;
	sf::Vector2f currentTorpedoWaypoint;
	sf::VertexArray torpedoAimingLines;
};
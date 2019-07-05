#pragma once
#include "Unit.h"
#include <list>

class Torpedo : public Unit {
public:
	Torpedo(float xSpawnPosition, float ySpawnPosition, int owningPlayerNum, sf::VertexArray vertexArray);
	void updateMove(sf::Clock clock); // Overrides declartion of updateMove in Unit to allow following of waypoints

private:
	void checkForNewWaypoint();

	std::list<sf::Vector2f> waypointList;
};
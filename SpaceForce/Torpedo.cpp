#include "Torpedo.h"
#include <iostream>

Torpedo::Torpedo(float xSpawnPosition, float ySpawnPosition, int owningPlayerNum, sf::VertexArray vertexArray) {
	icon.setRadius(10.0f);
	icon.setPosition(sf::Vector2f(xSpawnPosition, ySpawnPosition));
	icon.setOutlineColor(sf::Color::Red);
	unSelectedColor = sf::Color::Blue;
	selectedColor = sf::Color::Red;
	icon.setFillColor(unSelectedColor);

	speed = 0.0001f;
	vectorToMoveTo = icon.getPosition();
	owningPlayerNumber = owningPlayerNum;

	for (int x = 0; x < vertexArray.getVertexCount(); x++) {
		waypointList.push_back(vertexArray[x].position);
	}
	waypointList.pop_front(); // Get rid of ship position in vectorlist

	if (waypointList.size() > 0) {
		vectorToMoveTo = waypointList.front();
	}
}

void Torpedo::updateMove(sf::Clock clock) {
	std::cout << "Torpedo on the move";
	// In the overridden method for Torpedos checkForNewWaypoint handles the waypoints assigned at torpedo creation
	checkForNewWaypoint();

	Unit::updateMove(clock);
}

void Torpedo::checkForNewWaypoint() {
	if (waypointList.size() > 0 && vectorToMoveTo.x < 0 && vectorToMoveTo.y < 0) {
		vectorToMoveTo = waypointList.front();
	}
}
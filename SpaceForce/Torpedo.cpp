#include "Torpedo.h"
#include <iostream>

Torpedo::Torpedo(float xSpawnPosition, float ySpawnPosition, int owningPlayerNum, sf::VertexArray vertexArray) {
	icon.setRadius(5.0f);
	icon.setPointCount(3);
	icon.setPosition(sf::Vector2f(xSpawnPosition, ySpawnPosition));
	icon.setOutlineColor(sf::Color::Red);
	unSelectedColor = sf::Color::White;
	selectedColor = sf::Color::Red;
	icon.setFillColor(unSelectedColor);

	speed = 0.0001f;
	vectorToMoveTo = icon.getPosition();
	owningPlayerNumber = owningPlayerNum;

	for (int x = 0; x <= vertexArray.getVertexCount(); x+=2) {
		waypointList.push_back(vertexArray[x].position);
		std::cout << "Added waypoint: " + std::to_string(vertexArray[x].position.x) + " , " + std::to_string(vertexArray[x].position.y);
	}
	waypointList.pop_back(); // Remove the weird waypoint from the back
}
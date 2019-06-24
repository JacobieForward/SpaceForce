#include "ship.h"

ship::ship(float xSpawnPosition, float ySpawnPosition, int owningPlayerNum) {
	icon.setRadius(10.0f);
	icon.setPosition(sf::Vector2f(xSpawnPosition, ySpawnPosition));
	unSelectedColor = sf::Color::Blue;
	selectedColor = sf::Color::Red;
	icon.setFillColor(unSelectedColor);

	speed = 0.00001f;
	vectorToMoveTo = icon.getPosition();
	owningPlayerNumber = owningPlayerNum;
}

void ship::display(sf::RenderWindow* win) {
	win->draw(icon);
}

sf::FloatRect ship::getIconBounds() {
	return icon.getGlobalBounds();
}

sf::Vector2f ship::getShipPosition() {
	return icon.getPosition();
}

void ship::selectShip() {
	icon.setFillColor(selectedColor);
}

void ship::deSelectShip() {
	icon.setFillColor(unSelectedColor);
}

void ship::setMovementWaypoint(float xPosition, float yPosition) {
	vectorToMoveTo = sf::Vector2f(xPosition, yPosition);
}

void ship::updateMove(sf::Clock clock) {
	// Get the vector of the ships direction and then normalise it
	// Possibly later safe on computation time by keeping the same calculation unless a change is made?
	sf::Vector2f direction = (vectorToMoveTo - icon.getPosition());
	float delta = clock.restart().asSeconds() * 60;

	// Normalize the direction vector
	float directionMagnitude = sqrt((direction.x * direction.x) + (direction.y * direction.y));
	if (directionMagnitude <= 0.f) {
		//icon.move(delta * speed * direction);
		return;
	}
	direction = direction / directionMagnitude;

	icon.move(delta * speed * direction);
}

int ship::getPlayerNumber() {
	return owningPlayerNumber;
}

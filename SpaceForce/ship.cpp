#include "ship.h"

ship::ship(float xSpawnPosition, float ySpawnPosition, int owningPlayerNum) {
	icon.setRadius(10.0f);
	icon.setPosition(sf::Vector2f(xSpawnPosition, ySpawnPosition));
	icon.setOutlineColor(sf::Color::Red);
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

	direction = normalizeVector2f(direction);

	icon.move(delta * speed * direction);
}

// Need a more accessable place to put this. Maybe GameController, or try to override Vector2. Will likely need normalization later
sf::Vector2f ship::normalizeVector2f(sf::Vector2f vectorToNormalize) {
	// Normalize the direction vector
	float vectorToNormalizeMagnitude = sqrt((vectorToNormalize.x * vectorToNormalize.x) + (vectorToNormalize.y * vectorToNormalize.y));
	if (vectorToNormalizeMagnitude <= 0.f) {
		//icon.move(delta * speed * direction);
		return vectorToNormalize;
	}
	vectorToNormalize = vectorToNormalize / vectorToNormalizeMagnitude;
	return vectorToNormalize;
}

int ship::getPlayerNumber() {
	return owningPlayerNumber;
}

void ship::targetShip() {
	icon.setOutlineThickness(5.0f);
}

void ship::unTargetShip() {
	icon.setOutlineThickness(0);
}
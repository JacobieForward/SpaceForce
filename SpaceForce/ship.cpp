#include "ship.h"

Ship::Ship(float xSpawnPosition, float ySpawnPosition, int owningPlayerNum) {
	icon.setRadius(10.0f);
	icon.setPosition(sf::Vector2f(xSpawnPosition, ySpawnPosition));
	icon.setOutlineColor(sf::Color::Red);
	unSelectedColor = sf::Color::Blue;
	selectedColor = sf::Color::Red;
	icon.setFillColor(unSelectedColor);

	speed = 0.00001f;
	vectorToMoveTo = icon.getPosition();
	owningPlayerNumber = owningPlayerNum;
};
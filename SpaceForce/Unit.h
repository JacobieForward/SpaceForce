#pragma once
#include <list>
#include <SFML\graphics.hpp>
#include <SFML\System\Vector2.hpp>
#include <iostream>

class Unit {
public:
	Unit(void) {}
	~Unit(void) {
		std::cout << "Unit Destructor Called\n";
	}
	
	void selectUnit() {
		icon.setFillColor(selectedColor);
		std::cout << "Unit Position = " + std::to_string(getUnitPosition().x) + " , " + std::to_string(getUnitPosition().y);
	}

	void deSelectUnit() {
		icon.setFillColor(unSelectedColor);
	}

	int getPlayerNumber() {
		return owningPlayerNumber;
	}

	void targetUnit() {
		icon.setOutlineThickness(5.0f);
	}

	void unTargetUnit() {
		icon.setOutlineThickness(0);
	}

	void updateMove(sf::Clock clock) {
		checkForNewWaypoint();
		setRotationToMovementWaypoint();

		// Get the vector of the ships direction and then normalise it
		// Possibly later safe on computation time by keeping the same calculation unless a change is made
		if (vectorToMoveTo.x >= 0 && vectorToMoveTo.y >= 0) {
			sf::Vector2f direction = (vectorToMoveTo - icon.getPosition());
			float delta = clock.restart().asSeconds() * 60;

			direction = normalizeVector2f(direction);

			icon.move(delta * speed * direction);
		}
	}

	void display(sf::RenderWindow* win) {
		win->draw(icon);
	}

	sf::FloatRect getIconBounds() {
		return icon.getGlobalBounds();
	}

	sf::Vector2f getUnitPosition() {
		return icon.getPosition();
	}

	// Need a more accessable place to put this. Maybe GameController, or try to override Vector2. Will likely need normalization later
	sf::Vector2f normalizeVector2f(sf::Vector2f vectorToNormalize) {
		// Normalize the direction vector
		float vectorToNormalizeMagnitude = getVectorMagnitude(vectorToNormalize);
		if (vectorToNormalizeMagnitude <= 0.f) {
			return vectorToNormalize;
		}
		vectorToNormalize = vectorToNormalize / vectorToNormalizeMagnitude;
		return vectorToNormalize;
	}

	void setMovementWaypoint(float xPosition, float yPosition) {
		vectorToMoveTo = sf::Vector2f(xPosition, yPosition);
	}

	sf::CircleShape icon;
	sf::Color unSelectedColor;
	sf::Color selectedColor;
	int owningPlayerNumber;
	float speed;
	sf::Vector2f vectorToMoveTo;
	std::list<sf::Vector2f> waypointList;

private:
	void checkForNewWaypoint() {
		if (checkIfPositionEqualToMoveVector() && vectorToMoveTo.x > 0 && vectorToMoveTo.y > 0) {
			vectorToMoveTo.x = -100;
			vectorToMoveTo.y = -100;
			std::cout << "Reached Destination + \n";
		}
		if (waypointList.size() > 0 && vectorToMoveTo.x < 0 && vectorToMoveTo.y < 0) {
			std::cout << "Assigned new destination + \n";
			waypointList.pop_front();
			vectorToMoveTo = waypointList.front();
		}
	}

	float getVectorMagnitude(sf::Vector2f vectorToGetMagnitude) {
		return sqrt((vectorToGetMagnitude.x * vectorToGetMagnitude.x) + (vectorToGetMagnitude.y * vectorToGetMagnitude.y));
	}

	void setRotationToMovementWaypoint() {
		// TODO: Test this out and see if/why its not working. Rotation doesn't seem to change
		// Not a high priority item though
		icon.setRotation(atan(vectorToMoveTo.y - icon.getPosition().y/vectorToMoveTo.x - icon.getPosition().x));
	}

	// Could override the Vector2 == operator instead of this potentially
	bool checkIfPositionEqualToMoveVector() {
		return (vectorToMoveTo == icon.getPosition()
				|| (getIconBounds().contains(vectorToMoveTo.x - 1, vectorToMoveTo.y - 1))
				|| (getIconBounds().contains(vectorToMoveTo.x + 1, vectorToMoveTo.y - 1))
				|| (getIconBounds().contains(vectorToMoveTo.x - 1, vectorToMoveTo.y + 1))
				|| (getIconBounds().contains(vectorToMoveTo.x + 1, vectorToMoveTo.y + 1)));
	}
};
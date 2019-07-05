#pragma once
#include <SFML\graphics.hpp>
#include <SFML\System\Vector2.hpp>

class Unit {
public:
	sf::CircleShape icon;
	sf::Color unSelectedColor;
	sf::Color selectedColor;
	int owningPlayerNumber;
	float speed;
	sf::Vector2f vectorToMoveTo;

	Unit(void) {}
	~Unit(void) {}
	
	void selectUnit() {
		icon.setFillColor(selectedColor);
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
		// Get the vector of the ships direction and then normalise it
		// Possibly later safe on computation time by keeping the same calculation unless a change is made?
		if (vectorToMoveTo == icon.getPosition()) {
			vectorToMoveTo.x = -1000; // In place of a good null value (0 not usable due to being the top left edge
			vectorToMoveTo.y = -1000;
		}
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
		float vectorToNormalizeMagnitude = sqrt((vectorToNormalize.x * vectorToNormalize.x) + (vectorToNormalize.y * vectorToNormalize.y));
		if (vectorToNormalizeMagnitude <= 0.f) {
			//icon.move(delta * speed * direction);
			return vectorToNormalize;
		}
		vectorToNormalize = vectorToNormalize / vectorToNormalizeMagnitude;
		return vectorToNormalize;
	}

	void setMovementWaypoint(float xPosition, float yPosition) {
		vectorToMoveTo = sf::Vector2f(xPosition, yPosition);
	}

private:
	
};
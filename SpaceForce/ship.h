#pragma once
#include <SFML\graphics.hpp>
#include <SFML\System\Vector2.hpp>

class ship {
public:
	ship(float xSpawnPosition, float ySpawnPosition) {
		icon.setRadius(10.0f);
		icon.setPosition(sf::Vector2f(xSpawnPosition, ySpawnPosition));
		unSelectedColor = sf::Color::Blue;
		selectedColor = sf::Color::Red;
		icon.setFillColor(unSelectedColor);

		speed = 0.0001f;
		vectorToMoveTo = icon.getPosition();
	}

	void display(sf::RenderWindow *win) {
		win->draw(icon);
	}

	sf::FloatRect getIconBounds() {
		return icon.getGlobalBounds();
	}

	void selectShip() {
		icon.setFillColor(selectedColor);
	}

	void deSelectShip() {
		icon.setFillColor(unSelectedColor);
	}

	void setMovementWaypoint(float xPosition, float yPosition) {
		vectorToMoveTo = sf::Vector2f(xPosition, yPosition);
	}

	void updateMove(sf::Clock clock) {
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

private:
	sf::CircleShape icon;
	sf::Color unSelectedColor;
	sf::Color selectedColor;

	sf::Vector2f vectorToMoveTo;
	float speed;
};
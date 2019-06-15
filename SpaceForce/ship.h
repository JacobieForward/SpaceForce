#pragma once
#include <SFML\graphics.hpp>

class ship {
public:
	ship(float xSpawnPosition, float ySpawnPosition) {
		icon.setRadius(10.0f);
		icon.setPosition(sf::Vector2f(xSpawnPosition, ySpawnPosition));
		unSelectedColor = sf::Color::Blue;
		selectedColor = sf::Color::Red;
		icon.setFillColor(unSelectedColor);

		speed = 0.000001f;
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
		// TODO: Add normalization
		sf::Vector2f direction = vectorToMoveTo - icon.getPosition();
		float delta = clock.restart().asSeconds() * 60;
		icon.move(delta * speed * direction);
	}

	/*void moveShip(float xPosition, float yPosition) {
		icon.move(xPosition - icon.getPosition().x, yPosition - icon.getPosition().y);
	}*/

private:
	sf::CircleShape icon;
	sf::Color unSelectedColor;
	sf::Color selectedColor;

	sf::Vector2f vectorToMoveTo;
	float speed;
};
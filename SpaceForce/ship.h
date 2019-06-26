#pragma once
#include <SFML\graphics.hpp>
#include <SFML\System\Vector2.hpp>

class ship {
public:
	ship(float xSpawnPosition, float ySpawnPosition, int owningPlayerNum);
	void display(sf::RenderWindow* win);
	sf::FloatRect getIconBounds();
	sf::Vector2f getShipPosition();
	void selectShip();
	void deSelectShip();
	void setMovementWaypoint(float xPosition, float yPosition);
	void updateMove(sf::Clock clock);
	sf::Vector2f normalizeVector2f(sf::Vector2f vectorToNormalize);
	int getPlayerNumber();
	void targetShip();
	void unTargetShip();

private:
	sf::CircleShape icon;
	sf::Color unSelectedColor;
	sf::Color selectedColor;

	sf::Vector2f vectorToMoveTo;
	float speed;
	int owningPlayerNumber;
};
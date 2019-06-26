#pragma once
#include "ship.h"
#include "player.h"
#include <SFML/Window.hpp>
#include <list>

class GameController {
public:
	GameController();
	GameController(player* userPlayer);
	void spawnShip(float xPosition, float yPosition, int playerNumber);
	void addShip(ship* shipToAdd);
	ship* findShipAtPosition(float xPosition, float yPosition);
	void displayAllShips(sf::RenderWindow* window);
	void displayPlayerTorpedoAimingLine(sf::RenderWindow* window);
	void updateAllShips();
	void updatePlayerTorpedoAimingLine(sf::RenderWindow& window);

	enum class GameState{MAINMENU, SINGLEPLAYER, MULTIPLAYER, PAUSED};


private:
	std::list<ship *> shipList;
	player* primaryPlayer;
	sf::Clock controllerClock;
	ship* targetedShip;
};
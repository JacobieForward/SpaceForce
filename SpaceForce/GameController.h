#pragma once
#include "ship.h"
#include "Torpedo.h"
#include "player.h"
#include <SFML/Window.hpp>
#include <list>

class GameController {
public:
	GameController();
	GameController(Player* userPlayer);
	void spawnShip(float xPosition, float yPosition, int playerNumber);
	void spawnTorpedo(float xPosition, float yPosition, int playerNumber, sf::VertexArray waypointVertex);
	void addUnit(Unit* unitToAdd);
	Unit* findUnitAtPosition(float xPosition, float yPosition);
	void displayAllUnits(sf::RenderWindow* window);
	void displayPlayerTorpedoAimingLine(sf::RenderWindow* window);
	void updateAllUnits();
	void updatePlayerTorpedoAimingLine(sf::RenderWindow* window);

	// TODO: Implement menus using these enums. Will probably need to rework the types
	enum class GameState{MAINMENU, SINGLEPLAYER, MULTIPLAYER, PAUSED};


private:
	std::list<Unit *> unitList;
	Player* primaryPlayer;
	sf::Clock controllerClock;
	Unit* targetedUnit;
};
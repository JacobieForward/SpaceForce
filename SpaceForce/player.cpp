#include "player.h"

Player::Player(int playerNumber) {
	playerNum = playerNumber;
	torpedoAimingLines.setPrimitiveType(sf::Lines);
	torpedoAimingLines.resize(2);
	selectTorpedoDirectionMode = NULL;
	currentTorpedoWaypoint.x = -100.0f;
	currentTorpedoWaypoint.y = -100.0f;
}

void Player::selectUnit(Unit* newShip) {
	if (playerNum == newShip->getPlayerNumber()) {
		if (selectedUnit) {
			selectedUnit->deSelectUnit();
		}
		selectedUnit = newShip;
		newShip->selectUnit();
	}
}

void Player::deselectUnit() {
	if (selectTorpedoDirectionMode) {
		return;
	}
	else if (selectedUnit) {
		selectedUnit->deSelectUnit();
		selectedUnit = NULL;
	}
}

void Player::setUnitMovementWaypoint(float xPosition, float yPosition) {
	if (selectedUnit != NULL) {
		selectedUnit->setMovementWaypoint(xPosition, yPosition);
	}
}

bool Player::getSelectTorpedoDirectionMode() {
	return Player::selectTorpedoDirectionMode;
}

bool Player::unitIsSelected() {
	if (selectedUnit) {
		return true;
	}
	else {
		return false;
	}
}

void Player::cancelSelectTorpedoDirection() {
	selectTorpedoDirectionMode = false;
	torpedoAimingLines.clear();
	torpedoAimingLines.resize(2);
}

sf::VertexArray Player::confirmTorpedoLaunch() {
	// TODO: How is this for memory management? Does this leave a floating spot in memory? Needs research.
	// A pointer might be good assuming the values can be assigned from it before cancelSelecteTorpedoDirection
	// clears the vertexArray that is referenced
	sf::VertexArray tempVertex = torpedoAimingLines;

	cancelSelectTorpedoDirection();
	return tempVertex;
}

void Player::selectTorpedoDirection() {
	if (!selectedUnit) {
		return;
	}
	else {
		selectTorpedoDirectionMode = true;
	}
}

void Player::updateTorpedoAimingLine(sf::Vector2f destinationPosition) {
	torpedoAimingLines[0].position = selectedUnit->getUnitPosition();
	torpedoAimingLines[torpedoAimingLines.getVertexCount() - 1].position = destinationPosition;
}

void Player::displayAimingLine(sf::RenderWindow* win) {
	win->draw(torpedoAimingLines);
}

void Player::placeTorpedoWaypoint(sf::Vector2f newWaypointPosition) {
	torpedoAimingLines.append(newWaypointPosition);
	torpedoAimingLines.append(sf::Vector2f(0.0f, 0.0f));
}

int Player::getPlayerNumber() {
	return playerNum;
}

sf::Vector2f Player::getSelectedUnitPosition() {
	return selectedUnit->getUnitPosition();
}
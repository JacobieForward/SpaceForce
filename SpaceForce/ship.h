#pragma once
#include "Unit.h"

class Ship : public Unit {
public:
	Ship(float xSpawnPosition, float ySpawnPosition, int owningPlayerNum);
};
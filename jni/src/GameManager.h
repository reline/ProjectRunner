#pragma once

#include "Thing.h"
#include <vector>

class GameManager
{
public:
	GameManager();
	static GameManager* instance;
	std::vector<Thing*> lanes;
};
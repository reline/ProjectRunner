#pragma once

#include "Thing.h"
#include "Vector2.h"
#include <vector>

class GameManager
{
public:
	GameManager();
	static GameManager* instance;
	std::vector<Vector2> lanes;
};
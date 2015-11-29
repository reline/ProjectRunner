#pragma once

#include "Thing.h"
#include "Vector2.h"
#include <vector>
#include <SDL_mixer.h>

class GameManager
{
public:
	GameManager();
	static GameManager* instance;
	static Mix_Chunk* hurtSound;
	std::vector<Vector2> lanes;
};
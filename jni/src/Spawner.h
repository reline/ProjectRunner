#pragma once
#include <stdlib.h>
#include <time.h>

#include "Thing.h"
#include "GameManager.h"
#include "Game.h"
#include "ConstantMovement.h"

class Spawner : Thing
{
private:
	Thing* GetRandomLane();

public:
	Spawner(Transform transform = Transform());

	void Tick() override;
	void SpawnRandomObstical();
};
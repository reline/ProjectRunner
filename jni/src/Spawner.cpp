#include "Spawner.h"

Spawner::Spawner(Transform transform)
	: Thing(transform)
{
	srand(time(0));
	hasSpawnedThisScore = false;
}

Vector2& Spawner::GetRandomLane()
{
	return GameManager::instance->lanes[rand() % 3];
}

void Spawner::SpawnRandomObstacle()
{
	ConstantMovement* t = new ConstantMovement(
		Transform(GetRandomLane()), 
		"52_hello_mobile/hello.bmp", Vector2(0, 1)); // (startLocation, imageFilePath, velocity)
}

void Spawner::Tick()
{
	// if(!(Game::instance->frames % 300))
	// 	SpawnRandomObstacle();
	if (Game::instance->score % 5 == 0)
	{
		if(!hasSpawnedThisScore)
			SpawnRandomObstacle();
		hasSpawnedThisScore = true;
	}
	else
		hasSpawnedThisScore = false;
}
#include "Spawner.h"

Spawner::Spawner(Transform transform)
	: Thing(transform)
{
	srand(time(0));
	hasSpawnedThisScore = false;
	obstacleSpeed = Vector2(0,5);
}

Vector2& Spawner::GetRandomLane()
{
	return GameManager::instance->lanes[rand() % 3];
}

void Spawner::SpawnRandomObstacle()
{
	ConstantMovement* t = new ConstantMovement(
		Transform(GetRandomLane()), 
		"52_hello_mobile/Enemy.bmp", obstacleSpeed); // (startLocation, imageFilePath, velocity)
}

void Spawner::Tick()
{
	if (Game::instance->score % 1 == 0)
	{
		if(!hasSpawnedThisScore)
		{
			int secondsToSpawn = rand() % 5 + 1; // in order to have increased spawning, we have to make this smaller over time.
			if (Game::instance->score % secondsToSpawn == 0)
				SpawnRandomObstacle();
		}
		hasSpawnedThisScore = true;
	}
	else
		hasSpawnedThisScore = false;
}
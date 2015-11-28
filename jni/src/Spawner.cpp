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
		"52_hello_mobile/Enemy1.bmp", obstacleSpeed); // (startLocation, imageFilePath, velocity)
	t->transform.position.x -= (t->image.getWidth() / 2);
}

void Spawner::Tick()
{
	if (Game::instance->score % 2 == 0)
	{
		if(!hasSpawnedThisScore)
			SpawnRandomObstacle();
		hasSpawnedThisScore = true;
	}
	else
		hasSpawnedThisScore = false;
}
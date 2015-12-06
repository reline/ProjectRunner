#include "Spawner.h"

Spawner* Spawner::instance = nullptr;

Spawner::Spawner(Transform transform)
	: Thing(transform)
{
	srand(time(0));
	hasSpawnedThisScore = false;
	hasIncreasedSpeed = false;
	obstacleSpeed = Vector2(0,5);
	maxSpeed = 30;
	obstacleSpawnTime = 2;
	currentSpawnTime = 0;
	spawnTimeSubtractor = 1;
	instance = this;
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
	if (obstacleSpawnTime == 1 && currentSpawnTime != Game::instance->score)
	{
		SpawnRandomObstacle();
		currentSpawnTime = Game::instance->score;
	}
	if (obstacleSpawnTime != 1 && Game::instance->score % obstacleSpawnTime == 0)
	{
		if(!hasSpawnedThisScore)
		{
			SpawnRandomObstacle();
			if (Game::instance->score % 30 == 0 && obstacleSpawnTime > 1 && Game::instance->score != 0)
			{
				obstacleSpawnTime = obstacleSpawnTime - spawnTimeSubtractor;
				currentSpawnTime = Game::instance->score;
			}
		}
		hasSpawnedThisScore = true;
	}
	else
		hasSpawnedThisScore = false;
	if (obstacleSpeed.y <= maxSpeed)
	{
		if (Game::instance->score % 5 == 0)
		{
			if (!hasIncreasedSpeed)
				obstacleSpeed.y++;
			hasIncreasedSpeed = true;
		}
		else 
			hasIncreasedSpeed = false;
	}
}
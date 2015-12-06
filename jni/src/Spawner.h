#pragma once
#include <stdlib.h>
#include <time.h>
#include <vector>

#include "Thing.h"
#include "GameManager.h"
#include "Game.h"
#include "ConstantMovement.h"

class Spawner : Thing
{
private:
	Vector2& GetRandomLane();

	bool hasSpawnedThisScore;
	bool hasIncreasedSpeed;
	float maxSpeed;
	int obstacleSpawnTime;
	int spawnTimeSubtractor;
	int currentSpawnTime;
	std::vector<ConstantMovement> obstacles;

public:
	static Spawner* instance;

	Spawner(Transform transform = Transform());

	void Tick() override;
	void SpawnRandomObstacle();

	Vector2 obstacleSpeed;
};
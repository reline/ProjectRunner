#include "Spawner.h"

Spawner::Spawner(Transform transform)
	: Thing(transform)
{
	srand(time(0));
}

Thing* Spawner::GetRandomLane()
{
	return GameManager::instance->lanes[rand() % 3];
}

void Spawner::SpawnRandomObstical()
{
	ConstantMovement* t = new ConstantMovement(
		Transform(Vector2(transform.position.x, transform.position.y)), 
		"52_hello_mobile/hello.bmp", Vector2(0, 1)); // (startLocation, imageFilePath, velocity)
}

void Spawner::Tick()
{
	if(!(Game::instance->frames % 300))
		SpawnRandomObstical();
}
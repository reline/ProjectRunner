#include "ConstantMovement.h"

ConstantMovement::ConstantMovement()
{
	velocity = Vector2();
}

ConstantMovement::ConstantMovement(Transform transform = Transform(), string filePath = "", Vector2 velocity = Vector2())
	: Thing(transform, filePath)
{
	this->velocity = velocity;
}

ConstantMovement::~ConstantMovement() { }

void ConstantMovement::Tick()
{
	Thing::Tick();
	// constantly move the object across the screen at its current velocity
	this->transform.position += velocity;
}
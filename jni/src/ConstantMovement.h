#pragma once

#include "Thing.h"
#include "Vector2.h"

using std::string;

class ConstantMovement : public Thing
{
public:

	Vector2 velocity;

	ConstantMovement();
	ConstantMovement(Transform transform, string filePath, Vector2 velocity);
	~ConstantMovement();
	virtual void Tick() override;
};
#pragma once

#include "ConstantMovement.h"

#define LEFT 1
#define CENTER 2
#define RIGHT 3

using std::string;

class Player : public ConstantMovement
{
public:
	uint currentLane;

	Player();
	Player(Transform transform, string filePath, Vector2 velocity, uint initLane);
	~Player();
	virtual void Tick() override;

	// change lanes
	void moveLeft(int screenWidth);
	void moveRight(int screenWidth);

	// turning
	void turnLeft();
	void turnRight();

	uint getLane();
};
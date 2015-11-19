#pragma once

#include "Thing.h"
#include "ConstantMovement.h"

#define LEFT 1
#define CENTER 2
#define RIGHT 3

using std::string;

class Player : public Thing
{
public:
	uint currentLane;
	Player();
	Player(Transform transform = Transform(), string filePath = "", int priority = 1, uint initLane = CENTER);
	~Player();
	void Tick() override;

	// change lanes
	void moveLeft(int screenWidth);
	void moveRight(int screenWidth);

	// turning
	void turnLeft();
	void turnRight();

	uint getLane();
};
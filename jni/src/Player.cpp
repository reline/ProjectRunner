#include "Player.h"

#define LEFT 1
#define CENTER 2
#define RIGHT 3

Player::Player()
{
	// our player normally starts in the center
	this->currentLane = CENTER;
}

Player::Player(Transform transform, string filePath, int priority, uint initLane)
	: Thing(transform, filePath, priority)
{
	this->currentLane = initLane;
}

Player::~Player() { }

void Player::moveLeft(int distance) // should i pass how much to move, or the screen width?
{
	// safety check
	if(this->currentLane != LEFT)
	{
		this->transform.position.x -= distance;
		currentLane -= 1;
	}
}

void Player::moveRight(int distance)
{
	// safety check
	if(this->currentLane != RIGHT)
	{
		this->transform.position.x += distance; 
		currentLane += 1;
	}
}

void Player::turnLeft()
{
	// TODO
}

void Player::turnRight()
{
	// TODO
}

uint Player::getLane()
{
	return this->currentLane;
}
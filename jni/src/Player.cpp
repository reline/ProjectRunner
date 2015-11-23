#include "Player.h"

#define LEFT 1
#define CENTER 2
#define RIGHT 3

Player::Player()
{
	// our player normally starts in the center
	this->currentLane = CENTER;
	collisionState = CollisionState::NoCollision;
}

Player::Player(Transform transform, string filePath, int priority, uint initLane)
	: Thing(transform, filePath, priority)
{
	this->currentLane = initLane;
}

Player::~Player() { }

void Player::Tick()
{
	Super::Tick();
	bool foundCollision = false;
	for(auto &it : Thing::things)
	{
		for(Thing* thing : it.second)
		{
			if(thing == nullptr)
				continue;
			if(SDL_HasIntersection(&rect, &thing->rect) && dynamic_cast<ConstantMovement*>(thing) != nullptr)
			{
				if(collisionState == CollisionState::NoCollision)
				{
					collisionState = CollisionState::StartedCollision;
					Game::instance->currentLives--;
				}
				else if(collisionState == CollisionState::StartedCollision)
					collisionState = CollisionState::Overlapping;
				foundCollision = true;
				break;
			}
		}
	}
	if(!foundCollision)
	{
		if(collisionState == CollisionState::Overlapping)
			collisionState = CollisionState::EndedCollision;
		else if(collisionState == CollisionState::EndedCollision)
			collisionState = CollisionState::NoCollision;
	}
}

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
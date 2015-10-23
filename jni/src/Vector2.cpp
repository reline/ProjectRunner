#include "Vector2.h"

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::~Vector2()
{

}

Vector2 Vector2::operator+(Vector2& rhsVector)
{
	return Vector2(this->x + rhsVector.x, this->y + rhsVector.y);
}

void Vector2::operator+=(Vector2& rhsVector)
{
	this->y += rhsVector.y;
	this->x += rhsVector.x;
}
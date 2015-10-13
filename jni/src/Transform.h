#pragma once
#include "Vector2.h"

class Transform
{
public:
	Vector2 position;

	Transform(Vector2 startPos = Vector2());
	~Transform();
};
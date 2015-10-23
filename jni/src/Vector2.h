#pragma once

class Vector2
{
public:
	float x, y;
	Vector2(float x = 0, float y = 0);
	Vector2 operator+(Vector2& rhsVector);
	void operator+=(Vector2& rhsVector);
	~Vector2();
};
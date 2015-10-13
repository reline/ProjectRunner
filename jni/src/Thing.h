#pragma once

#include "Transform.h"
#include "LTexture.h"
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

class Thing
{
public:

	static vector<Thing*> things; // TODO: figure out the optimal init capacity

	Transform transform;
	LTexture image;

	Thing(Transform transform = Transform(), string path = "");
	~Thing();

	void Render();
	
};
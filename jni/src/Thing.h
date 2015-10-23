#pragma once

#include "LTexture.h"
#include "Transform.h"
#include "PackedDynamicArray.h"
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;

class Thing
{
public:

	static PackedDynamicArray<Thing*> things; // TODO: figure out the optimal init capacity

	Transform transform;
	LTexture image;

	Thing(Transform transform = Transform(), string path = "");
	// Thing(const Thing& thing);
	~Thing();

	void Render();
	void Destroy();
	virtual void Tick();
	
};
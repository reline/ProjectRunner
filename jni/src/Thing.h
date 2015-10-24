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
private:
		unsigned int thingIndex;
		int priority;
public:

	static std::map<int, PackedDynamicArray<Thing*>> things;

	Transform transform;
	LTexture image;

	Thing(Transform transform = Transform(), string path = "", int priority = 100);
	~Thing();

	void Render();
	
};
#include "Thing.h"

std::map<int, PackedDynamicArray<Thing*>> Thing::things;

Thing::Thing(Transform transform, string path, int priority)
{
	this->transform = transform;
	image = LTexture(priority);
	if(path != "")
	{
		if(!image.loadFromFile(path))
			SDL_Log("Image failed to load.");
	}
	this->priority = priority;
	thingIndex = things[priority].Add(this);
	widthHeightOverride = NULL;
}

Thing::~Thing()
{ 
	// Deallocate other things
	image.free();
	things[priority].RemoveAt(thingIndex);
}

Thing* Thing::Spawn(Transform transform, string path, int priority)
{
	Thing* newThing = new Thing(transform, path, priority);
	return newThing;
}

void Thing::Destroy()
{
	delete this;
}

void Thing::Render()
{
	rect = image.render(transform.position.x, transform.position.y, widthHeightOverride);
}

void Thing::Tick()
{
}

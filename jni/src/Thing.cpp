#include "Thing.h"

vector<Thing*> Thing::things;

Thing::Thing(Transform transform, string path)
{
	this->transform = transform;
	if(path != "")
	{
		if(!image.loadFromFile(path))
			SDL_Log("it didn't load");
		else
			SDL_Log("it loaded the file");
	}

	things.push_back(this);
}

Thing::~Thing()
{ 
	// Dealocate other things
	image.free();

	// Remove from list
	vector<Thing*>::iterator iter = std::find(things.begin(), things.end(), this);
	if(iter != things.end())
		things.erase(iter);
	// else something went wrong
}

void Thing::Render()
{
	// image.render((Game::instance->screenRect.w - image.getWidth()) / 2, (Game::instance->screenRect.h - image.getHeight()) / 2);
	image.render(transform.position.x, transform.position.y);
}
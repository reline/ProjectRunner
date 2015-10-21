#include "Thing.h"

PackedDynamicArray<Thing*> Thing::things;

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

	things.Add(this);
}

Thing::~Thing()
{ 
	// Dealocate other things
	image.free();

	// Remove from list
	things.RemoveValue(this);
}

void Thing::Render()
{
	// image.render(transform.position.x, transform.position.y, &Game::instance->camera);
	image.render(transform.position.x, transform.position.y);

	// SDL_Rect renderQuad = { transform.position.x, transform.position.y, image.getWidth(), image.getHeight() };
	// SDL_RenderCopyEx( Game::instance->renderer, image.mTexture, &renderQuad, &Game::instance->camera, 0.0, 0, SDL_FLIP_NONE ); // maybe?
}


	// void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
	// SDL_RenderCopyEx( Game::instance->renderer, mTexture, clip, &renderQuad, angle, center, flip );
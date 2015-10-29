//Using SDL, standard IO, and, strings
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <sstream>

#include "GameManager.h"
#include "Game.h"
#include "LTexture.h"
#include "Transform.h"
#include "Thing.h"
#include "Vector2.h"
#include "ConstantMovement.h"
#include "Spawner.h"

#define SSTR(x) dynamic_cast<std::ostringstream&>((std::ostringstream() << std::dec << x)).str()

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	Game::Init("SDL_Tutorial", SDL_WINDOW_SHOWN);
	GameManager manager;

	//Draw background to the screen
	Thing::Spawn(Transform(Vector2()), "52_hello_mobile/Background.bmp");

	Spawner* s = new Spawner(Transform(Vector2(0,1)));

	//Create and draw the terrain to the screen
	ConstantMovement* leftPath = new ConstantMovement(
		Transform(Vector2()), 
		"52_hello_mobile/hello.bmp", Vector2(0, 1)); // (startLocation, imageFilePath, velocity)

	ConstantMovement* middlePath = new ConstantMovement(
		Transform(Vector2()), 
		"52_hello_mobile/hello.bmp", Vector2(0, 1));

	ConstantMovement* rightPath = new ConstantMovement(
		Transform(Vector2()), 
		"52_hello_mobile/hello.bmp", Vector2(0, 1));

	manager.lanes.push_back(leftPath);
	manager.lanes.push_back(middlePath);
	manager.lanes.push_back(rightPath);

	leftPath->transform.position = Vector2(0, 0);
	middlePath->transform.position = Vector2((Game::instance->screenRect.w - middlePath->image.getWidth()) / 2, 0);
	rightPath->transform.position = Vector2(Game::instance->screenRect.w - rightPath->image.getWidth(), 0);

	// easy access, just how i like it
	int imageWidth = leftPath->image.getWidth();
	int imageHeight = leftPath->image.getHeight();

	// these seem to change within the game loop
	int screenWidth = Game::instance->screenRect.w;
	int screenHeight = Game::instance->screenRect.h;

	// Thing splash(Transform(Vector2()), "52_hello_mobile/hello.bmp");
	// splash.transform.position = Vector2((Game::instance->screenRect.w - splash.image.getWidth()) / 2, 0);

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//While application is running
	while(!quit)
	{
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 )
		{
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}

		// here we reuse our allocated memory for the ConstantMovement objects if they have disappeared from the screen
		if(leftPath->transform.position.y > screenHeight) // temporary kill box type thing
		{
			leftPath->~ConstantMovement();
			leftPath = new (leftPath) ConstantMovement(Transform(Vector2(0, -imageHeight)), "52_hello_mobile/hello.bmp", Vector2(0, 1));
		}
		if(middlePath->transform.position.y > screenHeight)
		{
			middlePath->~ConstantMovement();
			middlePath = new (middlePath) ConstantMovement(Transform(Vector2((screenWidth - imageWidth) / 2, -imageHeight)), "52_hello_mobile/hello.bmp", Vector2(0, 1));
		}
		if(rightPath->transform.position.y > screenHeight)
		{
			rightPath->~ConstantMovement();
			rightPath = new (rightPath) ConstantMovement(Transform(Vector2((screenWidth - imageWidth), -imageHeight)), "52_hello_mobile/hello.bmp", Vector2(0, 1));
		}

		// splash.transform.position.y++; // move the thing down

		//Clear screen
		SDL_SetRenderDrawColor(Game::instance->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(Game::instance->renderer);
		
		Game::Tick();

		//Update screen
		SDL_RenderPresent(Game::instance->renderer);
	}

	// middlePath->Destroy();
	// rightPath->Destroy();

	//Free resources and close SDL
	Game::Exit();

	return 0;
}

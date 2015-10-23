//Using SDL, standard IO, and, strings
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <sstream>

#include "Game.h"
#include "LTexture.h"
#include "Transform.h"
#include "Thing.h"
#include "Vector2.h"
#include "ConstantMovement.h"

#define SSTR(x) dynamic_cast<std::ostringstream&>((std::ostringstream() << std::dec << x)).str()

void close()
{
	Game::Exit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	Game::Init("SDL_Tutorial", SDL_WINDOW_SHOWN);

	//Draw background to the screen
	Thing Background(Transform(Vector2()), "52_hello_mobile/Background.bmp");

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


	leftPath->transform.position = Vector2(0, 0);
	middlePath->transform.position = Vector2((Game::instance->screenRect.w - middlePath->image.getWidth()) / 2, 0);
	rightPath->transform.position = Vector2(Game::instance->screenRect.w - rightPath->image.getWidth(), 0);

	int imageWidth = leftPath.image.getWidth();

	SDL_Log("Game Screen Height: " + SSTR(Game::instance->screenRect.y));
	SDL_Log("Right path initial y: " + SSTR(rightPath->transform.position.y));

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

		// TODO: here we reuse our allocated memory for the ConstantMovement objects if they have disappeared from the screen
		/*if(rightPath->transform.position.y > Game::instance->screenRect.y) { // why is this always true
			leftPath = new (leftPath) ConstantMovement(Transform(Vector2()), "52_hello_mobile/hello.bmp", Vector2(0, 1));
			middlePath = new (middlePath) ConstantMovement(Transform(Vector2((Game::instance->screenRect.w - imageWidth / 2, 0))), "52_hello_mobile/hello.bmp", Vector2(0, 1));
			rightPath = new (rightPath) ConstantMovement(Transform(Vector2((Game::instance->screenRect.w - imageWidth, 0))), "52_hello_mobile/hello.bmp", Vector2(0, 1));
		}*/

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
	close();

	return 0;
}

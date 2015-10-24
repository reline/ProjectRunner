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

#define SSTR(x) dynamic_cast<std::ostringstream&>((std::ostringstream() << std::dec << x)).str()

void close()
{
	Game::Exit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	Game::Init("SDL_Tutorial", SDL_WINDOW_SHOWN);

	Thing Background(Transform(Vector2()), "52_hello_mobile/Background.bmp");

	Thing splash(Transform(Vector2()), "52_hello_mobile/hello.bmp");
	splash.transform.position = Vector2((Game::instance->screenRect.w - splash.image.getWidth()) / 2, 0);

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

		splash.transform.position.y++; // move the thing down

		//Clear screen
		SDL_SetRenderDrawColor(Game::instance->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(Game::instance->renderer);
		
		// Game::Render();

		//Update screen
		SDL_RenderPresent(Game::instance->renderer);
	}

	//Free resources and close SDL
	close();

	return 0;
}

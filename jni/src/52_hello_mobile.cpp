//Using SDL, standard IO, and, strings
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <string.h>

#include "Game.h"
#include "LTexture.h"

//Scene textures
LTexture gSplashTexture;

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

bool loadMedia()
{

	//Load splash texture
	if( !gSplashTexture.loadFromFile( "52_hello_mobile/hello.bmp" ) )
	{
		SDL_Log( "Failed to load splash texture!\n" );
		return false;
	}

	return true;
}

void close()
{
	//Free loaded images
	gSplashTexture.free();
	Game::Exit();
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	Game::Init("SDL_Tutorial", SDL_WINDOW_SHOWN);

	if(1)
	{
		//Load media
		if( !loadMedia() )
		{
			SDL_Log( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//While application is running
			while( !quit )
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

				//Clear screen
				SDL_SetRenderDrawColor( Game::instance->renderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( Game::instance->renderer );

				//Render splash
				gSplashTexture.render( ( Game::instance->screenRect.w - gSplashTexture.getWidth() ) / 2, ( Game::instance->screenRect.h - gSplashTexture.getHeight() ) / 2 );

				//Update screen
				SDL_RenderPresent( Game::instance->renderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

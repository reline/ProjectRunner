/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, standard IO, and, strings
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <string.h>

#include "Game.h"
#include "LTexture.h"

// extern SDL_Rect Game::instance.screenRect;
// extern SDL_Window* gWindow;
// extern SDL_Renderer* Game::instance.renderer;

//Scene textures
LTexture gSplashTexture;

//Starts up SDL and creates window
// bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

// bool init()
// {
// 	//Initialization flag
// 	bool success = true;

// 	//Initialize SDL
// 	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
// 	{
// 		SDL_Log( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
// 		success = false;
// 	}
// 	else
// 	{
// 		//Set texture filtering to linear
// 		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
// 		{
// 			SDL_Log( "Warning: Linear texture filtering not enabled!" );
// 		}

//         //Get device display mode
//         SDL_DisplayMode displayMode;
//         if( SDL_GetCurrentDisplayMode( 0, &displayMode ) == 0 )
//         {
//             Game::instance.screenRect.w = displayMode.w;
//             Game::instance.screenRect.h = displayMode.h;
//         }

// 		//Create window
// 		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Game::instance.screenRect.w, Game::instance.screenRect.h, SDL_WINDOW_SHOWN );
// 		if( gWindow == NULL )
// 		{
// 			SDL_Log( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
// 			success = false;
// 		}
// 		else
// 		{
// 			//Create renderer for window
// 			Game::instance.renderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
// 			if( Game::instance.renderer == NULL )
// 			{
// 				SDL_Log( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
// 				success = false;
// 			}
// 			else
// 			{
// 				//Initialize renderer color
// 				SDL_SetRenderDrawColor( Game::instance.renderer, 0xFF, 0xFF, 0xFF, 0xFF );
// 			}
// 		}
// 	}

// 	return success;
// }

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
	// //Destroy window
	// SDL_DestroyRenderer( Game::instance.renderer );
	// SDL_DestroyWindow( gWindow );
	// gWindow = NULL;
	// Game::instance.renderer = NULL;

	// //Quit SDL subsystems
	// SDL_Quit();
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

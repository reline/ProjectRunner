//Using SDL, standard IO, and, strings
#include <SDL.h>
#include </home/baladash/Android_Development/SDL2-2.0.3/android-project/jni/SDL2_ttf-2.0.12/SDL_ttf.h>
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
#include "Player.h"
#include "Spawner.h"

// extern TTF_Font* TTF_OpenFont(const char *file, int ptsize);

#define SSTR(x) dynamic_cast<std::ostringstream&>((std::ostringstream() << std::dec << x)).str()

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	Game::Init("SDL_Tutorial", SDL_WINDOW_SHOWN);
	TTF_Init();
	GameManager manager;

	// these seem to change within the game loop
	int screenWidth = Game::instance->screenRect.w;
	int screenHeight = Game::instance->screenRect.h;

	//Draw background to the screen
	Thing::Spawn(Transform(Vector2()), "52_hello_mobile/PathWay.bmp");

	Spawner* s = new Spawner(Transform(Vector2(0,1)));

	// Font Stuff
	TTF_Font* Sans = TTF_OpenFont("52_hello_mobile/DroidSans.ttf", 24);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = 0;  //controls the rect's x coordinate 
	Message_rect.y = 0; // controls the rect's y coordinte
	Message_rect.w = 300; // controls the width of the rect
	Message_rect.h = 100; // controls the height of the rect

	// our player!
	Player* player = new Player(
		Transform(Vector2()),
		"52_hello_mobile/Player.bmp", 100, CENTER); // rendered last (100)

	float middleLaneXCoord = (screenWidth - player->image.getWidth()) / 2;
	float leftLaneXCoord = middleLaneXCoord - (screenWidth / 3);
	float rightLaneXCoord = middleLaneXCoord + (screenWidth / 3);

	manager.lanes.push_back(Vector2(leftLaneXCoord, 0));
	manager.lanes.push_back(Vector2(leftLaneXCoord, 0));
	manager.lanes.push_back(Vector2(rightLaneXCoord, 0));

	player->transform.position = Vector2(middleLaneXCoord, screenHeight - (player->image.getWidth() * 2));

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//Touch variables
	SDL_Point touchLocation = {screenWidth / 2, screenHeight / 2};

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
			//Touch down
			else if(e.type == SDL_FINGERDOWN)
			{
				touchLocation.x = e.tfinger.x * screenWidth;
				touchLocation.y = e.tfinger.y * screenHeight;
				// move our player towards the clicked lane
				if(touchLocation.x < player->transform.position.x)
				{
					player->moveLeft(screenWidth/3);
				}
				else if(touchLocation.x > player->transform.position.x + player->image.getWidth())
				{
					player->moveRight(screenWidth/3);
				}
			}
			//Touch motion
			else if(e.type == SDL_FINGERMOTION)
			{
				touchLocation.x = e.tfinger.x * screenWidth;
				touchLocation.y = e.tfinger.y * screenHeight;
				// todo: turn our player to the gestured direction
			}
			//Touch release
			else if(e.type == SDL_FINGERUP)
			{
				touchLocation.x = e.tfinger.x * screenWidth;
				touchLocation.y = e.tfinger.y * screenHeight;
			}
		}

		//Clear screen
		SDL_SetRenderDrawColor(Game::instance->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(Game::instance->renderer);
		
		Game::Tick();
		player->Render();


		SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, ("Score: " + SSTR(Game::instance->score)).c_str(), {255, 255, 255});
		SDL_Texture* Message = SDL_CreateTextureFromSurface(Game::instance->renderer, surfaceMessage);
		SDL_RenderCopy(Game::instance->renderer, Message, NULL, &Message_rect);

		//Update screen
		SDL_RenderPresent(Game::instance->renderer);
	}

	// middlePath->Destroy();
	// rightPath->Destroy();

	//Free resources and close SDL
	Game::Exit();

	return 0;
}

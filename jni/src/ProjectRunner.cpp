#pragma once

#include <jni.h>

//Using SDL, standard IO, and, strings
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
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

void reset();

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	Game::Init("SDL_Tutorial", SDL_WINDOW_SHOWN);
	TTF_Init();
	GameManager manager;

	// these seem to change within the game loop
	int screenWidth = Game::instance->screenRect.w;
	int screenHeight = Game::instance->screenRect.h;

	manager.hurtSound = Mix_LoadWAV("raw/hurt.wav");
	if(manager.hurtSound == nullptr)
		SDL_Log("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());

	//Draw background to the screen
	// Thing* background = Thing::Spawn(Transform(Vector2()), "drawable/PathWay.bmp");
	// SDL_Rect backgroundRect = { 0, 0, Game::instance->screenRect.w, Game::instance->screenRect.h };
	// background->widthHeightOverride = &backgroundRect;

	Spawner* s = new Spawner(Transform(Vector2(0,1)));

	// Font Stuff
	TTF_Font* Sans = TTF_OpenFont("drawable/DroidSans.ttf", 24);

	SDL_Rect scoreRect; //create a rect
	scoreRect.x = 0;  //controls the rect's x coordinate 
	scoreRect.y = 0; // controls the rect's y coordinte
	scoreRect.w = screenWidth / 5; // controls the width of the rect
	scoreRect.h = screenHeight / 30; // controls the height of the rect

	SDL_Rect lifeRect; //create a rect
	lifeRect.x = screenWidth - (screenWidth / 7);  //controls the rect's x coordinate 
	lifeRect.y = 0; // controls the rect's y coordinte
	lifeRect.w = screenWidth / 7; // controls the width of the rect
	lifeRect.h = screenHeight / 30; // controls the height of the rect

	SDL_Rect gameOverRect; //create a rect
	gameOverRect.w = screenWidth / 5; // controls the width of the rect
	gameOverRect.h = screenHeight / 30; // controls the height of the rect
	gameOverRect.x = screenWidth / 2 - gameOverRect.w / 2;  //controls the rect's x coordinate 
	gameOverRect.y = screenHeight / 2 - gameOverRect.h / 2; // controls the rect's y coordinte

	// our player!
	Player* player = new Player(
		Transform(Vector2()),
		"drawable/Player.bmp", 200, CENTER); // rendered last (100)

	// x coordinates for the center of each lane
	float middleLaneXCoord = screenWidth / 2;
	float leftLaneXCoord = screenWidth - (screenWidth * 5/6);
	float rightLaneXCoord = screenWidth - (screenWidth / 6);

	manager.lanes.push_back(Vector2(leftLaneXCoord, 0));
	manager.lanes.push_back(Vector2(middleLaneXCoord, 0));
	manager.lanes.push_back(Vector2(rightLaneXCoord, 0));

	player->transform.position = Vector2(middleLaneXCoord - (player->image.getWidth() / 2), screenHeight - (player->image.getWidth() * 2));

	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//Touch variables
	SDL_Point touchLocation = {screenWidth / 2, screenHeight / 2};

	SDL_Surface* scoreSurface = nullptr;
	SDL_Surface* playerLifeSurface = nullptr;
	SDL_Surface* gameOverSurface = nullptr;
	SDL_Texture* scoreTexture = nullptr;
	SDL_Texture* playerLifeTexture = nullptr;
	SDL_Texture* gameOverTexture = nullptr;


	/** APPLICATION LOOP **/
	while(!quit)
	{
        SDL_Log("DEBUGGING - Game is running", "GameActivity");

		//Clear screen for main menu Screen
		SDL_SetRenderDrawColor(Game::instance->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(Game::instance->renderer);

		gameOverSurface = TTF_RenderText_Solid(Sans, "Click to play!", {0, 0, 0});
		gameOverTexture = SDL_CreateTextureFromSurface(Game::instance->renderer, gameOverSurface);
		SDL_RenderCopy(Game::instance->renderer, gameOverTexture, NULL, &gameOverRect);

		//Update screen
		SDL_RenderPresent(Game::instance->renderer);

		/** MAIN MENU LOOP **/
		while(Game::instance->gameState == isMainMenu)
		{
			while(SDL_PollEvent(&e) != 0)
			{
				// todo: draw our 'play' button
				//User requests quit
				if( e.type == SDL_QUIT)
				{
					quit = true;
					break;
				}
				//Touch down
				else if(e.type == SDL_FINGERDOWN)
				{
					// todo: if button clicked...
					Game::instance->gameState = isGamePlay;
					touchLocation.x = e.tfinger.x * screenWidth;
					touchLocation.y = e.tfinger.y * screenHeight;					
				}
				//Touch motion
				else if(e.type == SDL_FINGERMOTION)
				{
					touchLocation.x = e.tfinger.x * screenWidth;
					touchLocation.y = e.tfinger.y * screenHeight;
				}
				//Touch release
				else if(e.type == SDL_FINGERUP)
				{
					touchLocation.x = e.tfinger.x * screenWidth;
					touchLocation.y = e.tfinger.y * screenHeight;
				}
			}
		}

		/** GAME LOOP **/
		while(Game::instance->gameState == isGamePlay)
		{
			if(Game::instance->currentLives == 0)
			{
				Game::instance->gameState = isGameOver;
				break;
			}
			//Handle events on queue
			while( SDL_PollEvent( &e ) != 0 )
			{
				//User requests quit
				if( e.type == SDL_QUIT)
				{
					quit = true;
					break;
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
			SDL_SetRenderDrawColor(Game::instance->renderer, 0x00, 0x00, 0x00, 0x00);
			SDL_RenderClear(Game::instance->renderer);

			// breakin stuff, oh yeah
			/*SDL_Rect fillRect = { (screenWidth / 3) - (screenWidth / 20), 0, screenWidth / 20, screenHeight };
	        SDL_SetRenderDrawColor( Game::instance->renderer, 0xFF, 0x0FF, 0x0FF, 0xFF );        
	        SDL_RenderFillRect( Game::instance->renderer, &fillRect );

	        fillRect = { (screenWidth / 3) * 2, 0, screenWidth / 20, screenHeight };
	        SDL_SetRenderDrawColor( Game::instance->renderer, 0xFF, 0x0FF, 0x0FF, 0xFF );        
	        SDL_RenderFillRect( Game::instance->renderer, &fillRect );*/

			Game::Tick();
			// player->Render();

			if(scoreSurface != nullptr)
				// delete scoreSurface;
				SDL_FreeSurface(scoreSurface);
			if(playerLifeSurface != nullptr)
				// delete playerLifeSurface;
				SDL_FreeSurface(playerLifeSurface);
			if(scoreTexture != nullptr)
				// delete scoreTexture;
				SDL_DestroyTexture(scoreTexture);
			if(playerLifeTexture != nullptr)
				// delete playerLifeTexture;
				SDL_DestroyTexture(playerLifeTexture);

			scoreSurface = TTF_RenderText_Solid(Sans, ("Score: " + SSTR(Game::instance->score)).c_str(), {255, 255, 255});
			playerLifeSurface = TTF_RenderText_Solid(Sans, ("Life: " + SSTR(Game::instance->currentLives)).c_str(), {255, 225, 255});
			scoreTexture = SDL_CreateTextureFromSurface(Game::instance->renderer, scoreSurface);
			playerLifeTexture = SDL_CreateTextureFromSurface(Game::instance->renderer, playerLifeSurface);
			SDL_RenderCopy(Game::instance->renderer, scoreTexture, NULL, &scoreRect);
			SDL_RenderCopy(Game::instance->renderer, playerLifeTexture, NULL, &lifeRect);

			//Update screen
			SDL_RenderPresent(Game::instance->renderer);
		}
		//Clear screen for GameOver Screen
		SDL_SetRenderDrawColor(Game::instance->renderer, 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(Game::instance->renderer);

		gameOverSurface = TTF_RenderText_Solid(Sans, ("Score: " + SSTR(Game::instance->score)).c_str(), {255, 255, 255});
		gameOverTexture = SDL_CreateTextureFromSurface(Game::instance->renderer, gameOverSurface);
		SDL_RenderCopy(Game::instance->renderer, gameOverTexture, NULL, &gameOverRect);

		//Update screen
		SDL_RenderPresent(Game::instance->renderer);	
		
		Mix_FreeChunk(manager.hurtSound);

		//Free resources
		Game::Exit();

		reset();

		/** GAMEOVER LOOP **/
		while(Game::instance->gameState == isGameOver)
		{
			while(SDL_PollEvent(&e) != 0)
			{
				if(e.type == SDL_FINGERDOWN)
				{
					Game::instance->gameState = isMainMenu;				
				}
			}

		}
		// clear screen
		SDL_SetRenderDrawColor(Game::instance->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(Game::instance->renderer);
		// update screen
		SDL_RenderPresent(Game::instance->renderer);	
	}
	return 0;
}

void reset()
{
	// reset player's health, ticks, score
	Game::instance->currentLives = 3;
	Game::instance->frames = 0;
	Game::instance->score = 0;

	// reset the player
	//delete Player::instance;
	Player::instance = new Player(
		Transform(Vector2()),
		"drawable/Player.bmp", 200, CENTER); // rendered last (100)
	Player::instance->transform.position = Vector2(Game::instance->screenRect.w / 2 - (Player::instance->image.getWidth() / 2), 
													Game::instance->screenRect.h - (Player::instance->image.getWidth() * 2));
	// reset the spawner
	//delete Spawner::instance;
	Spawner::instance = new Spawner(Transform(Vector2(0,1)));

	// reset the sound for the manager
	GameManager::instance->hurtSound = Mix_LoadWAV("raw/hurt.wav");

	/*// clear screen
	SDL_SetRenderDrawColor(Game::instance->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(Game::instance->renderer);
	// update screen
	SDL_RenderPresent(Game::instance->renderer);*/
}

#ifdef __cplusplus
extern "C" {
#endif
    JNIEXPORT jboolean JNICALL Java_com_raisingthebar_projectr_GameActivity_isGameFinished(JNIEnv* env, /*jclass cls,*/ jobject obj)
    {
        if (Game::instance != nullptr) {
            return Game::instance->gameState == isGameOver;
        } else {
            return false;
        }
    }
#ifdef __cplusplus
}
#endif
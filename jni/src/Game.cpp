#include "Game.h"

Game* Game::instance = nullptr;

Game::Game(char* name, Uint32 flags)
{
	if(instance != nullptr)
	{
		printf("Two games at once? Are you crazy?\n");
		exit(EXIT_FAILURE);
	}
	
	// Init video
	SDL_NullCheckPred([&](void){return SDL_Init(SDL_INIT_VIDEO) < 0;}, "SDL_Init failed.");

	//Set texture filtering to linear
	if(!SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ))
		SDL_Log( "Warning: Linear texture filtering not enabled!" );

	//Get device display mode
    SDL_DisplayMode displayMode;
    if(SDL_GetCurrentDisplayMode(0, &displayMode) == 0)
    {
        screenRect.w = displayMode.w;
        screenRect.h = displayMode.h;
    }

	// init window
	window = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenRect.w, screenRect.h, flags);
	SDL_NullCheck(window, "Window could not be created.");

	// Create renderer for window
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	SDL_NullCheck(renderer, "Renderer could not be created!");

	// init color
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	// set instance
	instance = this;
}

Game::~Game()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	printf("Game over man! Game over!\n");
	exit(0);
}

void Game::Init(char* name, Uint32 flags)
{
	instance = new Game(name, flags);
}

void Game::Exit()
{
	delete instance;
}
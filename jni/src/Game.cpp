#include "Game.h"
#include "Thing.h"

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
		SDL_Log("Warning: Linear texture filtering not enabled!");

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

	// camera = { screenRect.w / 3, screenRect.h / 3, (screenRect.w / 3) + screenRect.w, (screenRect.h / 3) + screenRect.h };
	camera = { 0, 0, screenRect.w, screenRect.h };

	// set instance
	instance = this;

	score = 0;
	currentSecond = 0;
	currentLives = 3;

	gameState = GameState::isMainMenu;
}

Game::~Game()
{
	for(auto &it : Thing::things)
	{
		// Iterate textures
		for(Thing* thing : it.second)
		{
			if(thing != nullptr)
				thing->Destroy();
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	printf("Game over man! Game over!\n");
	exit(0);
}

void Game::Render()
{
	std::vector<Thing*> theDoomedOnes;
	// Iterate texture lists in order of priority
	for(auto &it : Thing::things)
	{
		// Iterate textures
		for(Thing* thing : it.second)
		{
			if(thing == nullptr)
				continue;
			thing->Tick();
			// Render texture
			thing->Render();
			if(thing->transform.position.y > Game::instance->screenRect.h)
				theDoomedOnes.push_back(thing);
		}
	}
	uint numberOfDoomedThings = theDoomedOnes.size();
	for(uint i = 0; i < numberOfDoomedThings; i++)
	{
		if(theDoomedOnes[i] != nullptr)
		{
			theDoomedOnes[i]->Destroy();
			//SDL_Log("killed one");
		}
	}
	// for(auto &it : Thing::things)
	// {
	// 	SDL_Log("displaying");
	// 	it.second.Display();
	// }
}

void Game::Tick()
{
	instance->frames++;
	instance->currentSecond++;
	if (instance->currentSecond == 60)
	{
		instance->score++;
		instance->currentSecond = 0;
	}
	//SDL_Log(SSTR(instance->score).c_str());
	Render();
}

void Game::Init(char* name, Uint32 flags)
{
	instance = new Game(name, flags);
}

void Game::Exit()
{
	delete instance;
}
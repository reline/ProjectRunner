#pragma once

#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <cstdlib>

enum GameState
{
	isMainMenu,
	isGamePlay,
	isPaused,
	isGameOver,
};

class Game
{
private:
	
	Game(char* name, Uint32 flags);
	~Game();
	int currentSecond;

public:
	static Game* instance;
	SDL_Rect screenRect;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect camera;
	unsigned long long frames;
	int score;
	int currentLives;
	GameState gameState;

	static void Init(char* name, Uint32 flags);
	static void Render();
	static void Tick();
	static void Exit();
};

template<class UnaryPredicate>
void SDL_NullCheckPred(UnaryPredicate pred, char* msg)
{
	if(pred())
	{
		SDL_Log("%s SDL_Error: %s\n", msg, SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

template<class T>
void SDL_NullCheck(T obj, char* msg)
{
	if(obj == NULL || obj == nullptr)
	{
		SDL_Log("%s SDL_Error: %s\n", msg, SDL_GetError());
		exit(EXIT_FAILURE);
	}
}
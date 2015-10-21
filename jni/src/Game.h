#pragma once

#include <SDL.h>
#include <stdio.h>
#include <cstdlib>

class Game
{
private:
	Game(char* name, Uint32 flags);
	~Game();

public:
	static Game* instance;
	SDL_Rect screenRect;
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Rect camera;

	static void Init(char* name, Uint32 flags);
	static void Render();
	static void Exit();
};

template<class UnaryPredicate>
void SDL_NullCheckPred(UnaryPredicate pred, char* msg)
{
	if(pred())
	{
		printf("%s SDL_Error: %s\n", msg, SDL_GetError());
		exit(EXIT_FAILURE);
	}
}

template<class T>
void SDL_NullCheck(T obj, char* msg)
{
	if(obj == NULL)
	{
		printf("%s SDL_Error: %s\n", msg, SDL_GetError());
		exit(EXIT_FAILURE);
	}
}
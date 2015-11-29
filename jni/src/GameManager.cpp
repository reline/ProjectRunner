#include "GameManager.h"

GameManager* GameManager::instance = nullptr;
Mix_Chunk* GameManager::hurtSound = nullptr;

GameManager::GameManager()
{
	if(instance)
		return;
	instance = this;
}
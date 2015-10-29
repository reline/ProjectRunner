#include "GameManager.h"

GameManager* GameManager::instance = nullptr;

GameManager::GameManager()
{
	if(instance)
		return;
	instance = this;
}
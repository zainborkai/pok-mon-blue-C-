// SDLFramework.cpp : Defines the entry point for the console application.
//

#include "GameManager.h"

int main(int argc, char* argv[])
{
	GameManager* game = GameManager::Instance();
	game->Run();
	GameManager::Release();
	game = nullptr;

    return 0;
}


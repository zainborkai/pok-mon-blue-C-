#ifndef GAMESYSTEM_H
#define GAMESYSTEM_H

#include "Database.h"
#include "InputManager.h"


class GameSystem {
public:
	static SDL_Scancode KEY_AFFIRM;
	static SDL_Scancode KEY_CANCEL;
	const static int MAXBENCHCOUNT = 6;
public:
	class GameData {
	public:
		int money;
		std::vector<Pokemon*> bench;
		std::vector<InventoryItem*> playerInventory;
	public:
		GameData() {
			money = 1000;
		}
	};
	GameData* data;

	
	std::vector<InventoryItem*> GetInventory() {
		return data->playerInventory;
	}

public:
	static GameSystem* Instance() {
		if (sInstance == nullptr) { sInstance = new GameSystem(); }
		return sInstance;
	}
private:
	GameSystem();
	static GameSystem* sInstance;
};

#endif

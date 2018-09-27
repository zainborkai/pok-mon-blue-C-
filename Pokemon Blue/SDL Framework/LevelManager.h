#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <vector>
#include "Buildings.h"
#include "GroundMap.h"
#include "Player.h"

class LevelManager {
public:
	LevelManager();
	~LevelManager();

	InputManager* inputManager;
	void ChangeMap();

	static LevelManager* Instance();
	static void Release();
	//
	void Render();
	//void EarlyUpdate();
	void Update();

private:
	static LevelManager* sInstance;

	Buildings* buildings;

	Map* mMap;
	GroundMap* mGroundMap;
	Player* mPlayer;
	Graphics* mGraphics;
};



#endif
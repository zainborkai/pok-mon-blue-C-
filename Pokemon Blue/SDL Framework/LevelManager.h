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

	void ChangeMap();

	static LevelManager* Instance();
	static void Release();
	//
	void Render();
	//void EarlyUpdate();
	void Update();

private:
	static LevelManager* sInstance;

	std::vector<Texture*> mapList;

	Buildings* buildings;

	Map* mMap;
	GroundMap* mGroundMap;
	Player* mPlayer;
	Graphics* mGraphics;
};



#endif
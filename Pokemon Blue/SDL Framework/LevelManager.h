#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include <vector>
#include "Buildings.h"
#include "GroundMap.h"
#include "Player.h"
#include "GroundGrass.h"
#include "BattleScreen.h"

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
	GroundGrass* mGroundGrass;
	BattleScreen* mBattleScreen;
	Player* mPlayer;
	Graphics* mGraphics;
	int mStatus = 1;	//1:Ground	//2:house	//3:battle	//4:talk 

	//Setters
	void SetStatus(int status) {
		mStatus = status;
	};
	//Getters
	int GetStatus() {
		return mStatus;
	}


};



#endif
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "InputManager.h"
#include "AudioManager.h"
#include "Timer.h"
#include "Texture.h"
#include "Map.h"
#include "Player.h"


class GameManager {
private:
	static GameManager* sInstance;

	const int FRAME_RATE = 120;

	bool mQuit;

	Graphics* mGraphics;
	AssetManager* mAssetMgr;
	InputManager* mInputMgr;
	AudioManager* mAudioMgr;

	Timer* mTimer;
	Map* mMap;
	Player* mPlayer;

	SDL_Event mEvents;

public:
	static GameManager* Instance();
	static void Release();
	void Run();

private:
	GameManager();
	~GameManager();
	void EarlyUpdate();
	void Update();
	void LateUpdate();
	void Render();
};


#endif 
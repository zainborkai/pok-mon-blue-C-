#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "InputManager.h"
#include "AudioManager.h"
#include "Timer.h"
#include "Actor.h"
#include <vector>


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
	std::vector<Actor*> actorList;

	SDL_Event mEvents;

public:
	static GameManager* Instance();
	static void Release();
	void Run();

	// Actor* CreateActor();
	bool RegisterActor(Actor* act);
	bool UnregisterActor(Actor* act);
	std::vector<Actor*> _destroyList;
	void _QueueDestroy(Actor* act);
	void _ProcessDestroys();

	inline int GetFrameRate() { return FRAME_RATE; };

private:
	GameManager();
	~GameManager();
	void EarlyUpdate();
	void Update();
	void LateUpdate();
	void Render();
};


#endif

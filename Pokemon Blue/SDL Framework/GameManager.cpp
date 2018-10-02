
#include "GameManager.h"
#include "BattleManager.h"

GameManager* GameManager::sInstance = nullptr;


GameManager* GameManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new GameManager();
	}

	return sInstance;
}


void GameManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}


GameManager::GameManager() {
	mQuit = false;
	mGraphics = Graphics::Instance();

	if (!Graphics::Initialized()) {
		mQuit = true;
	}

	mAssetMgr = AssetManager::Instance();
	mInputMgr = InputManager::Instance();
	mAudioMgr = AudioManager::Instance();
	mTimer = Timer::Instance();
	mText = Text::Instance();
	mText->displayTextBox("INTRO");
	mNPC = new NPC;
	mOak = new Oak;
	mRival = new Rival;
	mMom = new Mom;
	mBrock = new Brock;
	mTrainer = new Trainer;
}

GameManager::~GameManager() {
	AudioManager::Release();
	mAudioMgr = nullptr;
	AssetManager::Release();
	mAssetMgr = nullptr;
	Graphics::Release();
	mGraphics = nullptr;
	InputManager::Release();
	mInputMgr = nullptr;
	Timer::Release();
	mTimer = nullptr;

	Text::Release();
	mText = nullptr;

	delete mNPC;
	mNPC = nullptr;

	delete mOak;
	mOak = nullptr;

	delete mRival;
	mRival = nullptr;

	delete mMom;
	mMom = nullptr;

	delete mBrock;
	mBrock = nullptr;

	delete mTrainer;
	mTrainer = nullptr;

}
//All the updates and the render happen every frame
void GameManager::EarlyUpdate() {
	//Update the input state before any other updates are run
	//mText->displayTextBox("INTRO");
	mText->NextText();
	for (auto actor : actorList) {
		delete actor;
	}
	actorList.clear();
}

void GameManager::Update() {
	//GameEntity updates should happen here
	
	std::vector<Actor*> copyList(actorList);
	//
	for (int i = 0; i < copyList.size(); i++) {
		auto actor = copyList[i];
		//
		actor->Update();
	}
	//
	_ProcessDestroys();
}
void GameManager::LateUpdate() {
	//Any collision detection should happen here

	mInputMgr->UpdatePrevInput();
	mTimer->Reset();
}


void GameManager::Render() {
<<<<<<< HEAD
	//Clears the last frame's render from the back buffer
	mGraphics->ClearBackBuffer();

	//All other rendering is to happen here
	mText->Render();

	mNPC->Render();
	mOak->Render();
	mRival->Render();
	mMom->Render();
	mBrock->Render();
	mTrainer->Render();
	//
	std::vector<Actor*> copyList(actorList);
	//
	for (int i = 0; i < copyList.size(); i++) {
		auto actor = copyList[i];
		//
		actor->Render();
	}
	//
	_ProcessDestroys();
	//
	mGraphics->Render();
}

void GameManager::Run() {

	// BattleManager::Instance(); // To activate everything.

	while (!mQuit) {
		mTimer->Update();

		while (SDL_PollEvent(&mEvents) != 0) {
			if (mEvents.type == SDL_QUIT) {
				mQuit = true;
			}
		}

		//Limits the frame rate to FRAME_RATE
		if (mTimer->DeltaTime() >= (1.0 / FRAME_RATE)) {
			EarlyUpdate();
			//
			Update();
			//
			LateUpdate();
			//
			Render();
		}
	}
}


/*
Actor* GameManager::CreateActor() {
	Actor* temp = new Actor();
	//
	RegisterActor(temp);
	//
	return temp;
}
*/
bool GameManager::RegisterActor(Actor* act) {
	// act._gm = this;
	
	actorList.push_back(act);
	return true;
}
bool GameManager::UnregisterActor(Actor* act) {
	for (int i = 0; actorList.size(); i++) {
		if (actorList[i] == act) {
			actorList.erase(actorList.begin() + i);
			return true;
		}
	}

	return false;
}

void GameManager::_QueueDestroy(Actor* act) {
	_destroyList.push_back(act);
}
void GameManager::_ProcessDestroys() {
	for (int i = 0; i < _destroyList.size(); i++) {
		Actor* actor = _destroyList[i];
		//
		UnregisterActor(actor);
		delete actor;
	}
	//
	_destroyList.clear();
}

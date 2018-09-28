#include "GameManager.h"

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
	mMap = new Map();
	mPlayer = new Player();
	mItem = new Item();


	Vector2 offset(mGraphics->SCREEN_WIDTH / 2, mGraphics->SCREEN_HEIGHT / 2);
	// mMap->Translate(offset);
	mPlayer->Translate(offset);


	mMap->Scale(Vector2(4, 4));
	mPlayer->Scale(Vector2(4, 4));

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
	delete mMap;
	mMap = nullptr;
	delete mPlayer;
	mPlayer = nullptr;
	delete mItem;
	mItem = nullptr;
}

void GameManager::EarlyUpdate() {
	// Updating the input state before any other updates are run
	
mPlayer->Move();
	


	Vector2 offset = mPlayer->Pos();
	Vector2 scl = mPlayer->Scale();
	mMap->Pos(Vector2(offset.x - mPlayer->GetX() * 16 * scl.x, offset.y - mPlayer->GetY() * 16 * scl.y));
}

void GameManager::Update() {
	// GameEntity updates should happen here
	mMap->Update();
	mPlayer->Update();
}

void GameManager::LateUpdate() {
	// Any collision detection should happen here

	mInputMgr->UpdatePrevInput();
	mTimer->Reset();
}

void GameManager::Render() {
	// Clears the last frame's render from the back buffer 
	mGraphics->ClearBackBuffer();

	// All other rendering is to happen here

	// mPlayer->Render();
	mMap->Render();
	mPlayer->Render();
	// Renders the current frame
	mGraphics->Render();
}

void GameManager::Run() {
	while (!mQuit) {
		mTimer->Update();

		while (SDL_PollEvent(&mEvents) != 0) {
			if (mEvents.type == SDL_QUIT) {
				mQuit = true;
			}
		}

		// Limits the frame rate to FRAME_RATE
		if (mTimer->DeltaTime() >= (1.0 / FRAME_RATE)) {
			EarlyUpdate();
			Update();
			LateUpdate();
			Render();
		}
	}
}

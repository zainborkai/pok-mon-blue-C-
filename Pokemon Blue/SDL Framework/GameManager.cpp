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
	mPalletTown = new PalletTown();
	mPlayer = new Player();
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
	delete mPalletTown;
	mPalletTown = nullptr;
	delete mPlayer;
	mPlayer = nullptr;
}

void GameManager::EarlyUpdate() {
	// Updating the input state before any other updates are run
	mPlayer->Move();

}

void GameManager::Update() {
	// GameEntity updates should happen here
	mPalletTown->Update();
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
	mPalletTown->Render();
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
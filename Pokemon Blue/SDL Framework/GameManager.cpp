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
}

void GameManager::EarlyUpdate() {
	// Updating the input state before any other updates are run

	//--Changes Map Position--//
	int input = mPlayer->Move();
	//
	//
	if (input == 1) {
		mPlayer->Y -= 1;
	}
	else if (input == 2) {
		mPlayer->Y += 1;
	}
	else if (input == 3) {
		mPlayer->X -= 1;
	}
	else if (input == 4) {
		mPlayer->X += 1;
	}
	//
	if (mPlayer->X <= 0) {
		mPlayer->X = 0;
	}
	else if (mPlayer->X > 88 - 1) { // ??? <-- NO MAGIC NUMBERS!
		mPlayer->X = 88 - 1;
	}

	if (mPlayer->Y <= 0) {
		mPlayer->Y = 0;
	}
	else if (mPlayer->Y > 198 - 1) { // ??? <-- NO MAGIC NUMBERS!
		mPlayer->Y = 198 - 1;
	}

	Vector2 offset = mPlayer->Pos();
	Vector2 scl = mPlayer->Scale();
	mMap->Pos(Vector2(offset.x -mPlayer->X * 16* scl.x, offset.y -mPlayer->Y * 16* scl.y));
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
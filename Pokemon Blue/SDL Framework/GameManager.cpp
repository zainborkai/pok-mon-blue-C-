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
}

void GameManager::Update() {
	//GameEntity updates should happen here

}

void GameManager::LateUpdate() {
	//Any collision detection should happen here

	mInputMgr->UpdatePrevInput();
	mTimer->Reset();
}

void GameManager::Render() {
	//Clears the last frame's render from the back buffer
	mGraphics->ClearBackBuffer();

	//All other rendering is to happen here
	mText->Render();

	// Random characters

	/*mNPC->Render();
	mOak->Render();
	mRival->Render();
	mMom->Render();
	mBrock->Render();
	mTrainer->Render();*/

	//Renders the current frame
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

		//Limits the frame rate to FRAME_RATE
		if (mTimer->DeltaTime() >= (1.0 / FRAME_RATE)) {
			EarlyUpdate();
			Update();
			LateUpdate();
			Render();
		}
	}
}
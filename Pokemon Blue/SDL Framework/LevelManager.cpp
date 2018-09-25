#include "LevelManager.h"


LevelManager::LevelManager() {
	mMap = new Map();
	mPlayer = new Player();
	buildings = new Buildings();
	mGraphics = Graphics::Instance();
	mapList.insert(mapList.begin(), buildings->GetCurrentBuilding());

	mMap->Scale(Vector2(4, 4));
	mPlayer->Scale(Vector2(4, 4));

	Vector2 offset(mGraphics->SCREEN_WIDTH / 2, mGraphics->SCREEN_HEIGHT / 2);
	//mMap->Translate(offset);
	mPlayer->Translate(offset);

}

LevelManager* LevelManager::sInstance = nullptr;
LevelManager* LevelManager::Instance() {
	//  Create a new instance if no instance was created before	
	if (sInstance == nullptr) {
		sInstance = new LevelManager();
	}

	return sInstance;
}

void LevelManager::Release() {
	delete sInstance;
	sInstance = nullptr;

}

LevelManager::~LevelManager() {
	delete buildings;
	buildings = nullptr;
	delete mMap;
	mMap = nullptr;
	delete mPlayer;
	mPlayer = nullptr;
}

void LevelManager::ChangeMap() {

}

void LevelManager::Render() {
	buildings->Render();
	mMap->Render();
	mPlayer->Render();
}


void LevelManager::Update() {
	mMap->Update();
	mPlayer->Update();
}
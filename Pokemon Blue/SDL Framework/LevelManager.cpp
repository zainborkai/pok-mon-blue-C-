#include "LevelManager.h"


LevelManager::LevelManager() : Actor() {
	mMap = new Map();
	mPlayer = new Player();
	buildings = new Buildings();
	mGraphics = Graphics::Instance();
	mapList.insert(mapList.begin(), buildings->GetCurrentBuilding());

	Vector2 offset(160 / 2 -16, 144 / 2 -0 -16 +8);
	//mMap->Translate(offset);
	mPlayer->Translate(offset);

	// *** "I changed some values here so that it lined up with the game perfectly. Cheers!" ~ Khori

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
	//buildings->Render();
	mMap->Render();
	mPlayer->Render();
	mapList[0]->Render();
}


void LevelManager::Update() {
	mMap->Update();
	mPlayer->Update();
	//--Changes Map Position--//
	mPlayer->Move();
	//
	//
	Vector2 offset = mPlayer->Pos();
	Vector2 scl = mPlayer->Scale();
	mMap->Pos(Vector2(offset.x - (mPlayer->X + mPlayer->shiftingX*mPlayer->shift) * 16, offset.y - (mPlayer->Y + mPlayer->shiftingY*mPlayer->shift) * 16));
}
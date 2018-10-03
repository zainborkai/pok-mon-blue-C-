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
	//buildings->Render();
	mMap->Render();
	mPlayer->Render();
	mapList[0]->Render();
}


void LevelManager::Update() {
	mMap->Update();
	mPlayer->Update();
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
	mMap->Pos(Vector2(offset.x - mPlayer->X * 16 * scl.x, offset.y - mPlayer->Y * 16 * scl.y));
}
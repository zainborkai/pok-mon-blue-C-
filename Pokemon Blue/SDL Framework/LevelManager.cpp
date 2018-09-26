#include "LevelManager.h"


LevelManager::LevelManager() {
	mMap = new Map();
	mGroundMap = new GroundMap();
	mGroundMap->ReadCSVFile("Pokemon_NewMap_Space.csv", "Space");
	mGroundMap->ReadCSVFile("Pokemon_NewMap_Grass.csv", "Grass");

	mPlayer = new Player();
	buildings = new Buildings();
	mGraphics = Graphics::Instance();
	mapList.insert(mapList.begin(), buildings->GetCurrentBuilding());

	mMap->Scale(Vector2(4, 4));
	mGroundMap->Scale(Vector2(4, 4));
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
	delete mGroundMap;
	mGroundMap = nullptr;
	delete mPlayer;
	mPlayer = nullptr;
}

void LevelManager::ChangeMap() {
	

}

void LevelManager::Render() {
	//buildings->Render();
	//mMap->Render();
	mGroundMap->Render();
	mPlayer->Render();
	mapList[0]->Render();
}


void LevelManager::Update() {
	mMap->Update();
	mGroundMap->Update();
	mPlayer->Update();
	//--Changes Map Position--//
	int input = mPlayer->Move();
	//
	//
	int moveToX = 0, moveToY = 0;
	//
	if (input == 0) {}
	else {
		if (input == 1) {
			moveToX = mPlayer->X + 0;
			moveToY = mPlayer->Y - 1;
		}
		else if (input == 2) {
			moveToX = mPlayer->X + 0;
			moveToY = mPlayer->Y + 1;
		}
		else if (input == 3) {
			moveToX = mPlayer->X - 1;
			moveToY = mPlayer->Y + 0;
		}
		else if (input == 4) {
			moveToX = mPlayer->X + 1;
			moveToY = mPlayer->Y + 0;
		}


		int groundID = mGroundMap->m_Map[0][moveToY][moveToX];
		//
		cout << "value: " << groundID << endl;
		//
		switch (groundID) {
		case 0:
			mPlayer->X = moveToX;
			mPlayer->Y = moveToY;
			break;
		case 2:
			if (moveToY > mPlayer->Y) {
				moveToY = mPlayer->Y + 2;
				//
				mPlayer->Y = moveToY;
			}
			break;
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


	}


	Vector2 offset = mPlayer->Pos();
	Vector2 scl = mPlayer->Scale();
	mMap->Pos(Vector2(offset.x - mPlayer->X * 16 * scl.x, offset.y - mPlayer->Y * 16 * scl.y));
	mGroundMap->Pos(Vector2(offset.x - mPlayer->X * 16 * scl.x, offset.y - mPlayer->Y * 16 * scl.y));
}
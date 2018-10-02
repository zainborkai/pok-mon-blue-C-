#include "LevelManager.h"

LevelManager::LevelManager() {
	mMap = new Map();
	mGroundMap = new GroundMap();
	mGroundMap->ReadCSVFile("Pokemon_NewMap_Space.csv", "Space");
	mGroundMap->ReadCSVFile("Pokemon_NewMap_Grass.csv", "Grass");

	mPlayer = new Player();
	buildings = new Buildings();
	buildings->SetGroundMapTexture(mGroundMap);
	mGraphics = Graphics::Instance();
	inputManager = InputManager::Instance();
	// Vector
	
	//mapList.pop_back;
	//mGroundMap->Scale(Vector2(4, 4));
	buildings->Scale(Vector2(7, 7));
	mPlayer->Scale(Vector2(7, 7));

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
	buildings->Render();
	//mMap->Render();
	//mGroundMap->Render();
	mPlayer->Render();
}



void LevelManager::Update() {

	//mMap->Update();
	mGroundMap->Update();
	//buildings->Update();
	mPlayer->Update();
	//--Changes Map Position--//
	int input = mPlayer->Move();
	//
	//
	int moveToX = 0, moveToY = 0;
	//
	if (inputManager->KeyPressed(SDL_SCANCODE_N)) {
		buildings->ChangeMapForward(Buildings::GROUNDMAP);	
		// Ground map starting position!
		mPlayer->X = 60;
		mPlayer->Y = 186;
	}
	if (inputManager->KeyPressed(SDL_SCANCODE_M)) {
		buildings->ChangeMapBackward();
		mPlayer->X = 10;
		mPlayer->Y = 60;
	}
	if (input == 0) {}
	else {
		if (input == 1) {
			// UP
			moveToX = mPlayer->X + 0;
			moveToY = mPlayer->Y - 16;
		}
		else if (input == 2) {
			// DOWN
			moveToX = mPlayer->X + 0;
			moveToY = mPlayer->Y + 16;
		}
		else if (input == 3) {
			// LEFT
			moveToX = mPlayer->X - 16;
			moveToY = mPlayer->Y + 0;
		}
		else if (input == 4) {
			// RIGHT
			moveToX = mPlayer->X + 16;
			moveToY = mPlayer->Y + 0;
		}

		int groundID = mGroundMap->m_Map[0][moveToY][moveToX];
		//int buildingID = buildings->(Building[0];

		// Disables collision check
		groundID = 0;
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

	//-------------- FIX THIS!!! --------------//
	buildings->GetCurrentBuilding()->Pos(Vector2(offset.x - buildings->GetCurrentBuilding()->GetmWidth() / 2  * scl.x - mPlayer->X * 6, offset.y - mPlayer->Y * 4 - 32));

	
	//--Working Map--//
	//mGroundMap->Pos(Vector2(offset.x - mPlayer->X * 16 * scl.x, offset.y - mPlayer->Y * 16 * scl.y));
}
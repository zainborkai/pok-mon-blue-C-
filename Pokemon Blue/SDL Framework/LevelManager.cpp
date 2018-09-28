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
		mPlayer->SetX(60);
		mPlayer->SetY(186);
	}
	if (inputManager->KeyPressed(SDL_SCANCODE_M)) {
		buildings->ChangeMapBackward();
		mPlayer->SetX(10);
		mPlayer->SetY(60);
	}
	if (input == 0) {}
	else {
		if (input == 1) {
			// UP
			moveToX = mPlayer->GetX() + 0;
			moveToY = mPlayer->GetY() - 16;
		}
		else if (input == 2) {
			// DOWN
			moveToX = mPlayer->GetX() + 0;
			moveToY = mPlayer->GetY() + 16;
		}
		else if (input == 3) {
			// LEFT
			moveToX = mPlayer->GetX() - 16;
			moveToY = mPlayer->GetY() + 0;
		}
		else if (input == 4) {
			// RIGHT
			moveToX = mPlayer->GetX() + 16;
			moveToY = mPlayer->GetY() + 0;
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
			mPlayer->SetX(moveToX);
			mPlayer->SetY(moveToY);
			break;
		case 2:
			if (moveToY > mPlayer->GetY()) {
				moveToY = mPlayer->GetY() + 2;
				//
				mPlayer->SetY(moveToY);
			}
			break;
		}

		
		if (mPlayer->GetX() <= 0) {
			mPlayer->SetX(0);
		}
		else if (mPlayer->GetX() > 88 - 1) { // ??? <-- NO MAGIC NUMBERS!
			mPlayer->SetX(88 - 1);
		}

		if (mPlayer->GetY() <= 0) {
			mPlayer->SetY(0);
		}
		else if (mPlayer->GetY() > 198 - 1) { // ??? <-- NO MAGIC NUMBERS!
			mPlayer->SetY(198 - 1);
		}
	}

	Vector2 offset = mPlayer->Pos();
	Vector2 scl = mPlayer->Scale();

	//-------------- FIX THIS!!! --------------//
	buildings->GetCurrentBuilding()->Pos(Vector2(offset.x - buildings->GetCurrentBuilding()->GetmWidth() / 2  * scl.x - mPlayer->GetX() * 6, offset.y - mPlayer->GetY() * 4 - 32));

	
	//--Working Map--//
	//mGroundMap->Pos(Vector2(offset.x - mPlayer->X * 16 * scl.x, offset.y - mPlayer->Y * 16 * scl.y));
}
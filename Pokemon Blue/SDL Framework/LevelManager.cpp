#include "LevelManager.h"


LevelManager::LevelManager() {
	mMap = new Map();
	mGroundMap = new GroundMap();
	mGroundMap->ReadCSVFile("Pokemon_NewMap_Space.csv", "Space");
	mGroundMap->ReadCSVFile("Pokemon_NewMap_Grass.csv", "Grass");
	mGroundMap->ReadCSVFile("Pokemon_NewMap_Houses.csv", "Houses");

	mPlayer = new Player();
	mGroundGrass = new GroundGrass();
	mBattleScreen = new BattleScreen();
	buildings = new Buildings();
	mGraphics = Graphics::Instance();
	mapList.insert(mapList.begin(), buildings->GetCurrentBuilding());

	mMap->Scale(Vector2(4, 4));
	mGroundMap->Scale(Vector2(4, 4));
	mGroundGrass->Scale(Vector2(4, 4));
	mBattleScreen->Scale(Vector2(5, 5));
	mapList[0]->Scale(Vector2(4, 4));
	mPlayer->Scale(Vector2(4, 4));

	Vector2 offset(mGraphics->SCREEN_WIDTH / 2, mGraphics->SCREEN_HEIGHT / 2);
	//mMap->Translate(offset);
	mPlayer->Translate(offset);

	mGroundMap->mPlayerX = mPlayer->X;
	mGroundMap->mPlayerY = mPlayer->Y;
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
	delete mGroundGrass;
	mGroundGrass = nullptr;
	delete mPlayer;
	mPlayer = nullptr;
}

void LevelManager::ChangeMap() {
	

}

void LevelManager::Render() {
	Vector2 offset = mPlayer->Pos();
	Vector2 scl = mPlayer->Scale();
	string grassID = mGroundMap->m_Map[1][mPlayer->Y][mPlayer->X];
	string HouseName = mGroundMap->EnteringHouse(mPlayer->X, mPlayer->Y);

	mMap->Render();
	mGroundMap->Render();
	if (GetStatus() == 2) {
		mapList[0]->Render();
		cout << "House Name:" << HouseName << "\n";
	}
	//mGroundGrass->Render();
	//mapList[0]->Render();
	mPlayer->Render();
	if (GetStatus() == 3) {
		mBattleScreen->Render();
		//cout << "Battle Mode!" << "\n";
	}

	if (grassID == "0" && GetStatus() == 1) {
		mGroundMap->SetCurrentLayer2Grass();
		mGroundMap->Pos(Vector2(100 * scl.x, 75 * scl.y));
		mGroundMap->Render();
	}
	//SDL_WaitEventTimeout(NULL, 20);

}


void LevelManager::Update() {

	mGroundMap->Update();

	mapList[0]->Update();
	mPlayer->Update();
	mBattleScreen->Update();
	mGroundMap->Update();
	mMap->Update();

	mPlayer->X = mGroundMap->mPlayerX;
	mPlayer->Y = mGroundMap->mPlayerY;

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

		SetStatus(1); // Set status to ground
		string groundID = mGroundMap->m_Map[0][moveToY][moveToX];
		//groundID = "0";
		//
		cout << "value: " << groundID << endl;
		//
		if (groundID == "0") {
			mPlayer->X = moveToX;
			mPlayer->Y = moveToY;
		}
		if (groundID == "2") {
			if (moveToY > mPlayer->Y) {
				moveToY = mPlayer->Y + 2;
				//
				mPlayer->Y = moveToY;
			}
		}

		string grassID = mGroundMap->m_Map[1][mPlayer->Y][mPlayer->X];
		if (grassID == "0") {
			srand(static_cast<unsigned int>(time(0)));  //seed random number generator
			int isEnemy = rand() % 5 + 0;  // random number between 1 and 5
			if (isEnemy == 1) {
				SetStatus(3);	// set status to battle
			}
		}

		string houseName = "";
		houseName = mGroundMap->EnteringHouse(moveToX, moveToY);
		cout << "x: " << moveToX << " y:" << moveToY << "\n";

		if (houseName != "") {
			mPlayer->Y = mPlayer->Y - 1;
			buildings->SetCurrentBuilding(houseName);
			mapList.clear();
			mapList.insert(mapList.begin(), buildings->GetCurrentBuilding());
			mapList[0]->Scale(Vector2(8, 8));
			mGroundMap->mPlayerX = mPlayer->X;
			mGroundMap->mPlayerY = mPlayer->Y;
			mPlayer->X = 0;
			mPlayer->Y = 0;
			SetStatus(2); // set status to house
			cout << " Entering " << houseName << "\n";
		}
		else {
			mGroundMap->mPlayerX = mPlayer->X;
			mGroundMap->mPlayerY = mPlayer->Y;
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

	//mMap->Pos(Vector2(offset.x - mPlayer->X * 16 * scl.x, offset.y - mPlayer->Y * 16 * scl.y));
	mGroundMap->SetCurrentLayer2Ground();
	mGroundMap->Pos(Vector2(offset.x - mPlayer->X * 16 * scl.x, offset.y - mPlayer->Y * 16 * scl.y));
	//mapList[0]->Pos(Vector2(offset.x - mPlayer->X * 16 * scl.x + 29 * 16, offset.y - mPlayer->Y * 16 * scl.y + 29 * 16));
	mapList[0]->Pos(Vector2(0, 0));
}
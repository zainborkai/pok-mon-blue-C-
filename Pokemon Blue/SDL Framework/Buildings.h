#include "Map.h"
#include <vector>
#include "AssetManager.h"
using namespace std;

// ID Format: 
// (City,Place,Type of Person, Number of Person)
// --------------------------------------------- //
// ex. PH_P1
// Pallet Town House, Person 1
// ex.2 VM_C1
// Viridian City PokeMart, Child 1

class Buildings : public Map {

private:
	char PlayerHouseFloorOne[8][8] = { { 'W','W','W','M','W','W','W','W' },
	{ 'B','B',' ',' ',' ',' ',' ','F' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' },
	{ ' ',' ',' ','W','W','P',' ',' ' },
	{ ' ',' ',' ','W','W',' ',' ',' ' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' }, };

	char PlayerHouseFloorTwo[8][8] = { { 'C','W','W',' ',' ',' ',' ','F' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' },
	{ ' ',' ',' ','N',' ',' ',' ',' ' },
	{ 'W',' ',' ',' ',' ',' ','W',' ' },
	{ 'W',' ',' ',' ',' ',' ','W',' ' }, };

	char PalletHouseOne[8][8] = { { 'B','B',' ','W',' ',' ',' ','B' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' },
	{ ' ',' ',' ','b','W',' ',' ',' ' },
	{ ' ',' ',' ','W','W',' ',' ',' ' },
	{ 'W',' ',' ',' ',' ',' ',' ','W' },
	{ 'W',' ',' ',' ',' ',' ',' ','W' }, };

	char ViridianHouseOne[8][8] = { { 'W','W',' ','M','N',' ',' ','W' },
	{ 'B','B',' ',' ',' ',' ',' ','B' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' },
	{ ' ','a',' ','W','W','b',' ',' ' },
	{ ' ',' ',' ','W','W',' ',' ',' ' },
	{ ' ',' ',' ',' ','e',' ',' ',' ' },
	{ 'W',' ',' ',' ',' ',' ',' ','W' },
	{ 'W',' ',' ',' ',' ',' ',' ','W' }, };

	char ViridianHouseTwo[8][8] = { { ' ',' ',' ','d',' ',' ',' ','W' },
	{ ' ',' ',' ',' ','c',' ',' ','B' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' },
	{ ' ',' ',' ','W','W',' ',' ',' ' },
	{ ' ',' ',' ','b','W',' ',' ',' ' },
	{ ' ',' ',' ','j',' ',' ',' ',' ' },
	{ 'W',' ',' ',' ',' ',' ',' ','W' },
	{ 'W',' ',' ',' ',' ',' ',' ','W' }, };

	char ViridianPokeMart[8][8] = { { 'W','W','W','W','W','W','W','W' },
	{ 'W','W','W','W','W','W','W','W' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' },
	{ 'W','W','j','W','W','W','W' },
	{ ' ','W',' ',' ','f','f','f','f' },
	{ ' ','o',' ',' ',' ',' ',' ',' ' },
	{ 'W','W',' ',' ',' ',' ',' ',' ' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' }, };

	char PewterHouseOne[8][8] = { { 'W','W','W','M','W','W','W','W' },
	{ 'B','b',' ',' ',' ',' ',' ','B' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' },
	{ ' ',' ',' ','W','W',' ',' ',' ' },
	{ ' ',' ',' ','W','W',' ',' ',' ' },
	{ ' ',' ',' ','d','n',' ',' ',' ' },
	{ 'W',' ',' ',' ',' ',' ',' ','W' },
	{ 'W',' ',' ',' ',' ',' ',' ','W' }, };

	char PewterHouseTwo[8][8] = { { 'W','W','W','M','W','W','W','W' },
	{ 'B','B',' ',' ',' ',' ',' ','B' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' },
	{ ' ',' ','d','W','W',' ',' ',' ' },
	{ ' ',' ',' ','W','W',' ',' ',' ' },
	{ ' ',' ',' ',' ','d',' ',' ',' ' },
	{ 'W',' ',' ',' ',' ',' ',' ','W' },
	{ 'W',' ',' ',' ',' ',' ',' ','W' }, };

	char PewterGym[12][10] = { { 'W','W','W','W','W','W','W','W','W','W' },
	{ 'W',' ',' ',' ','d',' ',' ',' ',' ','W' },
	{ 'W',' ',' ',' ',' ',' ',' ',' ',' ','W' },
	{ 'W','W','W','W',' ',' ','W','W','W','W' },
	{ 'W',' ',' ',' ',' ',' ',' ',' ',' ','W' },
	{ 'W',' ','W',' ',' ','W','W','W',' ','W' },
	{ 'W',' ',' ','d',' ',' ',' ',' ',' ','W' },
	{ 'W',' ','W',' ',' ','W','W','W',' ','W' },
	{ 'W',' ',' ',' ',' ',' ',' ',' ',' ','W' },
	{ 'W','W','W','W',' ',' ','W','W','W','W' },
	{ ' ',' ',' ','S',' ',' ','S','f',' ',' ' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' }, };

	char PewterPokeMart[8][8] = { { 'W','W','W','W','W','W','W','W' },
	{ 'W','W','W','W','W','W','W','W' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' },
	{ 'W','W',' ',' ','W','W','W','W' },
	{ ' ',' ',' ','g','f','d','g','g' },
	{ ' ','f',' ',' ',' ','g',' ',' ' },
	{ 'W','W',' ',' ',' ',' ',' ',' ' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ' }, };

	char PewterPokeCenter[8][14] = { { 'W','W','W','W','W','W','W','W','W','W','W','W','W','W' },
	{ 'W','W','W','J','W','W','W','W','W','W','W','f','W','W', },
	{ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' },
	{ 'f',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' },
	{ 'W',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' },
	{ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ' },
	{ 'W','W',' ',' ',' ',' ','W','W',' ',' ',' ',' ','W','W' },
	{ 'W','W',' ','E','E',' ','W','W',' ',' ',' ','f','W','W' }, };


	Texture* currentBuilding;
	Texture* nextFloor;
	Texture* prevFloor;

public:
	Buildings();
	~Buildings() {};
	// Setters
	void SetCurrentBuilding(Texture* txt) {
		currentBuilding = txt;
	};
	void SetCurrentBuilding(string txt) {
		if (txt == "PlayerHouseFloor1") currentBuilding = PalletPlayerHouseFloor1;
		if (txt == "PalletHouse1") currentBuilding = PalletHouse1;
		if (txt == "PalletLab") currentBuilding = PalletLab;
	};

	void SetNextFloor(Texture* txt) {
		nextFloor = txt;
	}
	void SetPrevFloor(Texture* txt) {
		prevFloor = txt;
	}

	// Getters
	Texture* GetCurrentBuilding() {
		return currentBuilding;
	}
	Texture* GetNextFloor() {
		return nextFloor;
	}
	Texture* GetPrevFloor() {
		return prevFloor;
	}
	//
	void Render();
	private:
		

		Texture* PalletPlayerHouseFloor1;
		Texture* PalletPlayerHouseFloor2;
		Texture* PalletHouse1;
		Texture* PalletLab;

		Texture* ViridianHouse1;
		Texture* ViridianHouse2;
		Texture* ViridianMart;
		Texture* ViridianCentre;

		Texture* PewterHouse1;
		Texture* PewterHouse2;
		Texture* PewterMart;
		Texture* PewterCentre;
		//Texture* PewterGym;
		//Texture* PewterMuseum;
};



#include "Map.h"
#include <vector>
#include "AssetManager.h"

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
	std::vector<Texture*> mapList;

public:
	Buildings();
	~Buildings() {};
	// Setters
	void SetCurrentBuilding(Texture* txt) {
		currentBuilding = txt;
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
	void Update();

	enum BuildingNames {
		PALLETPLAYERHOUSEFLOOR1, PALLETPLAYERHOUSEFLOOR2, PALLETHOUSE1, VIRIDIANHOUSE1, VIRIDIANHOUSE2, VIRIDIANMART,
		VIRIDIANCENTRE, PEWTERHOUSE1, PEWTERMART, PEWTERCENTRE
	};

	void ChangeMapForward(BuildingNames);
	void ChangeMapBackward();
	private:
		BuildingNames buildingNames;

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



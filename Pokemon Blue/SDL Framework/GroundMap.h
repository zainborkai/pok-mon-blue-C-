#ifndef GROUNDMAP_H
#define GROUNDMAP_H

#include "Map.h"
#include "Texture.h"
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class GroundMap : public Map {
public:
	Texture* m_grass;
	Texture* m_ground;
	Texture* currentLayer;
	string m_Map[3][200][100];
	GroundMap();
	~GroundMap();
	void Update();
	void Render();
	bool ReadCSVFile(string fname, string arrayName);
	string EnteringHouse(int x, int y);
	int mPlayerX;
	int mPlayerY;

	//Setters
	void SetCurrentLayer(Texture* txt) {
		currentLayer = txt;
	};
	void SetCurrentLayer2Grass() {
		currentLayer = m_grass;
	}
	void SetCurrentLayer2Ground() {
		currentLayer = m_ground;
	}

	// Getters
	Texture* GetCurrentLayer() {
		return currentLayer;
	}


};

#endif
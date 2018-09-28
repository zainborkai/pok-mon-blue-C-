#include "GroundMap.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

GroundMap::GroundMap() :

	//Texture("PokemonMasterMap.png", 1000, 2000, 1100, 2000) {
	//	Pos(Vector2(2500, 2500));
	//	centering = Vector2(0, 0);
	//	m_grass = new Texture("grass.png", 0, 0, 16, 16);

	Texture("CroppedMap.png", 0, 0, 1408, 3168) {

	centering = Vector2(0, 0);
	// WrapMode(LOOP);

}




GroundMap::~GroundMap() {}

void GroundMap::Update() {
	//Translate(Vector2(.1f, .1f));
}


/*
void GroundMap::Render() {
	//Vector2 pos = Pos(WORLD);

	//mRenderRect.x = pos.x;
	//mRenderRect.y = pos.y;
	
	//mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(WORLD));
}*/


bool GroundMap::ReadCSVFile(string fname, string arrayName) {
	ifstream src(fname);
	string currentLine;
	string delimiter = ",";
	size_t pos = 0;
	string cell_value = "";
	int    cell_number = 0;
	int	   line_number = 0;
	int	   currMap = 0;

	bool result = true;

	if (arrayName == "Space") currMap = 0;
	if (arrayName == "Grass") currMap = 1;



	if (!src.is_open()) {
		cout << "Couldn't open file :" << fname << endl;
		return -1;
	}


	while (!src.eof()) {
		getline(src, currentLine);
		cell_number = 0;
		while ((pos = currentLine.find(delimiter)) != string::npos) {
			cell_value = currentLine.substr(0, pos);

			currentLine.erase(0, pos + delimiter.length());
			m_Map[currMap][line_number][cell_number] = stoi(cell_value);

			// Display all cells
			//std::cout << line_number << ":" << cell_number << ":" << m_Map[currMap][line_number][cell_number] << std::endl;

			cell_number++;
		}
		line_number++;
	}

	src.close();

	return result;
}
#include "GroundMap.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

GroundMap::GroundMap() {
	//Texture("CroppedMap.png", 0, 0, 1408, 3168) {
	//centering = Vector2(0, 0);

	//Texture("PokemonMasterMap.png", 1000, 2000, 1100, 2000) {
	//	Pos(Vector2(2500, 2500));
	//	centering = Vector2(0, 0);
	

	// WrapMode(LOOP);
	m_ground = new Texture("CroppedMap.png", 0, 0, 1408, 3168);
	m_grass = new Texture("Grass.png", 48, 0, 16, 16);
	SetCurrentLayer(m_ground);
}




GroundMap::~GroundMap() {}

void GroundMap::Update() {
	//Translate(Vector2(.1f, .1f));
}



void GroundMap::Render() {
	Vector2 pos = Pos(WORLD);
	Vector2 scale = Scale(WORLD);

	centering = Vector2(0, 0);
	// Centers the texture on the texture's world position so that its position is not the top left
	mRenderRect.x = (int)(pos.x - mWidth * scale.x * centering.x);
	mRenderRect.y = (int)(pos.y - mWidth * scale.y * centering.y);

	// Scales the width and height according to the scale of the GameEntity
	mRenderRect.w = (int)(mWidth * scale.x);
	mRenderRect.h = (int)(mHeight * scale.y);
	//cout << "w:" << scale.x << " h:" << scale.y;
	if (currentLayer == m_grass) {
		mRenderRect.w = 16 * scale.x;
		mRenderRect.h = 16 * scale.y;
	}
	

	mGraphics->DrawTexture(currentLayer->GetmTex(), (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(WORLD));
}


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

	if (arrayName == "Space")  currMap = 0;
	if (arrayName == "Grass")  currMap = 1;
	if (arrayName == "Houses") currMap = 2;
	

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
			//m_Map[currMap][line_number][cell_number] = stoi(cell_value);
			m_Map[currMap][line_number][cell_number] = cell_value;
			//if( currMap == 2) 
			//			std::cout << line_number << ":" << cell_number << ":" << m_Map[currMap][line_number][cell_number] << std::endl;
			cell_number++;
		}
		line_number++;
	}

	src.close();

	return result;
}

string GroundMap::EnteringHouse(int x, int y) {
	string houseName = "";
//	cout << "name:" << m_Map[2][i+3][0] << "\n";
	for (int i = 0; i < 99; ++i) {
		//cout << "name:" << m_Map[2][i][0] << "\n";
		if (x == stoi(m_Map[2][i][1]) && y ==stoi(m_Map[2][i][2])) {
			houseName = m_Map[2][i][0];
			break;
		}
		if (m_Map[2][i][0] == "") {
			break;
		}
	}

	return houseName;
}

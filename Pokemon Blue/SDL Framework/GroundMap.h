#ifndef GROUNDMAP_H
#define GROUNDMAP_H


#include "Texture.h"
#include <vector>
using namespace std;

class GroundMap : public Texture {
public:
	Texture* m_grass;
	int m_Map[3][200][100];
	GroundMap();
	~GroundMap();
	void Update();
	//void Render();
	bool ReadCSVFile(string fname, string arrayName);
};

#endif
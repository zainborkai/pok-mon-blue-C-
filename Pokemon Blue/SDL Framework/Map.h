#ifndef MAP_H
#define MAP_H

#include "Texture.h"

class Map : public Texture {
public:
	Map();
	~Map();
	
	void Render();
	void Update();

	int mapX;
	int mapY;
};

#endif
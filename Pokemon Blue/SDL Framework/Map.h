#ifndef MAP_H
#define MAP_H

#include "Actor.h"
#include "Texture.h"

class Map : public Actor {
public:
	Map();
	~Map();
		
	// void Render();
	void Update();

	int mapX;
	int mapY;
};

#endif
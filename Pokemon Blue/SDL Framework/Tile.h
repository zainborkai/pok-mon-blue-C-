#ifndef TILE_H
#define TILE_H

#include "AnimatedTexture.h"


class Tile : public AnimatedTexture {
public:
	Tile();
	~Tile();
	void Update();
	// void Render();

	void Destroy();

private:
	// GameManager* _gm; {

};


#endif

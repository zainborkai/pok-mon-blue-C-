
#include "Tile.h"


Tile::Tile() :
	AnimatedTexture("nulltexture.png", 0, 0, 16, 16) {

	// _gm = nullptr; // GameManager* gm
	// AssignData();
}
Tile::~Tile() {}


void Tile::Update() {
	Translate(Vector2(0.1f, 0.3f));
}


void Tile::Destroy() {
	// _gm->UnregisterActor(this);
	//
	delete this;
}

#include "Map.h"

Map::Map() :
	Texture("CroppedMap.png", 0, 0, 1408, 3168) {
	
	centering = Vector2(0, 0);
	// WrapMode(LOOP);
}
	

Map::~Map() {}

void Map::Update() {
	//Translate(Vector2(-.1f, -.1f));
}



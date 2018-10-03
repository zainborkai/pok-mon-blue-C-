#include "GroundGrass.h"


GroundGrass::GroundGrass() :
	AnimatedTexture("pokemon_player_spritesheet.png", 0, 0, 16, 16, 3, .5f, HORIZONTAL) {
	centering = Vector2(0, 0);

	X = 128;
	Y = 128;
	//X = 0;
	//Y = 0;

}

void GroundGrass::Update() {
	//Translate(Vector2(-.1f, -.1f));
	AnimatedTexture::Update();
}


GroundGrass::~GroundGrass() {}
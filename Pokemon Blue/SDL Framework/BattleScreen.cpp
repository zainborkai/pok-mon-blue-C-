#include "BattleScreen.h"


BattleScreen::BattleScreen() :
	Texture("pokemonBattleScreenUI_.png", 0, 0, 505, 457) {
		Pos(Vector2(-40, -600));
		centering = Vector2(0, 0);

}

void BattleScreen::Update() {
	//Translate(Vector2(-.1f, -.1f));
	Texture::Update();
}


BattleScreen::~BattleScreen() {}
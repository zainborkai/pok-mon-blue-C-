#include "Rival.h"

Rival::Rival() :
	//This spritesheet is no good. Need to find a new one but can use to test things
	NPC("_pokemonspecial_sprites__red_by_liliebiehlina3siste-d5009qo.png", 70, 288, 16, 16, 1, 1.0f, HORIZONTAL)
{
	mText = Text::Instance();
	Pos(Vector2(150, 0));
}

Rival::~Rival() {
	Text::Release();
	mText = nullptr;
}

void Rival::Render() {
	Vector2 pos = Pos(WORLD);

	mRenderRect.x = pos.x;
	mRenderRect.y = pos.y;

	mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(WORLD));
}

void Rival::Update() {

}

void Rival::conversation() {

	mText = Text::Instance();
	//
	//The different parts on text your rival says depending on point in the game
	mText->displayTextBox("RIVAL_BEGINNING");
	mText->displayTextBox("RIVAL_BEFORE_CHOICE");
	mText->displayTextBox("RIVAL_AFTER_CHOICE");
	mText->displayTextBox("RIVAL_ROUTE22");
	mText->displayTextBox("RIVAL_ROUTE22_AFTER_BATTLE");
}
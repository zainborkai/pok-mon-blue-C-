#include "Character.h"

Character::Character() :
	Texture("Mom.png") {
	Pos(Vector2(200, 200));
}

Character::~Character() {}

void Character::Update() {
	Translate(Vector2(.1f, .1f));
}

void Character::Render() {
	Vector2 pos = Pos(WORLD);

	mRenderRect.x = pos.x;
	mRenderRect.y = pos.y;

	//mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(WORLD));
}
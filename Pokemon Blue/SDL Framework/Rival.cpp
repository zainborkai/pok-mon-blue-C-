#include "Rival.h"

Rival::Rival() :
	AnimatedTexture("OAK.png", 0, 0, 32, 32, 1, 1.0f, HORIZONTAL)
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

}
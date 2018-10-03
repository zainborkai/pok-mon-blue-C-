#include "Brock.h"

Brock::Brock() :
	NPC("NPCSprites.png", 130, 111, 16, 16, 1, 1.0f, HORIZONTAL)
{
	mText = Text::Instance();
	Pos(Vector2(250, 100));
}

Brock::~Brock() {

}

void Brock::Update() {

}

void Brock::Render() {
	Vector2 pos = Pos(WORLD);

	mRenderRect.x = pos.x;
	mRenderRect.y = pos.y;

	mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(WORLD));
}
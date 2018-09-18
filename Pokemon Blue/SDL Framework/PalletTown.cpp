#include "PalletTown.h"

PalletTown::PalletTown() :
	AnimatedTexture("CroppedMap.png", 800, 576, 1600, 1000, 1, 1, VERTICAL) {
	Pos(Vector2(0, 0));
	WrapMode(LOOP);
}

PalletTown::~PalletTown() {}



void PalletTown::Update() {
	//Translate(Vector2(-.1f, -.1f));
}

void PalletTown::Render() {
	Vector2 pos = Pos(WORLD);
	Vector2 scale = Scale(WORLD);

	this->mRenderRect.x = pos.x;
	this->mRenderRect.y = pos.y;

	//mRenderRect.x = (int)(pos.x - mWidth * scale.x * 0.5f);
	//mRenderRect.y = (int)(pos.y - mWidth * scale.y * 0.5f);

	// Scales the width and height according to the scale of the GameEntity
	//mRenderRect.w - (int)(mWidth * scale.x);
	//mRenderRect.h - (int)(mHeight * scale.y);

	mGraphics->DrawTexture(this->mTex, (mClipped) ? &this->mClipRect : NULL, &this->mRenderRect, Rotation(WORLD));
}



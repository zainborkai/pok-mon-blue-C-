#include "PalletTown.h"

PalletTown::PalletTown() :
	AnimatedTexture("Mom.png") {
	Pos(Vector2(0, 0));

}

PalletTown::~PalletTown() {}

void PalletTown::Update() {
	Translate(Vector2(.1f, .1f));
}

void PalletTown::Render() {
	Vector2 pos = Pos(WORLD);

	mRenderRect.x = pos.x;
	mRenderRect.y = pos.y;

	mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(WORLD));
}

#include "Buildings.h"

Buildings::Buildings() {
	ViridianHouse = new Texture("ViridianHouseOne.png", 0, 0, 128, 128);

	SetCurrentBuilding(ViridianHouse);
	SetPrevFloor(ViridianHouse);
	//SetNextFloor()
}
// l
void Buildings::Render() {
	Vector2 pos = Pos(WORLD);
	Vector2 scale = Scale(WORLD);

	// Centers the texture on the texture's world position so that its position is not the top left
	mRenderRect.x = (int)(pos.x - mWidth * scale.x * centering.x);
	mRenderRect.y = (int)(pos.y - mWidth * scale.y * centering.y);

	// Scales the width and height according to the scale of the GameEntity
	mRenderRect.w = (int)(mWidth * scale.x);
	mRenderRect.h = (int)(mHeight * scale.y);

	mGraphics->DrawTexture(ViridianHouse->GetmTex(), (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(WORLD));
}


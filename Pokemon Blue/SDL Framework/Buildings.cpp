#include "Buildings.h"

Buildings::Buildings() {

	PalletPlayerHouseFloor1 = new Texture("PalletTown/PlayerHouseFloorOne.png", 0, 0, 128, 128);
	PalletPlayerHouseFloor2 = new Texture("ViridianHouseOne.png", 0, 0, 128, 128);
	PalletHouse1 = new Texture("PalletTown/SecondHouse.png", 0, 0, 128, 128);
	//PalletLab = new Texture(0, 0, );

	ViridianHouse1 = new Texture("ViridianHouseOne.png", 0, 0, 228, 228);
	ViridianHouse2 = new Texture("ViridianHouseTwo.png", 0, 0, 128, 128);
	ViridianMart = new Texture("ViridianPokeMart.png", 0, 0, 8, 8);
	ViridianCentre = new Texture("ViridianPokeCenter.png", 0, 0, 128, 224);

	PewterHouse1 = new Texture("PewterHouseOne.png", 0, 0, 128, 128);
	PewterHouse2 = new Texture("PewterHouseTwo.png", 0, 0, 128, 128);
	PewterMart = new Texture("PewterPokeMart.png", 0, 0, 8, 8);
	PewterCentre = new Texture("PewterPokeCenter.png", 0, 0, 128, 224);
	//PewterGym = new Texture(0, 0,);
	//PewterMuseum = new Texture(0, 0,);

	SetCurrentBuilding(ViridianHouse1);
	SetPrevFloor(ViridianHouse1);
	//SetNextFloor();
}
// l
void Buildings::Render() {
	Vector2 pos = Pos(WORLD);
	Vector2 scale = Scale(WORLD);

	// Centers the texture on the texture's world position so that its position is not the top left
	//mRenderRect.x = (int)(pos.x - mWidth * scale.x * centering.x);
	//mRenderRect.y = (int)(pos.y - mWidth * scale.y * centering.y);
	mRenderRect.x = 0;
	mRenderRect.y = 0;


	// Scales the width and height according to the scale of the GameEntity
	mRenderRect.w = (int)(mWidth * scale.x);
	mRenderRect.h = (int)(mHeight * scale.y);
	mRenderRect.w = 1280;
	mRenderRect.h = 1280;


	//mGraphics->DrawTexture(currentBuilding->GetmTex(), (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(WORLD));
}


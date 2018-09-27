#include "Buildings.h"


Buildings::Buildings() {

	PalletPlayerHouseFloor1 = new Texture("ViridianHouseOne.png", 0, 0, 128, 128);
	PalletPlayerHouseFloor2 = new Texture("ViridianHouseTwo.png", 0, 0, 128, 128);
	PalletHouse1 = new Texture("ViridianHouseOne.png", 0, 0, 128, 128);
	//PalletLab = new Texture(0, 0, );

	ViridianHouse1 = new Texture("ViridianHouseOne.png", 0, 0, 128, 128);
	ViridianHouse2 = new Texture("ViridianHouseTwo.png", 0, 0, 128, 128);
	ViridianMart = new Texture("ViridianPokeMart.png", 0, 0, 8, 8);
	ViridianCentre = new Texture("ViridianPokemonCenter.png", 0, 0, 128, 224);

	PewterHouse1 = new Texture("PewterHouse.png", 0, 0, 128, 128);
	//PewterHouse2 = new Texture("PewterHouseTwo.png", 0, 0, 128, 128);
	PewterMart = new Texture("PewterPokeMart.png", 0, 0, 128, 128);
	PewterCentre = new Texture("PewterPokemonCenter.png", 0, 0, 128, 224);
	//PewterGym = new Texture(0, 0,);
	//PewterMuseum = new Texture(0, 0,);

	SetCurrentBuilding(PewterMart);
	SetPrevFloor(PewterMart);
	mapList.insert(mapList.begin(),GetCurrentBuilding());
	//SetNextFloor();
	//centering = Vector2(1, 0);
}

void Buildings::ChangeMapForward(BuildingNames bn) {
	switch (bn) {

	case PALLETPLAYERHOUSEFLOOR1:
		SetCurrentBuilding(PalletPlayerHouseFloor1);
		break;
	case PALLETPLAYERHOUSEFLOOR2:
		SetCurrentBuilding(PalletPlayerHouseFloor2);
		break;

	case PALLETHOUSE1:
		SetCurrentBuilding(PalletHouse1);
		break;

	case VIRIDIANHOUSE1:
		SetCurrentBuilding(ViridianHouse1);
		break;

	case VIRIDIANHOUSE2:
		SetCurrentBuilding(ViridianHouse2);
		break;

	case VIRIDIANCENTRE:
		SetCurrentBuilding(ViridianCentre);
		break;

	case VIRIDIANMART:
		SetCurrentBuilding(ViridianMart);
		break;

	case PEWTERHOUSE1:
		SetCurrentBuilding(PewterHouse1);
		break;

	case PEWTERMART:
		SetCurrentBuilding(PewterMart);
		break;

	case PEWTERCENTRE:
		SetCurrentBuilding(PewterCentre);
		break;
	}
	mapList.insert(mapList.begin(), GetCurrentBuilding());
}

void Buildings::ChangeMapBackward() {
	mapList.erase(mapList.begin());
}
void Buildings::Update() {

}

void Buildings::Render() {
	Vector2 pos = Pos(WORLD);
	Vector2 scale = Scale(WORLD);

	// Centers the texture on the texture's world position so that its position is not the top left
	//mRenderRect.x = (int)(pos.x - mWidth * scale.x * centering.x);
	//mRenderRect.y = (int)(pos.y - mWidth * scale.y * centering.y);

	// Scales the width and height according to the scale of the GameEntity
	//mRenderRect.w = (int)(mWidth * scale.x);
	//mRenderRect.h = (int)(mHeight * scale.y);
	mapList[0]->SetRenderRectW((int)(mapList[0]->GetmWidth() * scale.x));
	mapList[0]->SetRenderRectH((int)(mapList[0]->GetmHeight() * scale.y));
	mapList[0]->SetCenteringX(0);
	mapList[0]->SetCenteringY(0);
	mapList[0]->SetRenderRectX((int)(mapList[0]->GetPos().x - mWidth * scale.x * mapList[0]->GetCenteringX()));
	mapList[0]->SetRenderRectY((int)(mapList[0]->GetPos().y - mWidth * scale.y * mapList[0]->GetCenteringY()));

	mGraphics->DrawTexture(mapList[0]->GetmTex(), (mClipped) ? &mClipRect : NULL, &mapList[0]->GetRenderRect(), Rotation(WORLD));
}


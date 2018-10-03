#include "Mom.h"

Mom::Mom() :
	//This spritesheet is no good. Need to find a new one but can use to test things
	NPC("Mom.png", 0, 0, 32, 32, 1, 1.0f, HORIZONTAL)
{
	mText = Text::Instance();
	Pos(Vector2(175, 0));
}

Mom::~Mom() {
	Text::Release();
	mText = nullptr;
}

void Mom::Render() {
	Vector2 pos = Pos(WORLD);

	mRenderRect.x = pos.x;
	mRenderRect.y = pos.y;

	mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(WORLD));
}

void Mom::Update() {

}

void Mom::conversation() {

	mText = Text::Instance();
	//
	//The different parts on text your mom says depending on point in the game
	if (Beginning) {
		mText->displayTextBox("MOM_BEGINNING");
	}
	else {
		mText->displayTextBox("MOM_STATIC");
	}
	
}
#include "Oak.h"

Oak::Oak() :
	AnimatedTexture("OAK.png", 0, 0, 32, 32, 1, 1.0f, HORIZONTAL)
{
	mText = Text::Instance();
	Pos(Vector2(100, 0));
}

Oak::~Oak() {
	Text::Release();
	mText = nullptr;
}

void Oak::conversation()
{
	mText = Text::Instance();

	if (!choice && !battle) {
		mText->displayTextBox("OAK_BEFORE_CHOICE");
	}
	else if (choice && !battle) {
		mText->displayTextBox("OAK_AFTER_CHOICE");
	}
	else if (choice && battle) {
		mText->displayTextBox("OAK_AFTER_RIVAL_BATTLE");
	}
	else if (delivery) {
		mText->displayTextBox("OAK_AFTER_DELIVERY");
	}
}

void Oak::Update() {

}

void Oak::Render() 
{
	Vector2 pos = Pos(WORLD);

	mRenderRect.x = pos.x;
	mRenderRect.y = pos.y;

	mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(WORLD));
}
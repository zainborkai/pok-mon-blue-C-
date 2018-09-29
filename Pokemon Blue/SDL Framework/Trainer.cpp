#include "Trainer.h"

Trainer::Trainer() :
	NPC("NPCSprites.png", 243, 17, 16, 16, 1, 1.0f, HORIZONTAL)
{
	mText - Text::Instance();
	Pos(Vector2(100, 300));
}

Trainer::~Trainer() {
	Text::Release();
	mText = nullptr;
}

void Trainer::Render() {
	Vector2 pos = Pos(WORLD);

	mRenderRect.x = pos.x;
	mRenderRect.y = pos.y;

	mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(WORLD));
}

void Trainer::Update() {

}

void Trainer::conversation() {

	mText = Text::Instance();

}

void Trainer::BattleFunction() {
	if (WinBattle) {
		mText->displayTextBox("WinText");
	}
	else
		mText->displayTextBox("LoseText");
}
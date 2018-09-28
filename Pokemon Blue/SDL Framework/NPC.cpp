#include "NPC.h"

NPC::NPC() :
	AnimatedTexture("NPC#1.png", 0, 0, 32, 32, 1, 1.0f, HORIZONTAL)
{
	pNPCText = Text::Instance();
	
	//conversation = 
}

NPC::~NPC() {

}

void NPC::Update() {

}

void NPC::Render() {
	Vector2 pos = Pos(WORLD);

	mRenderRect.x = pos.x;
	mRenderRect.y = pos.y;

	mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(WORLD));
}
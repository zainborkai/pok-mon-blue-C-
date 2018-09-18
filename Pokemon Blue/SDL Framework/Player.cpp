#include "Player.h"


Player::Player() :
	AnimatedTexture("PlayerSpriteSheet.png", 0, 0, 32, 32, 2, .5f, HORIZONTAL) {
	Pos(Vector2(100, 100));
	playerInput = InputManager::Instance();
	
}

void Player::Update() {
	//Translate(Vector2(-.1f, -.1f));
	AnimatedTexture::Update();
	if (!mAnimationDone) {
		mAnimationTimer += mTimer->DeltaTime();
		if (mAnimationTimer >= mAnimationSpeed) {
			//Only loop if the wrap mode is LOOP
			if (mWrapMode == LOOP) {
				mAnimationTimer -= mAnimationSpeed;
			}
			else {
				mAnimationDone = true;
				mAnimationTimer = mAnimationSpeed - mTimePerFrame;
			}
		}
		// Change mStart to make cuts
		if (mAnimationDirection == HORIZONTAL) {
			mClipRect.x = mStartX + (int)(mAnimationTimer / mTimePerFrame) * mWidth;
		}
		else {
			mClipRect.y = mStartY + (int)(mAnimationTimer / mTimePerFrame) * mHeight;
		}
	}
}

void Player::Render() {
	Vector2 pos = Pos(WORLD);
	Vector2 scale = Scale(WORLD);

	mRenderRect.x = pos.x;
	mRenderRect.y = pos.y;

	//mRenderRect.x = (int)(pos.x - mWidth * scale.x * 0.5f);
	//mRenderRect.y = (int)(pos.y - mWidth * scale.y * 0.5f);

	// Scales the width and height according to the scale of the GameEntity
	//mRenderRect.w - (int)(mWidth * scale.x);
	//mRenderRect.h - (int)(mHeight * scale.y);

	mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(WORLD));
}

void Player::Move() {

	if (playerInput->KeyDown(SDL_SCANCODE_W)) {
		// Move up..
		std::cout << "Moving up" << std::endl;
	}
	else if (playerInput->KeyDown(SDL_SCANCODE_S)) {
		// Move down..
	}
	else if (playerInput->KeyDown(SDL_SCANCODE_A)) {
		// Move left..
	}
	else if (playerInput->KeyDown(SDL_SCANCODE_D)) {
		// Move right..
	}
}

Player::~Player() {}
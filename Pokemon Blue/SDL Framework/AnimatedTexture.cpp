
#include "AnimatedTexture.h"

AnimatedTexture::AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir) :
	Texture(filename, x, y, w, h) {

	mTimer = Timer::Instance();
}

AnimatedTexture::AnimatedTexture(std::string filename, int x, int y, int w, int h) :
	Texture(filename, x, y, w, h) {

	mTimer = Timer::Instance();
}

AnimatedTexture::~AnimatedTexture() {}

void AnimatedTexture::AnimData::WrapMode(WRAP_MODE mode) {
	mWrapMode = mode;
}

void AnimatedTexture::Update() {
	if (data != nullptr) {
		data->Run(mTimer->DeltaTime());
		if (!data->mAnimationDone) {
			if (data->mAnimationDirection == HORIZONTAL) {
				mClipRect.x = data->mStartX + (int)(data->mAnimationTimer / data->mTimePerFrame) * mWidth;
			}
			else {
				mClipRect.y = data->mStartY + (int)(data->mAnimationTimer / data->mTimePerFrame) * mHeight;
			}
		}
	}
}

AnimatedTexture::AnimData::AnimData(int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir) {
	mStartX = x;
	mStartY = y;

	mFrameCount = frameCount;
	mAnimationSpeed = animationSpeed;
	mTimePerFrame = mAnimationSpeed / mFrameCount;
	mAnimationTimer = 0.0f;

	mAnimationDirection = animationDir;
	mAnimationDone = false;
	mWrapMode = LOOP;

}

void AnimatedTexture::AnimData::Run(float deltaTime) {
	if (!mAnimationDone) {
		mAnimationTimer += deltaTime;

		if (mAnimationTimer >= mAnimationSpeed) {
			if (mWrapMode == LOOP) {
				mAnimationTimer -= mAnimationSpeed;
			}
			else {
				mAnimationDone = true;
				mAnimationTimer = mAnimationSpeed - mTimePerFrame;
			}
		}

		if (mAnimationDirection == HORIZONTAL) {
			//mClipRect.x = mStartX + (int)(mAnimationTimer / mTimePerFrame) * mWidth;
		}
		else {
			//mClipRect.y = mStartY + (int)(mAnimationTimer / mTimePerFrame) * mHeight;
		}
	}
}

void AnimatedTexture::AssignData(AnimData* thisdata) {
	data = thisdata;
}

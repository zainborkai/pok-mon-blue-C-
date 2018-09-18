#ifndef ANIMATEDTEXTURE_H
#define ANIMATEDTEXTURE_H

#include "Timer.h"
#include "Texture.h"


class AnimatedTexture : public Texture {
public:
	enum WRAP_MODE { ONCE = 0, LOOP = 1 };
	enum ANIM_DIR { HORIZONTAL = 0, VERTICAL = 1};

private:
	Timer* mTimer;
	int mStartX;
	int mStartY;

	float mAnimationTimer;
	float mAnimationSpeed;
	float mTimePerFrame;
	int mFrameCount;

	WRAP_MODE mWrapMode;
	ANIM_DIR mAnimationDirection;
	bool mAnimationDone;

public:
	// Loads a texture from a file (relative to the exe path)
	// Supports spritesheets
	// x - Starting pixel's X on spritesheet
	// y - Starting pixel's Y on spritesheet
	// w - The width of the clipped sprite
	// h - The height of the clipped sprite
	// frameCount - The number of frames in the animation
	// animationSpeed - How long it takes to run the animation in seconds
	// animationDirection - How the animation sprites are arranged in the spritesheet

	AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir);
	~AnimatedTexture();

	void WrapMode(WRAP_MODE mode);

	void Update();
};



#endif
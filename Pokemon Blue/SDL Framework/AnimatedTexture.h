#ifndef ANIMATEDTEXTURE_H
#define ANIMATEDTEXTURE_H

#include "Timer.h"
#include "Texture.h"

class AnimatedTexture : public Texture {
public:
	enum WRAP_MODE { ONCE = 0, LOOP = 1 };
	enum ANIM_DIR { HORIZONTAL = 0, VERTICAL = 1 };
	class AnimData {
	public:
		AnimData(int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir);

		void WrapMode(WRAP_MODE mode);
		void Run(float deltaTime);

		int mStartX;
		int mStartY;

		float mAnimationTimer;
		bool mAnimationDone;
		float mAnimationSpeed;
		float mTimePerFrame;
		int mFrameCount;

		WRAP_MODE mWrapMode;
		ANIM_DIR mAnimationDirection;
	};

private:
	Timer* mTimer;
	AnimData* data;

public:
	//Loads a texture from file (relative to the exe path)
	//Supports spritesheets
	//x - Starting pixel's X on the spritesheet
	//y - Starting pixel's Y on the spritesheet
	//w - The width of the clipped sprite
	//h - The height of the clipped sprte
	//frameCount - The number of frames in the animation
	//animationSpeed - how long it takes to run the animation in seconds
	//animationDirection - How the animation sprites are arranged in the spritesheet
	AnimatedTexture(std::string filename, int x, int y, int w, int h, int frameCount, float animationSpeed, ANIM_DIR animationDir);
	AnimatedTexture() {};
	AnimatedTexture(std::string filename, int x, int y, int w, int h);
	~AnimatedTexture();

	void Update();

	void AssignData(int _x, int _y, int _w, int _h, int _frameCount, float _animSpeed, ANIM_DIR _animDir) {
		AssignData(new AnimData(_x, _y, _w, _h, _frameCount, _animSpeed, _animDir));
	}
	void AssignData(AnimData* data);
	AnimData* GetData() { return data; }
};

#endif

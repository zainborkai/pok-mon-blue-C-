#ifndef TEXTURE_H
#define TEXTURE_H

#include "GameEntity.h"
#include "AssetManager.h"


class Texture : public GameEntity {
protected: 
	// The SDL_Texture to be rendered
	SDL_Texture* mTex;

	// Used to render the texture
	Graphics* mGraphics;

	// Width of the texture
	int mWidth;

	// Height of the texture
	int mHeight;

	// True if the texture is loaded from a spritesheet
	bool mClipped;

	// Is used to render the texture on the screen
	SDL_Rect mRenderRect;

	// Is used to clip the texture from a spritesheet
	SDL_Rect mClipRect;

public:
	SDL_Rect GetRenderRect() { return mRenderRect; }
	int GetmWidth() { return mWidth; }
	int GetmHeight() { return mHeight; }
	int GetCenteringX() { return centering.x; }
	int GetCenteringY() { return centering.y; }

	void SetRenderRectX(int x) { mRenderRect.x = x; }
	void SetRenderRectY(int y) { mRenderRect.y = y; }
	void SetRenderRectW(int w) { mRenderRect.w = w; }
	void SetRenderRectH(int h) { mRenderRect.h = h; }
	void SetCenteringX(int cx) {  centering.x = cx; }
	void SetCenteringY(int cy) {  centering.y = cy; }
	// Loads a whole texture from a file
	Texture(std::string filename);
	SDL_Texture* GetmTex() { return mTex; }
	// Loads a texture from a file (spritesheets)
	// x = Starting pixel's X on the spritesheet
	// y = Starting pixel's Y on the spritesheet
	// w = The width of the clipped sprite
	// h = The height of the clipped sprite
	Texture(std::string filename, int x, int y, int w, int h);

	// Converts the given text into a texture (Constructor)
	Texture(std::string text, std::string fontpath, int size, SDL_Color colour);
	~Texture();

	// Called to render the texture to screen
	virtual void Render();

	Vector2 centering;
};


#endif
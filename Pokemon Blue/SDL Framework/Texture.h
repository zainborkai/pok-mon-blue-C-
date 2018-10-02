#ifndef TEXTURE_H
#define TEXTURE_H

#include "GameEntity.h"
#include "AssetManager.h"

class Texture : public GameEntity {
protected:
	//The SDL_Texture to be rendered
	SDL_Texture* mTex; //control mTex to display something on screen

	//Used to render the texture
	Graphics* mGraphics;

	//Width of the texture
	int mWidth;

	//Height of the texture

	int mHeight;
	Vector2 centering;

	//true if the texture is loaded from a spritesheet
	bool mClipped;

	//Is used to render the texture on the screen
	SDL_Rect mRenderRect;

	//Is used to clip the texture from a spritesheet

	SDL_Rect mClipRect;

public:
	//Loads a whole texture from a file
	Texture(std::string filename);
	SDL_Texture* GetmTex() { return mTex; }
	SDL_Rect GetmRenderRect() { return mRenderRect; }
	void SetmTex(SDL_Texture* texture) { mTex = texture; }
	void SetmRenderRectX(float x) { mRenderRect.x = x; }
	void SetmRenderRectY(float y) { mRenderRect.y = y; }
	//Loads a texture from a file (spritesheets)
	//x = starting pixel's X on the spritesheet
	//y = starting pixel's Y on the spritesheet
	//w = The width of the clipped sprite
	//h = The heigh of the clipped sprite
	Texture(std::string filename, int x, int y, int w, int h);

	//Converts the given text into a texture
	Texture(std::string text, std::string fontpath, int size, SDL_Color color);
	~Texture();

	//Called to render the texture to screen
	virtual void Render();

	Texture() {};

	void AssignTexture(std::string filename);
	void AssignTexture(std::string filename, int x, int y, int w, int h);
	void AssignTexture(std::string text, std::string fontpath, int size, SDL_Color colour);
	void SetCenter(int x, int y);

};

#endif // !TEXTURE_H


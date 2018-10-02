#ifndef TEXTURE_H
#define TEXTURE_H

#include "GameEntity.h"
#include "AssetManager.h"


class Texture : public GameEntity {
protected:
	SDL_Texture * mTex;


	Graphics* mGraphics;


	int mWidth;
	int mHeight;
	Vector2 centering;


	bool mClipped;

	SDL_Rect mRenderRect;


	SDL_Rect mClipRect;


public:
	Texture(std::string filename);
	Texture(std::string filename, int x, int y, int w, int h);
	Texture(std::string text, std::string fontpath, int size, SDL_Color colour);
	~Texture();


	virtual void Render();
	void AssignTexture(std::string filename);
	void AssignTexture(std::string filename, int x, int y, int w, int h);
	void AssignTexture(std::string text, std::string fontpath, int size, SDL_Color colour);
	void SetCenter(int x, int y);
};


#endif

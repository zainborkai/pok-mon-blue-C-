
#include "Texture.h"


Texture::Texture(std::string filename) {
	mGraphics = Graphics::Instance();
	//
	AssignTexture(filename);

	mGraphics = Graphics::Instance();

	//Loads the texture from AssetManager to avoid loading textures more than once
	mTex = AssetManager::Instance()->GetTexture(filename);

	//Gets the width and height of the texture
	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mClipped = false;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}


Texture::Texture(std::string filename, int x, int y, int w, int h) {
	mGraphics = Graphics::Instance();

	AssignTexture(filename, x, y, w, h);
	mGraphics = Graphics::Instance();

	mTex = AssetManager::Instance()->GetTexture(filename);

	mClipped = true;

	mWidth = w;
	mHeight = h;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	mClipRect.x = x;
	mClipRect.y = y;
	mClipRect.w = mWidth;
	mClipRect.h = mHeight;
}



Texture::Texture(std::string text, std::string fontPath, int size, SDL_Color colour) {
	mGraphics = Graphics::Instance();
	mTex = AssetManager::Instance()->GetText(text, fontPath, size, colour);

	mClipped = false;

	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;
}

Texture::~Texture() {
	mTex = nullptr;
	mGraphics = nullptr;
}

void Texture::AssignTexture(std::string filename) {
	if (filename.size() == 0) { filename = "nulltexture.png"; }
	
	mTex = AssetManager::Instance()->GetTexture(filename);


	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mClipped = false;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	centering = Vector2(0.0f, 0.0f);
}

void Texture::AssignTexture(std::string filename, int x, int y, int w, int h) {
	if (filename.size() == 0) { filename = "nulltexture.png"; }
	
	mTex = AssetManager::Instance()->GetTexture(filename);

	mClipped = true;

	mWidth = w;
	mHeight = h;


	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	centering = Vector2(0.0f, 0.0f);


	mClipRect.x = x;
	mClipRect.y = y;
	mClipRect.w = mWidth;
	mClipRect.h = mHeight;
}


void Texture::AssignTexture(std::string text, std::string fontPath, int size, SDL_Color colour) {
	mGraphics = Graphics::Instance();
	mTex = AssetManager::Instance()->GetText(text, fontPath, size, colour);


	mClipped = false;

	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	centering = Vector2(0.0f, 0.0f);
}

void Texture::Render() {
	Vector2 pos = Pos(WORLD)*Graphics::GameScale;
	Vector2 scale = Scale(WORLD)*Graphics::GameScale;

	mRenderRect.x = (int)(pos.x - mWidth * scale.x * centering.x);
	mRenderRect.y = (int)(pos.y - mHeight * scale.y * centering.y);

	mRenderRect.w = (int)(mWidth * scale.x);
	mRenderRect.h = (int)(mHeight * scale.y);

	mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(WORLD));
}

void Texture::SetCenter(int x, int y) {
	centering = Vector2(x, y);
}


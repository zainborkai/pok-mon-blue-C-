#include "Texture.h"

Texture::Texture(std::string filename) {
	mGraphics = Graphics::Instance();

	// Loads the texture from AssetManager to avoid loading textures more than once
	mTex = AssetManager::Instance()->GetTexture(filename);

	// Gets the Width and Height of the texture
	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mClipped = false;

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	centering = Vector2(0.5f, 0.5f);
	
}

Texture::Texture(std::string filename, int x, int y, int w, int h) {
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

	centering = Vector2(0.5f, 0.5f);

}

Texture::Texture(std::string text, std::string fontPath, int size, SDL_Color colour) {
	mGraphics = Graphics::Instance();

	mTex = AssetManager::Instance()->GetText(text, fontPath, size, colour);

	mClipped = false;
	SDL_QueryTexture(mTex, NULL, NULL, &mWidth, &mHeight);

	mRenderRect.w = mWidth;
	mRenderRect.h = mHeight;

	centering = Vector2(0.5f, 0.5f);
}

Texture::~Texture() {
	mTex = nullptr;
	mGraphics = nullptr;
}

void Texture::Render() {
	Vector2 pos = Pos(WORLD);
	Vector2 scale = Scale(WORLD);

	// Centers the texture on the texture's world position so that its position is not the top left
	mRenderRect.x = (int)(pos.x - mWidth * scale.x * centering.x);
	mRenderRect.y = (int)(pos.y - mWidth * scale.y * centering.y);

	// Scales the width and height according to the scale of the GameEntity
	mRenderRect.w = (int)(mWidth * scale.x);
	mRenderRect.h = (int)(mHeight * scale.y);

	mGraphics->DrawTexture(mTex, (mClipped) ? &mClipRect : NULL, &mRenderRect, Rotation(WORLD));

}
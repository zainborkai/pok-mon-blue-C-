#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "MathHelper.h"

class Graphics {
public:
	const int SCREEN_WIDTH = 160; // 160; // 800
	const int SCREEN_HEIGHT = 144; // 144; // 600
	const char* WINDOW_TITLE = "SDL2.0";

	static const Vector2 GameScale;
	static Vector2 GamePos;

private:
	static Graphics *sInstance;
	static bool sInitialized;

	SDL_Window* mWindow;


	SDL_Renderer* mRenderer;

public:
	static Graphics* Instance();
	static void Release();
	static bool Initialized();

	SDL_Texture* LoadTexture(std::string path);

	SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);

	void DrawTexture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void ClearBackBuffer();
	void Render();


private:
	Graphics();
	~Graphics();
	bool Init();
};



#endif
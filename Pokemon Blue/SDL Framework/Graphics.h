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
	const int SCREEN_WIDTH = 800; // 160; // 800
	const int SCREEN_HEIGHT = 600; // 144; // 600
	const char* WINDOW_TITLE = "SDL2.0";

	static const Vector2 GameScale;

private:
	static Graphics *sInstance;
	static bool sInitialized;

	//window create using SDL
	SDL_Window* mWindow;

	//renderer used to render all textures
	SDL_Renderer* mRenderer;

public:
	static Graphics* Instance();
	static void Release();
	static bool Initialized();

	//Load a texture from a file using the given path
	SDL_Texture* LoadTexture(std::string path);

	//Render a texture from using the given font and text
	SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);

	//clear all the rendered textures fro the bank buffer

	void DrawTexture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL, float angle = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void ClearBackBuffer();
	void Render();

private:
	Graphics();
	~Graphics();
	bool Init();
};

#endif
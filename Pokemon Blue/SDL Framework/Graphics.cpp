
#include "Graphics.h"


Graphics* Graphics::sInstance = NULL;
bool Graphics::sInitialized = false;

const Vector2 Graphics::GameScale = Vector2(4, 4);
Vector2 Graphics::GamePos = Vector2(0, 0);

Graphics* Graphics::Instance() {
	if (sInstance == NULL) {
		sInstance = new Graphics();
	}

	return sInstance;
}

void Graphics::Release() {
	delete sInstance;
	sInstance = nullptr;
	sInitialized = false;
}

bool Graphics::Initialized() {
	return sInitialized;
}

Graphics::Graphics() {
	sInitialized = Init();
}

Graphics::~Graphics() {
	SDL_DestroyWindow(mWindow);
	mWindow = nullptr;

	SDL_DestroyRenderer(mRenderer);
	mRenderer = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool Graphics::Init() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		std::printf("Window Creation Error: %s\n", SDL_GetError());
		return false;
	}
	

	mWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH*GameScale.x, SCREEN_HEIGHT*GameScale.y, SDL_WINDOW_SHOWN);
	//
	if (mWindow == NULL) {
		std::printf("Window Creation Error: %s\n", SDL_GetError());
		return false;
	}


	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	//
	if (mRenderer == NULL) {
		std::printf("Renderer Creation Error: %s\n", SDL_GetError());
		return false;
	}


	SDL_SetRenderDrawColor(mRenderer, 0xFF, 0xFF, 0xFF, 0xFF);


	int flags = IMG_INIT_PNG; // IMG_INIT_JPG
	if (!(IMG_Init(flags) & flags)) {
		std::printf("IMG Initialization Error: %s\n", IMG_GetError());
		return false;
	}


	return true;
}


SDL_Texture* Graphics::LoadTexture(std::string path) {
	SDL_Texture* tex = nullptr;

	SDL_Surface* surface = IMG_Load(path.c_str());

	if (surface == nullptr) {
		std::printf("Image Load Error: Path (%s) - Error(%s)", path.c_str(), IMG_GetError());
		return nullptr;
	}


	tex = SDL_CreateTextureFromSurface(mRenderer, surface);

	if (tex == nullptr) {
		std::printf("Create Texture Error: %s\n", SDL_GetError());
		return nullptr;
	}


	SDL_FreeSurface(surface);


	return tex;
}



SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color) {
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);

	if (surface == nullptr) {
		std::printf("Text Render Error: %s\n", TTF_GetError());
		return nullptr;
	}


	SDL_Texture* tex = SDL_CreateTextureFromSurface(mRenderer, surface);

	if (tex == nullptr) {
		std::printf("Text Texture Creation Error: %s\n", SDL_GetError());
		return nullptr;
	}


	SDL_FreeSurface(surface);


	return tex;
}


void Graphics::ClearBackBuffer() {
	SDL_RenderClear(mRenderer);
}

void Graphics::DrawTexture(SDL_Texture* tex, SDL_Rect* clip, SDL_Rect* rend, float angle, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(mRenderer, tex, clip, rend, angle, NULL, flip);
}

void Graphics::Render() {
	SDL_RenderPresent(mRenderer);
}

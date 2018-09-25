#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <SDL_mixer.h>
#include "Graphics.h"

class AssetManager {
private:
	static AssetManager* sInstance;

	//Used to cache all loaded images
	std::map<std::string, SDL_Texture*> mTexture;
	std::map<std::string, SDL_Texture*> mText;
	std::map<std::string, TTF_Font*> mFonts;
	std::map<std::string, Mix_Music*> mMusic;
	std::map<std::string, Mix_Chunk*> mSFX;

public:
	static AssetManager* Instance();
	static void Release();

	SDL_Texture* GetTexture(std::string filename); // Used when any texture needs to be loaded from a file

	SDL_Texture* GetText(std::string text, std::string filename, int size, SDL_Color color); // Used to load text

	Mix_Music* GetMusic(std::string filename); // Used for loading music

	Mix_Chunk* GetSFX(std::string filename); // Used for loading sound effects

private:
	AssetManager();
	~AssetManager();

	TTF_Font* GetFont(std::string filename, int size);
};

#endif


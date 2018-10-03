#include "AssetManager.h"

AssetManager* AssetManager::sInstance = nullptr;

AssetManager* AssetManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new AssetManager();
	}

	return sInstance;
}

void AssetManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

AssetManager::AssetManager() {}

AssetManager::~AssetManager() {
	// Freeing all load textures
	for (auto tex : mTextures) {
		if (tex.second != NULL) {
			SDL_DestroyTexture(tex.second);
		}
	}

	mTextures.clear();

	// Freeing all rendered text
	for (auto text : mText) {
		if (text.second != NULL) {
			SDL_DestroyTexture(text.second);
		}
	}

	mFonts.clear();

	// Freeing all loaded music
	for (auto music : mMusic) {
		if (music.second != NULL) {
			Mix_FreeMusic(music.second);
		}
	}

	mMusic.clear();

	// Freeing all loaded sound effects
	for (auto sfx : mSFX) {
		if (sfx.second != NULL) {
			Mix_FreeChunk(sfx.second);
		}
	}

	mSFX.clear();
}

SDL_Texture* AssetManager::GetTexture(std::string filename) {
	// Get the full path / base directory of the file
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);

	// If the file has not been already loaded
	if (mTextures[fullPath] == nullptr) {
		mTextures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);
	}

	return mTextures[fullPath];
}

TTF_Font* AssetManager::GetFont(std::string filename, int size) {
	// Get the full path of font
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);

	// Key takes into account the size of the font as well as the same font that can be
	// opened with different sizes.
	std::string key = fullPath + (char)size;

	if (mFonts[key] == nullptr) {
		mFonts[key] = TTF_OpenFont(fullPath.c_str(), size);

		if (mFonts[key] == nullptr) {
			std::printf("Font Loading Error: Font-%s Error-%s", filename.c_str(), TTF_GetError());
		}
	}

	return mFonts[key];
}

SDL_Texture* AssetManager::GetText(std::string text, std::string filename, int size, SDL_Color colour) {
	// Get the font from the font cache
	TTF_Font* font = GetFont(filename, size);

	std::string key = text + filename + (char)size + (char)colour.r + (char)colour.b + (char)colour.g;

	if (mText[key] == nullptr) {
		mText[key] = Graphics::Instance()->CreateTextTexture(font, text, colour);
	}

	return mText[key];
}

Mix_Music* AssetManager::GetMusic(std::string filename) {
	// Get the full path of the WAV file
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);

	if (mMusic[fullPath] == nullptr) {
		mMusic[fullPath] = Mix_LoadMUS(fullPath.c_str());

		if (mMusic[fullPath] == NULL) {
			std::printf("Music Loading Error: File-%s Error-%s", filename.c_str(), Mix_GetError());
		}
	}

	return mMusic[fullPath];
}

Mix_Chunk* AssetManager::GetSFX(std::string filename) {
	// Get the full path of the WAV file
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/" + filename);

	if (mSFX[fullPath] == nullptr) {
		mSFX[fullPath] = Mix_LoadWAV(fullPath.c_str());

		if (mSFX[fullPath] == NULL) {
			std::printf("SFX Loading Error: File-%s Error-%s", filename.c_str(), Mix_GetError());
		}
	}

	return mSFX[fullPath];
}
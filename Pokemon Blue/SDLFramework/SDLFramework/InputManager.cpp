#include <string.h>
#include "InputManager.h"

InputManager* InputManager::sInstance = nullptr;

InputManager* InputManager::Instance() {
	if (sInstance == nullptr) {
		sInstance = new InputManager();
	}

	return sInstance;
}

void InputManager::Release() {
	delete sInstance;
	sInstance = nullptr;
}

InputManager::InputManager() {
	mKeyboardState = SDL_GetKeyboardState(&mKeyLength);
	mPrevKeyBoardState = new Uint8[mKeyLength];
	memcpy(mPrevKeyBoardState, mKeyboardState, mKeyLength);
}

InputManager::~InputManager() {
	delete[] mPrevKeyBoardState;
	mPrevKeyBoardState = NULL;
}

bool InputManager::KeyDown(SDL_Scancode scanCode) {
	return (mKeyboardState[scanCode] != 0);
}

bool InputManager::KeyPressed(SDL_Scancode scanCode) {
	return (mPrevKeyBoardState[scanCode]) == 0 && (mKeyboardState[scanCode] != 0);
}

bool InputManager::KeyReleased(SDL_Scancode scanCode) {
	return (mPrevKeyBoardState[scanCode] != 0) && (mKeyboardState[scanCode] == 0);
}

void InputManager::UpdatePrevInput() {
	memcpy(mPrevKeyBoardState, mKeyboardState, mKeyLength);
}
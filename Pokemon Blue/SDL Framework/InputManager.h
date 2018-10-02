#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>
#include "MathHelper.h"

class InputManager {
private:
	static InputManager* sInstance;

	Uint8* mPrevKeyBoardState;

	const Uint8* mKeyboardState;

	int mKeyLength;

public:
	static InputManager* Instance();
	static void Release();

	bool KeyDown(SDL_Scancode scanCode);
	bool KeyPressed(SDL_Scancode scanCode);
	bool KeyReleased(SDL_Scancode scanCode);

	void UpdatePrevInput();

private:
	InputManager();
	~InputManager();
};


#endif

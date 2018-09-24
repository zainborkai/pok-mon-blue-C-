#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <SDL.h>
#include "MathHelper.h"

class InputManager {
private:
	static InputManager* sInstance;

	//Holds the keyboard key state of the last frame
	Uint8* mPrevKeyBoardState;

	//Holds the keyboard key state of the current frame
	const Uint8* mKeyboardState;

	//The number of keys in the mKeyboardState array
	int mKeyLength;

public:
	static InputManager* Instance();
	static void Release();

	bool KeyDown(SDL_Scancode scaneCode);
	bool KeyPressed(SDL_Scancode scanCode);
	bool KeyReleased(SDL_Scancode scanCode);

	void UpdatePrevInput();

private:
	InputManager();
	~InputManager();
};

#endif // !INPUTMANAGER_H


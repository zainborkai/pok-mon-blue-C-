#ifndef BATTLESCREEN_H
#define BATTLESCREEN_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include <iostream>


class BattleScreen : public Texture {
public:

	void Update();
	// void Render();

	BattleScreen();
	~BattleScreen();

	int X = 0;
	int Y = 0;


};


#endif
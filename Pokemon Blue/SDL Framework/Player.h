#ifndef PLAYER_H
#define PLAYER_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include <iostream>


class Player : AnimatedTexture {
public:
	void Move();

	void Update();
	void Render();

	Player();
	~Player();

	InputManager* playerInput;

};


#endif
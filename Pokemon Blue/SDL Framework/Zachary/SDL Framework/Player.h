#ifndef PLAYER_H
#define PLAYER_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include <iostream>


class Player : public AnimatedTexture {
public:
	int Move();
	void MovePlayer();

	void Update();
	// void Render();

	Player();
	~Player();

	int X = 0;
	int Y = 0;


	InputManager* playerInput;

};


#endif
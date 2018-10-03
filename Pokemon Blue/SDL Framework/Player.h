#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "AnimatedTexture.h"
#include "InputManager.h"
#include <iostream>
#include <algorithm>


class Player : public Actor {
public:
	void Move();
	void MovePlayer();

	void Update();
	void Render();

	Player();
	~Player();

	int X = 0;
	int Y = 0;
	int shiftingX = 0;
	int shiftingY = 0;
	float shift = 0.0f;


	InputManager* playerInput;

};


#endif
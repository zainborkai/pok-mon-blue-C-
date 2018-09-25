#ifndef PLAYER_H
#define PLAYER_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include <iostream>
#include <string>


class Player : public AnimatedTexture {
public:
	int Move();
	void Update();
	void Render();

	Player();
	~Player();

	float GetX() { return X; }
	float GetY() { return Y; }

private:
	
	float X;
	float Y;


	InputManager* playerInput;

};


#endif


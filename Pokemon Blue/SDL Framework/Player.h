#ifndef PLAYER_H
#define PLAYER_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include <iostream>
#include <string>
#include "Inventory.h"

class Player : public AnimatedTexture {
public:
	
	int Move();
	void Update();
	void Render();

	Player();
	~Player();

	int GetX() { return X; }
	int GetY() { return Y; }

	void SetX(int x) { X = x; }
	void SetY(int y) { Y = y; }

	//void NPCinteraction();
	


private:
	
	float X;
	float Y;


	InputManager* playerInput;

};

#endif


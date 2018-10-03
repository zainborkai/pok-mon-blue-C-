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
	void playerState();

	Player();
	~Player();

	float GetX() { return X; }
	float GetY() { return Y; }
	bool getTextbox() { return textbox; }
	void NPCinteraction();
	void battling();
	void walking();
	enum player_State {
		Talking,
		Battling,
		Walking,
	};

private:
	
	float X;
	float Y;
	bool textbox;
	bool battle;

	InputManager* playerInput;

};

#endif


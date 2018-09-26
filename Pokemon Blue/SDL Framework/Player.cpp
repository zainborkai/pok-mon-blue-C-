#include "Player.h"


Player::Player() :
	AnimatedTexture("pokemon_player_spritesheet.png", 0, 0, 16, 16, 3, .5f, HORIZONTAL) {
	centering = Vector2(0, 0);
	playerInput = InputManager::Instance();

	X = 60;
	Y = 186;
	
}

void Player::Update() {
	//Translate(Vector2(-.1f, -.1f));
	AnimatedTexture::Update();
}

int Player::Move() {
	int output = 0;
	if (playerInput->KeyPressed(SDL_SCANCODE_W)) {
		// Move up..
		mStartY = 48;
		std::cout << "Moving up" << std::endl;

		output = 1;
	}
	else if (playerInput->KeyPressed(SDL_SCANCODE_S)) {
		// Move down..
		mStartY = 0;
		std::cout << "Moving down" << std::endl;

		output = 2;
	}
	else if (playerInput->KeyPressed(SDL_SCANCODE_A)) {
		// Move left..
		mStartY = 16;
		std::cout << "Moving left" << std::endl;

		output = 3;
	}
	else if (playerInput->KeyPressed(SDL_SCANCODE_D)) {
		// Move right..
		mStartY = 32;
		std::cout << "Moving right" << std::endl;

		output = 4;
	}
	//
	mClipRect.y = mStartY;
	if (output == 0) {
		mAnimationTimer = 0;
	}
	//
	return output;
}

void Player::MovePlayer() {
}


Player::~Player() {}
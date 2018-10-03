#include "Player.h"


Player::Player() :
	AnimatedTexture("pokemon_player_spritesheet.png", 0, 0, 16, 16, 3, 0.05f, HORIZONTAL) {
	centering = Vector2(0, 0);
	playerInput = InputManager::Instance();
	mWrapMode = LOOP;
	//mAnimationSpeed = 0.01;
	X = 60;
	Y = 186;
	//X = 0;
	//Y = 0;

}

void Player::Update() {
	//Translate(Vector2(-.1f, -.1f));
	AnimatedTexture::Update();
	SDL_WaitEventTimeout(NULL, 200);

}

int Player::Move() {
	//mAnimationTimer = 0.01f;
	int output = 0;
	if (playerInput->KeyDown(SDL_SCANCODE_W)) {
		// Move up..
		mStartY = 48;
		std::cout << "Moving up" << std::endl;
		//SDL_WaitEventTimeout(NULL, 100);

		output = 1;
	}
	else if (playerInput->KeyDown(SDL_SCANCODE_S)) {
		// Move down..
		mStartY = 0;
		std::cout << "Moving down" << std::endl;
		//mAnimationTimer = 30;
		//SDL_WaitEventTimeout(NULL, 100);

		output = 2;
	}
	else if (playerInput->KeyDown(SDL_SCANCODE_A)) {
		// Move left..
		mStartY = 16;
		std::cout << "Moving left" << std::endl;
		//SDL_WaitEventTimeout(NULL, 100);

		output = 3;
	}
	else if (playerInput->KeyDown(SDL_SCANCODE_D)) {
		// Move right..
		mStartY = 32;
		std::cout << "Moving right" << std::endl;
		//SDL_WaitEventTimeout(NULL, 100);

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
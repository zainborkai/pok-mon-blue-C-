
#include "Player.h"

Player::Player() : Actor() {
	AssignTexture("pokemon_player_spritesheet.png", 0, 0, 16, 16);
	AssignData(0, 0, 16, 16, 3, .8f, HORIZONTAL);

	centering = Vector2(0, 0.25f);
	playerInput = InputManager::Instance();

	X = 63;
	Y = 186;
}

void Player::Update() {
	//Translate(Vector2(-.1f, -.1f));
	AnimatedTexture::Update();
}

void Player::Render() {
	Actor::Render();
}

void Player::Move() {
	// *** "Here's a little bonus something from me Zachary. Tired of not seeing this work." ~ Khori
	if (shiftingX == 0 && shiftingY == 0) {
		GetData()->mAnimationTimer = 0;
		//
		if (playerInput->KeyDown(SDL_SCANCODE_W)) {
			// Move up..
			GetData()->mStartY = 48;
			std::cout << "Moving up" << std::endl;

			shiftingX = 0;
			shiftingY = -1;
		}
		else if (playerInput->KeyDown(SDL_SCANCODE_S)) {
			// Move down..
			GetData()->mStartY = 0;
			std::cout << "Moving down" << std::endl;

			shiftingX = 0;
			shiftingY = 1;
		}
		else if (playerInput->KeyDown(SDL_SCANCODE_A)) {
			// Move left..
			GetData()->mStartY = 16;
			std::cout << "Moving left" << std::endl;

			shiftingX = -1;
			shiftingY = 0;
		}
		else if (playerInput->KeyDown(SDL_SCANCODE_D)) {
			// Move right..
			GetData()->mStartY = 32;
			std::cout << "Moving right" << std::endl;

			shiftingX = 1;
			shiftingY = 0;
		}
		//
		if ((X+shiftingX <= 0) || (X + shiftingX > 88 - 1)) { // ??? <-- NO MAGIC NUMBERS!
			shiftingX = 0;
		}

		if ((Y + shiftingY <= 0) || (Y + shiftingY > 198 - 1)) { // ??? <-- NO MAGIC NUMBERS!
			shiftingY = 0;
		}
	}
	else {
		shift = shift + (4.0f / 120); // *** 4 steps per second. // ??? <-- ... BUT IT USES MAGIC NUMBERS! 120 is the frame rate!
		//
		if (shift >= 1.0f) {
			X += shiftingX;
			Y += shiftingY;
			//
			shiftingX = 0;
			shiftingY = 0;
			shift = 0;
		}
	}
	//
	mClipRect.y = GetData()->mStartY;
}

void Player::MovePlayer() {
}


Player::~Player() {}
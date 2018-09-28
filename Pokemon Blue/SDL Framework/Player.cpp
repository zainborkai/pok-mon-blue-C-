#include "Player.h"


Player::Player() :
	AnimatedTexture("pokemon_player_spritesheet.png", 0, 0, 16, 16, 3, .5f, HORIZONTAL) {
	centering = Vector2(0, 0);
	playerInput = InputManager::Instance();

	X = 63;
	Y = 186;
	
}

/*void Player::NPCinteraction() {
	int player;
	std::string text;
	bool isActive = true;
	//create a staement to prompt interaction with npc
	bool inFront = true;

	//display text
}*/



void Player::Update() {
	//Translate(Vector2(-.1f, -.1f));
	AnimatedTexture::Update();
}

//movements of the player (assigning keys)
int slowtime = 30;
int Player::Move() {
	int output = 0;
	if (slowtime > 0) { 
		--slowtime;
		return 0;
	}
	slowtime = 30;

	

	if (playerInput->KeyDown(SDL_SCANCODE_W)) {
		// Move up..
		mStartY = 48;
	
		Y -= 1;
		
		std::cout << "Moving up" << std::endl;

		output = 1;
	}
	else if (playerInput->KeyDown(SDL_SCANCODE_S)) {
		// Move down..
		mStartY = 0;
		Y += 1;
		std::cout << "Moving down" << std::endl;

		output = 2;
	}
	else if (playerInput->KeyDown(SDL_SCANCODE_A)) {
		// Move left..
		mStartY = 16;
		X -= 1;
		std::cout << "Moving left" << std::endl;

		output = 3;
	}
	else if (playerInput->KeyDown(SDL_SCANCODE_D)) {
		// Move right..
		mStartY = 32;
		std::cout << "Moving right" << std::endl;
		X += 1;
		output = 4;
	}
	//
	if (X <= 0) {
		X = 0;
	}
	else if (X > 88 - 1) { // ??? <-- NO MAGIC NUMBERS!
		X = 88 - 1;
	}

	if (Y <= 0) {
		Y = 0;
	}
	else if (Y > 198 - 1) { // ??? <-- NO MAGIC NUMBERS!
		Y = 198 - 1;
	}
	//
	mClipRect.y = mStartY;
	if (output == 0) {
		mAnimationTimer = 0;
	}
	//
	return output;
}

 
void Player::Render() {
	Vector2 pos = Pos(WORLD);
	Vector2 scale = Scale(WORLD);

	this->mRenderRect.x = (int)(pos.x - mWidth * scale.x * centering.x);
	this->mRenderRect.y = (int)(pos.y - mHeight * scale.y * centering.y);

	this->mRenderRect.w = (int)(mWidth * scale.x);
	this->mRenderRect.h = (int)(mHeight * scale.y);



	mGraphics->DrawTexture(this->mTex, (mClipped) ? &this->mClipRect : NULL, &this->mRenderRect, Rotation(WORLD));
}



Player::~Player() {}



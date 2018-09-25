#include "GameEntity.h"

GameEntity::GameEntity(Vector2 pos) {
	mPos = pos;
	mRotation = 0.0f;
	mActive = true;
	mParent = nullptr;
	mScale = VEC2_ONE;
}

GameEntity::~GameEntity() {
	mParent = nullptr;
}

void GameEntity::Pos(Vector2 pos) {
	mPos = pos;
}

Vector2 GameEntity::Pos(SPACE space) {
	if (space == LOCAL || mParent == nullptr) {
		return mPos;
	}

	Vector2 parentScale = mParent->Scale(WORLD);

	//The object's local position is rotated by the parent's rotation
	Vector2 rotPos = RotateVector(Vector2(mPos.x * parentScale.x, mPos.y * parentScale.y), mParent->Rotation(LOCAL));

	//The final position also depends on the parents scale
	return mParent->Pos(WORLD) + rotPos;
}

void GameEntity::Rotation(float r) {
	mRotation = r;

	if (mRotation > 360.0f) {
		int mul = mRotation / 360;
		mRotation -= 360.0f * mul;
	}
	else if (mRotation < 0.0f) {
		int mul = (mRotation / 360) - 1;
		mRotation -= 360.0f * mul;
	}
}

float GameEntity::Rotation(SPACE space) {
	if (space == LOCAL || mParent == nullptr) {
		return mRotation;
	}

	return mParent->Rotation(WORLD) + mRotation;
}

void GameEntity::Scale(Vector2 scale) {
	mScale = scale;
}

Vector2 GameEntity::Scale(SPACE space) {
	if (space == LOCAL || mParent == nullptr) {
		return mScale;
	}

	Vector2 scale = mParent->Scale(WORLD);
	scale.x *= mScale.x;
	scale.y *= mScale.y;

	return scale;
}

void GameEntity::Active(bool active) {
	mActive = active;
}

bool GameEntity::Active() {
	return mActive;
}

void GameEntity::Parent(GameEntity* parent) {
	//If the parent is removed, the position/rotation/scale are the GameEntity's world
	//values, to keep the object looking the same after the removal of the parent
	if (parent == nullptr) {
		mPos = Pos(WORLD);
		mScale = Scale(WORLD);
		mRotation = Rotation(WORLD);
	}
	else {
		// If the object already has a parent, remove the current parent to get it ready to 
		// be the child of the new parent
		if (mParent != nullptr) {
			Parent(nullptr);
		}

		Vector2 parentScale = parent->Scale(WORLD);

		//Setting the local position to be relative to the new parent
		mPos = RotateVector(Pos(WORLD) - parent->Pos(WORLD), parent->Rotation(WORLD));
		mPos.x /= parentScale.x;
		mPos.y /= parentScale.y;

		//Setting the local rotation to be relative to the new parent
		mRotation = mRotation - parent->Rotation(WORLD);

		//Setting the new scale to be relative to the new parent
		mScale - Vector2(mScale.x / parentScale.x, mScale.y / parentScale.y);
	}
	mParent = parent;
}

GameEntity* GameEntity::Parent() {
	return mParent;
}

void GameEntity::Translate(Vector2 vec) {
	mPos += vec;
}

void GameEntity::Rotate(float amount) {
	mRotation += amount;
}

void GameEntity::Update() {

}

void GameEntity::Render() {

}

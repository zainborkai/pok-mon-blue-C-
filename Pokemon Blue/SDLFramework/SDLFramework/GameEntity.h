// The base class for all game entities, providing position, rotation, and scaling functionality to all entities.
// Sets up a system to parent GameEntity objects to one another making the child's position, rotation, and scale
// relative to the parent's instead of the world origin

#ifndef GAMEENTITY_H
#define GAMEENTITY_H

#include "MathHelper.h"

class GameEntity {
public:
	enum SPACE { LOCAL = 0, WORLD = 1 };

private:
	Vector2 mPos;
	float mRotation;
	Vector2 mScale;

	//Set to true if the object is to be updated and rendered
	bool mActive;


	//A GameEntity can only have one parent at a time, but can have many children
	GameEntity* mParent;

public:
	GameEntity(Vector2 Pos = VEC2_ZERO);
	~GameEntity();

	void Pos(Vector2 pos);

	void Rotation(float rotation);
	Vector2 Pos(SPACE space = WORLD);

	float Rotation(SPACE space = WORLD);

	void Scale(Vector2 scale);
	Vector2 Scale(SPACE space = WORLD);
	void Active(bool active);
	bool Active();
	void Parent(GameEntity* parent);
	GameEntity* Parent();
	void Translate(Vector2 vec);
	void Rotate(float amount);
	Vector2 GetPos() { return mPos; }

	virtual void Update();
	virtual void Render();
};

#endif // !GAMEENTITY


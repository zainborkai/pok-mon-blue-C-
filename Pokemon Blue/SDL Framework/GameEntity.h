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


	bool mActive;


	GameEntity* mParent;


public:
	GameEntity(Vector2 pos = VEC2_ZERO);
	~GameEntity();

	void Pos(Vector2 pos);
	Vector2 Pos(SPACE space = WORLD);

	void Rotation(float rotation);
	float Rotation(SPACE space = WORLD);

	void Scale(Vector2 scale);
	Vector2 Scale(SPACE space = WORLD);

	void Active(bool active);
	bool Active();
	void Parent(GameEntity* parent);
	GameEntity* Parent();
	void Translate(Vector2 vec);
	void Rotate(float amount);


	virtual void Update();
	virtual void Render();
};


#endif

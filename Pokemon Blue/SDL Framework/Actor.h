#ifndef ACTOR_H
#define ACTOR_H

#include "AnimatedTexture.h"
// #include "GameManager.h"


class Actor : public AnimatedTexture {
public:
	Actor();
	~Actor();
	void Update();
	void Render();

	void Destroy();

	int counter;
	bool visible = true;
private:
	bool _destroyed = false;;
};


#endif

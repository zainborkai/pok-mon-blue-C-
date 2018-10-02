
#include "Actor.h"
#include "GameManager.h"


Actor::Actor() :
	AnimatedTexture("nulltexture.png", 0, 0, 16, 16) {
	GameManager* gm = GameManager::Instance();
	gm->RegisterActor(this);
}
Actor::~Actor() {}


void Actor::Update() {
	AnimatedTexture::Update();
}

void Actor::Render() {
	if (visible) {
		AnimatedTexture::Render();
	}
}


void Actor::Destroy() {
	GameManager* gm = GameManager::Instance();
	gm->_QueueDestroy(this);
	//
	_destroyed = true;
}

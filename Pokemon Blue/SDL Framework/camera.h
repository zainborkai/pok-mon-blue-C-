#ifndef CAMERA_H
#define CAMERA_H

//#include "map.h"
//#include "player.h"

#include <chrono>

class Camera {
public:
	Camera();

	SDL_Rect& getCameraRect() { return mCameraRect; }

	void update(Player& player, SDL_Rect& mapRect);

private:
	SDL_Rect mCameraRect;
};

#endif // CAMERA_H

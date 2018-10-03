#ifndef GROUNDGRASS_H
#define GROUNDGRASS_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include <iostream>


class GroundGrass : public AnimatedTexture {
public:

	void Update();
	// void Render();

	GroundGrass();
	~GroundGrass();

	int X = 0;
	int Y = 0;


};


#endif
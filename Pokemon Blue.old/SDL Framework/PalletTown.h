#ifndef PALLETTOWN_H
#define PALLETTOWN_H


#include "AnimatedTexture.h"

class PalletTown : AnimatedTexture {
public:
	PalletTown();
	~PalletTown();
	void Update();
	void Render();
};

#endif
#ifndef CHARACTER_H
#define CHARACTER_H

#include "Texture.h"

class Character : public Texture {
public:
	Character();
	~Character();
	void Update();
	void Render();



};

#endif // !CHARACTER_H
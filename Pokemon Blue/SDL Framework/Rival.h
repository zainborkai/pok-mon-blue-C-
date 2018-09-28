#ifndef RIVAL_H
#define RIVAL_H

#include "Text.h"

class Rival : public AnimatedTexture
{
public:
	Rival();
	~Rival();

	void Render();
	void Update();

	void conversation();

private:
	

	Text* mText;
};

#endif // !RIVAL_H


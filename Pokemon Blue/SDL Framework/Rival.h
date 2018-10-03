#ifndef RIVAL_H
#define RIVAL_H

#include "Text.h"
#include "NPC.h"

class Rival : public NPC
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


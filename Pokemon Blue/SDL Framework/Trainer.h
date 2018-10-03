#ifndef TRAINER_H
#define TRAINER_H

#include "Text.h"
#include "NPC.h"

class Trainer : public NPC
{
public:
	Trainer();
	~Trainer();

	void Render();
	void Update();

	void conversation();
	void BattleFunction();

private:
	bool WinBattle;

	Text* mText;
};

#endif // !TRAINER_H

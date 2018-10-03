#ifndef OAK_H
#define OAK_H

#include "Text.h"
#include "NPC.h"

class Oak : public NPC
{
public:
	Oak();
	~Oak();

	void Render();
	void Update();

	void conversation();

private:
	//need to keep track of what point of the game we are in
	bool choice = false;
	bool battle = false;
	bool delivery = false;

	Text* mText;
};

#endif // !OAK_H

#ifndef MOM_H
#define MOM_H

#include "Text.h"
#include "NPC.h"

class Mom : public NPC
{
public:
	Mom();
	~Mom();

	void Render();
	void Update();

	void conversation();

private:

	bool Beginning;

	Text* mText;
};

#endif // !MOM_H


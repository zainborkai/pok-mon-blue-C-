#ifndef BROCK_H
#define BROCK_H

#include "Text.h"
#include "NPC.h"

class Brock : public NPC {
public:
	Brock();
	~Brock();

	void Render();
	void Update();

	void conversation();

private:


	Text* mText;
};

#endif //!BROCK_H


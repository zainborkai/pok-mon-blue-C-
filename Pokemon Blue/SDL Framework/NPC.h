#ifndef NPC_H
#define NPC_H

#include "Text.h"

class NPC : public AnimatedTexture
{
public:
	NPC();
	~NPC();

	void Update();
	void Render();

	/*int GetPosX() { return posX; }
	int GetPosY() { return posY; }
	int GetWidth() { return width; }
	int GetHeight() { return height; }

	void SetPosX(int x) { posX = x; }
	void SetPosY(int y) { posY = y; }
	void SetPosX(int w) { width = w; }
	void SetPosX(int h) { height = h; }*/

private:
	
	std::string conversation;
	int posX;
	int posY;
	int width;
	int height;

	Text* pNPCText;
	
};

#endif


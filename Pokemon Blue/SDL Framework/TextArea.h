#ifndef TEXTAREA_H
#define TEXTAREA_H

#include <map>
#include "TiledTexture.h"
#include "Helper.h"
#include "GameSystem.h"


class TextArea : public TiledTexture {
public:
	std::string message;
	TextArea(std::string str) :
		TiledTexture("gametext.png") {

		Scale(Vector2(1.0f, 1.0f));

		textSpeed = 0;

		FeedString(str);
	};


	// ??? <-- VERY BAD!!
	std::map<char, Vector2> linking = {
		{ 'A', Vector2(0, 0) },
		{ 'a', Vector2(0, 24) },
		
		{ '0', Vector2(0, 48) },

		{ '?', Vector2(0, 56) },
		{ '!', Vector2(8, 56) },
		{ '.', Vector2(16, 56) },
		{ ',', Vector2(24, 56) },
		{ '\'', Vector2(32, 56) },
		{ '/', Vector2(40, 56) },
		{ '-', Vector2(48, 56) },
		{ ' ', Vector2(72, 56) },
	};

	int textTime;
	int textSpeed;
	int textDuration;
	float textPercent;

	void FeedString(std::string str, int maxLength = 1000, int lineSep = 16) {
		message = str;

		textTime = 0;


		Clear();
		//
		int charcode;
		for (int i = 0; i < str.size(); i++) {
			char linkingChar;
			if (between((int)'A', (int)str[i], (int)'Z')) {
				linkingChar = 'A';
			}
			else if (between((int)'a', (int)str[i], (int)'z')) {
				linkingChar = 'a';
			}
			else if (between((int)'0', (int)str[i], (int)'9')) {
				linkingChar = '0';
			}
			else if (str[i] == ' ') {
				linkingChar = ' ';
			}
			else if (str[i] == '!') {
				linkingChar = '!';
			}
			else if (str[i] == '?') {
				linkingChar = '?';
			}
			else if (str[i] == ',') {
				linkingChar = ',';
			}
			else if (str[i] == '.') {
				linkingChar = '.';
			}
			else if (str[i] == '\'') {
				linkingChar = '\'';
			}
			else if (str[i] == '/') {
				linkingChar = '/';
			}
			else if (str[i] == '-') {
				linkingChar = '-';
			}
			else {
				continue; // *** Nope!
			}
			

			Vector2 texPos;
			texPos = linking[linkingChar];
			charcode = (int)str[i] - (int)linkingChar;
			//
			Add(8* (tiles.size() % maxLength), lineSep * (tiles.size() / maxLength), texPos.x + 8 * (charcode % 10), texPos.y + 8 * (charcode / 10), 8, 8);
		}
	};



	void Update() {
		TiledTexture::Update();


		if (InputManager::Instance()->KeyDown(GameSystem::KEY_AFFIRM)) {
			textTime += 1 *3;
		}
		else {
			textTime += 1;
		}
		//
		textDuration = textSpeed * message.size(); // ??? <-- Kinda inefficient...
		//
		textPercent = longevity(textTime, 0, textDuration);
		//
		restrictBegin = 0;
		restrictEnd = message.size() *textPercent;
	}
	bool IsDone() { return textPercent >= 1.0f; }
};


#endif

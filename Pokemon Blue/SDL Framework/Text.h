#ifndef TEXT_H
#define TEXT_H

#include "Texture.h"
#include "InputManager.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <map>

class TextLine
{
public:
	std::vector<std::string> stuff;
	std::vector<Texture> UseTexture;
	int StartPoint = 0;
	const int showLineCount = 2;

};

class Text : public Texture {
public:
	Text();
	~Text();
	void Update();
	void Render();
	void NextText();
	void SetmWords(std::string words) { mWords = words; }
	std::string GetmWords() { return mWords; }

	std::string replaceString(std::string strToReplaceOn, std::string subStringToLookFor, std::string whatToReplaceItWith);

	void SetIsActive(bool active) { isActive = active; }

	bool GetIsActive() { return isActive; }

	static Text* Instance();
	static void Release();
	static bool Initialized();

	void SetParagraphNumber(int paragraphNum) { paragraphNumber = paragraphNum; }
	void SetLineNumber(int lineNum) { lineNumber = lineNum; }

	int GetParagraphNumber() { return paragraphNumber; }
	int GetLineNumber() { return lineNumber; }

	TextLine* textLine;
	void NewText(std::string area, int paragraph);

	int currentParagraph = 0;
	std::string currentArea;

private:
	static Text* sInstance;
	static bool sInitialized;

	std::string mWords = "HELLO WORLD!"; //What is this?
	int LineNumber;

	//creating the map that stores a vector of strings that also stores a vector of strings
	std::map<std::string, std::vector<std::vector<std::string>*>*> textFile;
	//
	//Setting constants for parts of the textfile
	const std::string playerName = "ASH";
	const std::string rivalName = "GARY";

	//std::vector<std::string> TextFile;
	Texture* pTextBox;
	Texture* pText;
	Texture* pNextLine;
	SDL_Color color;

	//
	std::string strToReplaceOn;
	std::string subStringToLookFor;
	std::string whatToReplaceItWith;
	int index;

	std::string theLine;
	std::string key;

	bool isActive = true;

	InputManager* mInputMgr;

	int paragraphNumber;
	int lineNumber;

};


#endif //!TEXT_H

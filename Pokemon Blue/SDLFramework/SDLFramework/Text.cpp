#include "Text.h"

Text* Text::sInstance = NULL;
bool Text::sInitialized = false;

//Create a singleton
Text* Text::Instance() {
	//create a new instance if no instance was created before
	if (sInstance == NULL) {
		sInstance = new Text();
	}

	return sInstance;
}

//Singleton
void Text::Release() {
	delete sInstance;
	sInstance = nullptr;
	sInitialized = false;
}

//Singleton
bool Text::Initialized() {
	return sInitialized;
}

//Function 
std::string Text::replaceString(std::string strToReplaceOn, std::string subStringToLookFor, std::string whatToReplaceItWith) {
	do {
		index = strToReplaceOn.find(subStringToLookFor);
		if (index >= 0) {
			strToReplaceOn.replace(index, index + subStringToLookFor.size(), whatToReplaceItWith);
		}
	} while (index >= 0);

	return strToReplaceOn;
};

Text::Text() : Texture(" ", "POKEMONGB.ttf", 12, { 0,0,0 }) {
	Pos(Vector2(100, 100));
	//
	//need this code to access the input manager in Text
	mInputMgr = InputManager::Instance();
	//Open the text file
	std::ifstream src("GameText.txt");

	if (!src.is_open()) {
		std::cout << "couldn't open file: GameText.txt" << std::endl;
	}
	//This code will manipulate the text file so it displays what I want

	while (!src.eof()) {
		std::getline(src, theLine);
		//
		//Substitute the names
		theLine = replaceString(theLine, "<NAME>", playerName);
		theLine = replaceString(theLine, "<RIVAL>", rivalName);
		//
		//Now we set the conditions for how we want text displayed
		if (theLine.size() >= 3 && theLine[0] == '*' && theLine[1] == '*' && theLine[2] == '*') {
			//we will skip these lines
			//These lines are markers for certain events/locations
			key = theLine.substr(3, theLine.size() - 3);
			textFile[key] = new std::vector<std::vector<std::string>*>();
		}
		else if (theLine.size() >= 2 && theLine[0] == '-' && theLine[1] == '-') {
			//we will skip these lines too
			//These are markers for interacting with an NPC/object
		}
		else if (theLine.size() >= 2 && theLine[0] == '<' && theLine[1] == '<') {
			//skip these
		}
		else if (theLine.size() == 0) {
			textFile[key]->push_back(new std::vector<std::string>());
		}
		else {
			(*textFile[key])[textFile[key]->size() - 1]->push_back(theLine);
		}

	}
	src.close();
	//
	//This for loop is going through the text file and displaying the lines
	for (std::pair<std::string, std::vector<std::vector<std::string>*>*> pair : textFile) {
		std::vector<std::vector<std::string>*>* paragraph = textFile[pair.first];

		for (int i = 0; i < paragraph->size(); i++) {
			std::vector<std::string>* line = (*paragraph)[i];

			for (int j = 0; j < line->size(); j++) {
				std::string theWords = (*line)[j];

				//std::cout << theWords << std::endl;
			}
		}
	}
	//This line will display the 3rd line of the first paragraph in the "INTRO" key
	//textFile["INTRO"][0][0];
	//std::cout << (*(*textFile["INTRO"])[5])[0] << std::endl;
	// paragraphNumber = 0;
	// lineNumber = 0;

	pTextBox = new Texture("TextBox.png");
	pTextBox->Pos(Vector2(0, 50));
	//
	//
	//
	currentArea = "INTRO";
	currentParagraph = 0;

	//Getting a bunch of lines and giving them a texture
	textLine = new TextLine();
	NewText(currentArea, currentParagraph);

}

void Text::NewText(std::string area, int paragraph) {
	for (int i = 0; i < (*(*textFile[area])[paragraph]).size(); i++) {
		textLine->stuff.push_back((*(*textFile[area])[paragraph])[i]);

	}
	for (int i = 0; i < textLine->stuff.size(); i++) {

		textLine->UseTexture.push_back(
			Texture(textLine->stuff[i], "POKEMONGB.ttf", 10, { 0,0,0 })
		);
	}
}


Text::~Text() {
	delete pTextBox;
	pTextBox = nullptr;

	delete pText;
	pText = nullptr;

	delete pNextLine;
	pNextLine = nullptr;

	delete textFile[key];
	textFile[key] = nullptr;

	InputManager::Release();
	mInputMgr = nullptr;
}

void Text::Update() {

}

void Text::NextText() {
	
	if (!GetIsActive()) { return; }
	
	
	//Trying to make code that will iterate through the elements of the textFile map
	//and display each line by line when the Z key is pressed
	if (mInputMgr->KeyPressed(SDL_SCANCODE_Z))
	{
		if (textLine->StartPoint + textLine->showLineCount < textLine->UseTexture.size()) {
			textLine->StartPoint++;
		}
		else {
			currentParagraph++;
			//
			int sizething = (*textFile[currentArea]).size();
			if (currentParagraph < sizething) {
				delete textLine;
				//
				textLine = new TextLine();
				NewText(currentArea, currentParagraph);
			}
			else {
				// FINSIH TALKING!!!
				delete textLine;
				textLine = nullptr;
				//
				SetIsActive(false);
			}

			

		}
	}



}

void Text::Render() {

	if (isActive == true) {
		//display textBox 
		
		/*
		{
		[0] Hello there!
		[1] Welcome to the
		[2] world of POKeMON!
		}
		
		*/

		pTextBox->SetmRenderRectX(pTextBox->Pos(WORLD).x);
		pTextBox->SetmRenderRectY(pTextBox->Pos(WORLD).y);
		mGraphics->DrawTexture(pTextBox->GetmTex(), (mClipped) ? &mClipRect : NULL, &pTextBox->GetmRenderRect(), Rotation(WORLD));

		int screenX, screenY;
		screenX = pTextBox->GetPos().x +5;
		screenY = pTextBox->GetPos().y +10;

		int n; // Start Point
		for (int i = 0; i < textLine->showLineCount; i++) { // for (int i = 0; i < wordBox.size(); i++) {
			n = textLine->StartPoint + i;
			//
			if (n >= textLine->UseTexture.size()) { break; }
			//
			int pushTextDown = 15 * i;

			textLine->UseTexture[n].SetmRenderRectX(screenX);
			textLine->UseTexture[n].SetmRenderRectY(screenY + pushTextDown);
			mGraphics->DrawTexture(textLine->UseTexture[n].GetmTex(), (mClipped) ? &mClipRect : NULL, &textLine->UseTexture[n].GetmRenderRect(), Rotation(WORLD));
		}
	}
	//   0         1          2       3         4      5       (size is 6)
	/*{ "Khori", "Armstrong", "Matt", "Walsh", "Bob", "Jones" }

	int startpoint = 1;
	for (int i = startpoint; i < startpoint+2; i++) {

	}*/
	/*
	Array ... And it's size is "5"
	{ 0 , 1, 2 , 3, 4 } (5 things)

	"for statement", you're saying "start from 0...
	Count up until we are "equal" to size...
	... That would mean the moment we hit "5" (that is, 1 higher than the "biggest" index)...
	... We STOP!

	You're basically saying "go through everything from beginning to end."

	You'll notice... We "start" at 0... But do we have to?
	What if I put "1"?
	We also say "STOP when we are at size"... But what if I said "stop at -2 of size?"

	What if I said "i += 3"?
	*/
	

}
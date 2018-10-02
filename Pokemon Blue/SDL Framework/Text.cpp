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

//Singleton component
void Text::Release() {
	delete sInstance;
	sInstance = nullptr;
	sInitialized = false;
}

//Singleton component
bool Text::Initialized() {
	return sInitialized;
}
//
// This function is going to allow us to access any part of the text file
// Each part is identified with a leading ***
void Text::displayTextBox(std::string currentPart) {
	//Need to make a function so we can set currentArea to the part we want 
	currentArea = currentPart; // I think this needs to be changed so we can use any area of the text file
	currentParagraph = 0;

	//Getting a bunch of lines and giving them a texture
	textLine = new TextLine();
	NewText(currentArea, currentParagraph);

	NextText();
	//displayTextBox("INTRO"); //I want this function to be able to change what text is displayed in the textbox
} 

//Function that will replace a string from the text file with a different specified string
std::string Text::replaceString(std::string strToReplaceOn, std::string subStringToLookFor, std::string whatToReplaceItWith) {
	do {
		index = strToReplaceOn.find(subStringToLookFor);
		if (index >= 0) {
			strToReplaceOn.replace(index, index + subStringToLookFor.size(), whatToReplaceItWith);
		}
	} while (index >= 0);

	return strToReplaceOn;
};
//
//The Text constructor
Text::Text() : Texture(" ", "POKEMONGB.ttf", 8, { 0,0,0 }) {
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
		} //So each time we reach a space in the text file, everything before it is stored in the textFile vector
		else if (theLine.size() == 0) {
			textFile[key]->push_back(new std::vector<std::string>());
		}
		else {//What is this doing?
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
	//Display the text box
	pTextBox = new Texture("TextBox.png");
	pTextBox->Pos(Vector2(0, 50));
	//
	//
	pNameBox = new Texture("NameBox.PNG");
	pNameBox->Pos(Vector2(250, 200));

	newName = new Texture("NEW NAME", "POKEMONGB.ttf", 26, { 0,0,0 });
	newName->Pos(Vector2(330, 270));
	blueName = new Texture("BLUE", "POKEMONGB.ttf", 26, {0,0,0});
	blueName->Pos(Vector2(330, 350));
	garyName = new Texture("GARY", "POKEMONGB.ttf", 26, { 0,0,0 });
	garyName->Pos(Vector2(330, 430));
	johnName = new Texture("JOHN", "POKEMONGB.ttf", 26, { 0,0,0 });
	johnName->Pos(Vector2(330, 510));
	//
	//
	pArrow = new Texture("arrowPKMN.png");
	pArrow->Pos(Vector2(275, 255));
	//accessText. wanted to make a variable with getters and setters to access specific texts
}
//
// NewText function. Creates the text
void Text::NewText(std::string area, int paragraph) {
	for (int i = 0; i < (*(*textFile[area])[paragraph]).size(); i++) {
		textLine->stuff.push_back((*(*textFile[area])[paragraph])[i]);
	}
	for (int i = 0; i < textLine->stuff.size(); i++) {

		textLine->UseTexture.push_back(
			Texture(textLine->stuff[i], "POKEMONGB.ttf", 8, { 0,0,0 })
		);
	}
}

//Text deconstructor. Ensures we don't have any memory leaks when the text isn't active
Text::~Text() {
	delete pTextBox;
	pTextBox = nullptr;

	delete pNameBox;
	pNameBox = nullptr;

	delete pArrow;
	pArrow = nullptr;

	delete pText;
	pText = nullptr;

	delete pNextLine;
	pNextLine = nullptr;

	delete textFile[key];
	textFile[key] = nullptr;

	InputManager::Release();
	mInputMgr = nullptr;
}
//
//The text update function. Nothing here yet. Not sure what this does?
void Text::Update() {

}
//
//NextText function. This is the big one that will display each line, 2 lines at a time. 
void Text::NextText() {
	//
	MoveArrow();
	//
	if (!GetIsActive()) { return; }

	//Trying to make code that will iterate through the elements of the textFile map
	//and display each line by line when the Z key is pressed
	if (mInputMgr->KeyPressed(SDL_SCANCODE_Z))
	{//                   0          +             2        <          size of the vector
		if (textLine->StartPoint + textLine->showLineCount < textLine->UseTexture.size()) {
			textLine->StartPoint++; // increment the start point by 1
		}
		else {
			currentParagraph++; //This will change to the next paragraph once we reach the end of the previous paragraph
			//
			int paragraphSize = (*textFile[currentArea]).size();
			if (currentParagraph < paragraphSize) { // If we reach the end of a paragraph, It will clear the screen before it displays the new paragraph
				delete textLine;
				//delete the old text and create a new textLine
				textLine = new TextLine();
				NewText(currentArea, currentParagraph);
			}
			else {
				// FINISH TALKING!!!
				delete textLine;
				textLine = nullptr;
				//
				SetIsActive(false);
			}
		}
	}
}


//Want a function that will move the arrow on the screen
void Text::MoveArrow() {
	if (mInputMgr->KeyPressed(SDL_SCANCODE_DOWN)) {
		//pArrow->Pos(pArrow->GetPos().x); // We dont want the X position to change
		pArrow->Pos(Vector2(275, pArrow->GetPos().y + 80));

		if (pArrow->GetPos().y >= 495) {
			pArrow->Pos(Vector2(275, 495));
		}
	}

	else if (mInputMgr->KeyPressed(SDL_SCANCODE_UP)) {
		pArrow->Pos(Vector2(275, pArrow->GetPos().y - 80));

		if (pArrow->GetPos().y <= 255) {
			pArrow->Pos(Vector2(275, 255));
		}
	}
}

void Text::Render() {

	if (isActive == true) {
		//display textBox 
		//
		pTextBox->SetmRenderRectX(pTextBox->Pos(WORLD).x);
		pTextBox->SetmRenderRectY(pTextBox->Pos(WORLD).y);
		mGraphics->DrawTexture(pTextBox->GetmTex(), (mClipped) ? &mClipRect : NULL, &pTextBox->GetmRenderRect(), Rotation(WORLD));
		//
		//
		pNameBox->SetmRenderRectX(pNameBox->Pos(WORLD).x);
		pNameBox->SetmRenderRectY(pNameBox->Pos(WORLD).y);
		mGraphics->DrawTexture(pNameBox->GetmTex(), (mClipped) ? &mClipRect : NULL, &pNameBox->GetmRenderRect(), Rotation(WORLD));
		//
		newName->SetmRenderRectX(newName->Pos(WORLD).x);
		newName->SetmRenderRectY(newName->Pos(WORLD).y);
		mGraphics->DrawTexture(newName->GetmTex(), (mClipped) ? &mClipRect : NULL, &newName->GetmRenderRect(), Rotation(WORLD));
		//
		blueName->SetmRenderRectX(blueName->Pos(WORLD).x);
		blueName->SetmRenderRectY(blueName->Pos(WORLD).y);
		mGraphics->DrawTexture(blueName->GetmTex(), (mClipped) ? &mClipRect : NULL, &blueName->GetmRenderRect(), Rotation(WORLD));
		//
		garyName->SetmRenderRectX(garyName->Pos(WORLD).x);
		garyName->SetmRenderRectY(garyName->Pos(WORLD).y);
		mGraphics->DrawTexture(garyName->GetmTex(), (mClipped) ? &mClipRect : NULL, &garyName->GetmRenderRect(), Rotation(WORLD));
		//
		johnName->SetmRenderRectX(johnName->Pos(WORLD).x);
		johnName->SetmRenderRectY(johnName->Pos(WORLD).y);
		mGraphics->DrawTexture(johnName->GetmTex(), (mClipped) ? &mClipRect : NULL, &johnName->GetmRenderRect(), Rotation(WORLD));
		//
		//Render the arrow on screen
		pArrow->SetmRenderRectX(pArrow->Pos(WORLD).x);
		pArrow->SetmRenderRectY(pArrow->Pos(WORLD).y);
		mGraphics->DrawTexture(pArrow->GetmTex(), (mClipped) ? &mClipRect : NULL, &pArrow->GetmRenderRect(), Rotation(WORLD));
		//
		//we are declaring new variables that will adjust the position of the text on screen relative to the position of the text box
		int screenX, screenY;
		screenX = pTextBox->GetPos().x + 10;
		screenY = pTextBox->GetPos().y + 15;
		//
		//This is going to display the text on the screen
		int n; // Start Point
		for (int i = 0; i < textLine->showLineCount; i++) { // for (int i = 0; i < wordBox.size(); i++) {
			n = textLine->StartPoint + i;
			//
			if (n >= textLine->UseTexture.size()) { break; }
			//
			int pushTextDown = 20 * i; // This new variable makes sure that the second line is always displaced from the first line
			//
			//
			textLine->UseTexture[n].SetmRenderRectX(screenX);
			textLine->UseTexture[n].SetmRenderRectY(screenY + pushTextDown);
			//Need help on what this line is doing 
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

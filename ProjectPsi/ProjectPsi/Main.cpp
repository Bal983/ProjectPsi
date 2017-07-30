//C++ includes
#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>
#include <tuple>

//Allegro includes
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Generic Variables
ALLEGRO_DISPLAY *settingsDisplay = NULL;
ALLEGRO_DISPLAY *mainDisplay = NULL;
ALLEGRO_EVENT_QUEUE *mainEventQueue = NULL;
bool quit = false;

//Try to keep only 16:9 resolution setups
//static const int SCREENWIDTH = 1920;
//static const int SCREENHEIGHT = 1080;
static const int SCREENWIDTH = 1280;
static const int SCREENHEIGHT = 720;

//Variables used to initialize the simulation
string leftValue1;
string leftValue2;
string leftValue3;
string leftValue4;
string leftValue5;
string leftValue6;
string leftValue7;
string rightValue1;
string rightValue2;
string rightValue3;
string rightValue4;
string rightValue5;
string rightValue6;
string rightValue7;

//Title Screen Variables
ALLEGRO_USTR *mainMenuScreenTitle = al_ustr_new("Project Psi");
ALLEGRO_USTR *newSimulationString = al_ustr_new("New Simulation");
ALLEGRO_USTR *loadSimulationString = al_ustr_new("Load Simulation");
ALLEGRO_USTR *optionsString = al_ustr_new("Options");
ALLEGRO_USTR *creditsString = al_ustr_new("Credits");
ALLEGRO_USTR *quitString = al_ustr_new("Quit");
const int titleScreenMenuItems = 5; //Don't count the title in here
ALLEGRO_USTR *allTitleScreenOptions[titleScreenMenuItems] = {
    newSimulationString,
    loadSimulationString,
    optionsString,
    creditsString,
    quitString
}; //add new menu options to this array, make sure to increment maxMenuItems, so far this is just for us to keep track of them

//New Simulation Screen Variables
ALLEGRO_USTR *newSimulationScreenTitle = al_ustr_new("New Simulation");
ALLEGRO_USTR *newSimulationLeftp1prompt = al_ustr_new("Placeholder:");
ALLEGRO_USTR *newSimulationLeftp2prompt = al_ustr_new("Placeholder:");
ALLEGRO_USTR *newSimulationLeftp3prompt = al_ustr_new("Placeholder:");
ALLEGRO_USTR *newSimulationLeftp4prompt = al_ustr_new("Placeholder:");
ALLEGRO_USTR *newSimulationLeftp5prompt = al_ustr_new("Placeholder:");
ALLEGRO_USTR *newSimulationLeftp6prompt = al_ustr_new("Placeholder:");
ALLEGRO_USTR *newSimulationLeftp7prompt = al_ustr_new("Placeholder:");
ALLEGRO_USTR *newSimulationLeftp1value = al_ustr_new("Value");
ALLEGRO_USTR *newSimulationLeftp2value = al_ustr_new("Value");
ALLEGRO_USTR *newSimulationLeftp3value = al_ustr_new("Value");
ALLEGRO_USTR *newSimulationLeftp4value = al_ustr_new("Value");
ALLEGRO_USTR *newSimulationLeftp5value = al_ustr_new("Value");
ALLEGRO_USTR *newSimulationLeftp6value = al_ustr_new("Value");
ALLEGRO_USTR *newSimulationLeftp7value = al_ustr_new("Value");
ALLEGRO_USTR *newSimulationRightp1prompt = al_ustr_new("Placeholder:");
ALLEGRO_USTR *newSimulationRightp2prompt = al_ustr_new("Placeholder:");
ALLEGRO_USTR *newSimulationRightp3prompt = al_ustr_new("Placeholder:");
ALLEGRO_USTR *newSimulationRightp4prompt = al_ustr_new("Placeholder:");
ALLEGRO_USTR *newSimulationRightp5prompt = al_ustr_new("Placeholder:");
ALLEGRO_USTR *newSimulationRightp6prompt = al_ustr_new("Placeholder:");
ALLEGRO_USTR *newSimulationRightp7prompt = al_ustr_new("Placeholder:");
ALLEGRO_USTR *newSimulationRightp1value = al_ustr_new("Value");
ALLEGRO_USTR *newSimulationRightp2value = al_ustr_new("Value");
ALLEGRO_USTR *newSimulationRightp3value = al_ustr_new("Value");
ALLEGRO_USTR *newSimulationRightp4value = al_ustr_new("Value");
ALLEGRO_USTR *newSimulationRightp5value = al_ustr_new("Value");
ALLEGRO_USTR *newSimulationRightp6value = al_ustr_new("Value");
ALLEGRO_USTR *newSimulationRightp7value = al_ustr_new("Value");
ALLEGRO_USTR *newSimulationGoBackString = al_ustr_new("Go Back");
const int newSimulationScreenMenuItems = 15; //Don't count the title in here
tuple<ALLEGRO_USTR,ALLEGRO_USTR> allNewSimulationScreenOptions[newSimulationScreenMenuItems] = {
	make_tuple(*newSimulationLeftp1prompt, *newSimulationLeftp1value),
	make_tuple(*newSimulationLeftp2prompt, *newSimulationLeftp2value),
	make_tuple(*newSimulationLeftp3prompt, *newSimulationLeftp3value),
	make_tuple(*newSimulationLeftp4prompt, *newSimulationLeftp4value),
	make_tuple(*newSimulationLeftp5prompt, *newSimulationLeftp5value),
	make_tuple(*newSimulationLeftp6prompt, *newSimulationLeftp6value),
	make_tuple(*newSimulationLeftp7prompt, *newSimulationLeftp7value),
	make_tuple(*newSimulationRightp1prompt, *newSimulationRightp1value),
	make_tuple(*newSimulationRightp2prompt, *newSimulationRightp2value),
	make_tuple(*newSimulationRightp3prompt, *newSimulationRightp3value),
	make_tuple(*newSimulationRightp4prompt, *newSimulationRightp4value),
	make_tuple(*newSimulationRightp5prompt, *newSimulationRightp5value),
	make_tuple(*newSimulationRightp6prompt, *newSimulationRightp6value),
	make_tuple(*newSimulationRightp7prompt, *newSimulationRightp7value),
	make_tuple(*newSimulationGoBackString, *newSimulationGoBackString)
}; //add new menu options to this array, make sure to increment maxMenuItems, so far this is just for us to keep track of them
tuple<float, float>allNewSimulationScreenPositions[newSimulationScreenMenuItems] = {
	make_tuple(0.2, 0.2),
	make_tuple(0.2, 0.3),
	make_tuple(0.2, 0.4),
	make_tuple(0.2, 0.5),
	make_tuple(0.2, 0.6),
	make_tuple(0.2, 0.7),
	make_tuple(0.2, 0.8),
	make_tuple(0.7, 0.2),
	make_tuple(0.7, 0.3),
	make_tuple(0.7, 0.4),
	make_tuple(0.7, 0.5),
	make_tuple(0.7, 0.6),
	make_tuple(0.7, 0.7),
	make_tuple(0.7, 0.8),
	make_tuple(0.475, 1)
};//this is the format of width position/height position
//these are the positions corresponding to the values of the above tuples, only the values not the prompts.
//We need to find a better way to do this
//Note: the last one maps to the middle and the far right

//Load Simulation Screen Variables
ALLEGRO_USTR *loadSimulationScreenTitle = al_ustr_new("Load Simulation");
ALLEGRO_USTR *loadSimulationStringOne = al_ustr_new("Loading Simulation Coming Soon!");
ALLEGRO_USTR *loadSimulationGoBackString = al_ustr_new("Go Back");
const int loadSimulationScreenMenuItems = 2; //Don't count the title in here
ALLEGRO_USTR *allLoadSimulationScreenOptions[loadSimulationScreenMenuItems] = {
    loadSimulationGoBackString,
    loadSimulationStringOne
}; //add new menu options to this array, make sure to increment maxMenuItems, so far this is just for us to keep track of them

//Options Screen Variables
ALLEGRO_USTR *optionsScreenTitle = al_ustr_new("Options");
ALLEGRO_USTR *optionsGoBackString = al_ustr_new("Go Back");
ALLEGRO_USTR *optionsStringOne = al_ustr_new("Press up arrow or w to move up in the menu");
ALLEGRO_USTR *optionsStringTwo = al_ustr_new("Press down arrow or s to move down in the menu");
ALLEGRO_USTR *optionsStringThree = al_ustr_new("Press escape at any time to close the launcher");
ALLEGRO_USTR *optionsStringFour = al_ustr_new("Press enter at any to confirm your selection");
ALLEGRO_USTR *optionsStringFive = al_ustr_new("Press backspace to move back in the menu system");
const int optionsScreenMenuItems = 6; //Don't count the title in here
ALLEGRO_USTR *allOptionsScreenOptions[optionsScreenMenuItems] = {
    optionsGoBackString,
    optionsStringOne,
    optionsStringTwo,
    optionsStringThree,
    optionsStringFour,
    optionsStringFive
}; //add new menu options to this array, make sure to increment maxMenuItems, so far this is just for us to keep track of them

//Credits Screen Variables
ALLEGRO_USTR *creditsScreenTitle = al_ustr_new("Credits");
ALLEGRO_USTR *creditsGoBackString = al_ustr_new("Go Back");
ALLEGRO_USTR *creditsStringOne = al_ustr_new("Project Psi was created by Bryton Leason and Sam Horovatin");
ALLEGRO_USTR *creditsStringTwo = al_ustr_new("This project is for the purpose of learning about AI and making something we can be proud of");
ALLEGRO_USTR *creditsStringThree = al_ustr_new("We are using allegro and trying to do as much of the code on our own as possible");
ALLEGRO_USTR *creditsStringFour = al_ustr_new("Thanks for playing with our simulator!");
const int creditsScreenMenuItems = 5; //Don't count the title in here
ALLEGRO_USTR *allCreditsScreenOptions[creditsScreenMenuItems] = {
    creditsGoBackString,
    creditsStringOne,
    creditsStringTwo,
    creditsStringThree,
    creditsStringFour
}; //add new menu options to this array, make sure to increment maxMenuItems, so far this is just for us to keep track of them

//Colours and Fonts
ALLEGRO_COLOR screenOptionsColour = al_map_rgb_f(0.8706, 0.7216, 0.5294); //burlywood colour
ALLEGRO_COLOR screenBackgroundColour = al_map_rgb_f(0, 0, 0); //black colour
ALLEGRO_FONT *screenOptionsFont = NULL;
ALLEGRO_FONT *screenOptionsSmallFont = NULL;
ALLEGRO_FONT *screenTitleFont = NULL;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Function prototypes so I can keep being a java programmer
//Generic Functions
void drawTriangle(float, float, int, ALLEGRO_COLOR);
tuple<bool, string> processMenu(string, int);
void loadNewMenu(string);
int normalizeScreenIndex(int, int);

//Title Screen Functions
void setupTitleScreen();
int normalizeTitleScreenIndex(int);
void moveTitleScreenDown(int);
void moveTitleScreenUp(int);
void drawTitleScreenWithSelection(int, int);

//New Simulation Functions
void setupNewSimulationScreen();
int normalizeNewSimulationScreenIndex(int);
void moveNewSimulationScreenDown(int);
void moveNewSimulationScreenUp(int);
void drawNewSimulationScreenWithSelection(int, int);
void updateNewSimulationScreenString(int, char);
void removeCharFromNewSimluationScreenString(int);

//Load Simulation Functions
void setupLoadSimulationScreen();
int normalizeLoadSimulationScreenIndex(int);

//Options Functions
void setupOptionsScreen();

//Credits Functions
void setupCreditsScreen();

//Init Functions
int initAddons();
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int main(int argc, char **argv) {

    if (initAddons() == -1) {
        return -1;
    }

    setupTitleScreen();

	bool valueInputMode = false;
    int currentMenuIndex = 0;
    string currentMenu = "Title Screen";
    while (!quit) {
		ALLEGRO_EVENT event;
		al_wait_for_event(mainEventQueue, &event);
		if (!valueInputMode) {
			switch (event.type) {
			case ALLEGRO_EVENT_DISPLAY_CLOSE: //This triggers when you hit the x on the window
				quit = true;
				break;
			case ALLEGRO_EVENT_KEY_CHAR:
				switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_BACKSPACE:
					if (currentMenu == "Title Screen") {
						quit = true;
					}
					else {
						currentMenu = "Title Screen";
						currentMenuIndex = 0;
						setupTitleScreen();
					}
					break;
				case ALLEGRO_KEY_ESCAPE:
					quit = true;
					break;
				case ALLEGRO_KEY_ENTER:
					if (currentMenu == "Title Screen") {
						auto response = processMenu("Title Screen", currentMenuIndex);
						quit = get<0>(response);
						loadNewMenu(get<1>(response));
						currentMenu = get<1>(response);
						currentMenuIndex = 0;
					}
					else if (currentMenu == "New Simulation") {
						auto response = processMenu("New Simulation", currentMenuIndex);
						valueInputMode = get<0>(response);
						if (!valueInputMode){
							loadNewMenu(get<1>(response));
							currentMenu = get<1>(response);
							currentMenuIndex = 0;
						}
					}
					else if (currentMenu == "Load Simulation") {
						auto response = processMenu("Load Simulation", currentMenuIndex);
						quit = get<0>(response);
						loadNewMenu(get<1>(response));
						currentMenu = get<1>(response);
						currentMenuIndex = 0;
					}
					else if (currentMenu == "Options") {
						auto response = processMenu("Options", currentMenuIndex);
						quit = get<0>(response);
						loadNewMenu(get<1>(response));
						currentMenu = get<1>(response);
						currentMenuIndex = 0;
					}
					else if (currentMenu == "Credits") {
						auto response = processMenu("Credits", currentMenuIndex);
						quit = get<0>(response);
						loadNewMenu(get<1>(response));
						currentMenu = get<1>(response);
						currentMenuIndex = 0;
					}
					break;
				case ALLEGRO_KEY_DOWN:
					if (currentMenu == "Title Screen") {
						moveTitleScreenDown(currentMenuIndex);
					}
					else if (currentMenu == "New Simulation") {
						moveNewSimulationScreenDown(currentMenuIndex);
					}
					else if (currentMenu == "Load Simulation") {

					}
					currentMenuIndex++;
					break;
				case ALLEGRO_KEY_S:
					if (currentMenu == "Title Screen") {
						moveTitleScreenDown(currentMenuIndex);
					}
					else if (currentMenu == "New Simulation") {
						moveNewSimulationScreenDown(currentMenuIndex);
					}
					else if (currentMenu == "Load Simulation") {

					}
					currentMenuIndex++;
					break;
				case ALLEGRO_KEY_UP:
					if (currentMenu == "Title Screen") {
						moveTitleScreenUp(currentMenuIndex);
					}
					else if (currentMenu == "New Simulation") {
						moveNewSimulationScreenUp(currentMenuIndex);
					}
					else if (currentMenu == "Load Simulation") {

					}
					currentMenuIndex--;
					break;
				case ALLEGRO_KEY_W:
					if (currentMenu == "Title Screen") {
						moveTitleScreenUp(currentMenuIndex);
					}
					else if (currentMenu == "New Simulation") {
						moveNewSimulationScreenUp(currentMenuIndex);
					}
					else if (currentMenu == "Load Simulation") {

					}
					currentMenuIndex--;
					break;
				}
			}
		}
		 else {
			 switch (event.type) {
			 case ALLEGRO_EVENT_KEY_CHAR:
				 switch (event.keyboard.keycode) {
				 case ALLEGRO_KEY_ENTER:
					 valueInputMode = false;
					 break;
				 case ALLEGRO_KEY_ESCAPE:
					 quit = true;
					 break;
				 case ALLEGRO_KEY_BACKSPACE:
					 if (currentMenu == "New Simulation") {
						 removeCharFromNewSimluationScreenString(currentMenuIndex);
					 }
					 break;
				 default:
					 if (currentMenu == "New Simulation") {
						 updateNewSimulationScreenString(currentMenuIndex, event.keyboard.unichar);
					 }
					 break;
				 }
			 }
		}
    }
    return 0;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Generic Functions
void drawTriangle(float topLeftX, float topLeftY, int direction, ALLEGRO_COLOR colour) {
    if (direction > 0) {
        al_draw_filled_triangle(topLeftX, topLeftY,
            topLeftX + SCREENWIDTH*0.02, topLeftY + SCREENHEIGHT*0.02,
            topLeftX, topLeftY + SCREENHEIGHT* 0.04,
            colour);
    }
    else {
        al_draw_filled_triangle(topLeftX, topLeftY,
            topLeftX - SCREENWIDTH*0.02, topLeftY + SCREENHEIGHT*0.02,
            topLeftX, topLeftY + SCREENHEIGHT* 0.04,
            colour);
    }
}

tuple<bool, string> processMenu(string currentMenu, int currentMenuIndex) {
    if (currentMenu == "Title Screen") {
        currentMenuIndex = normalizeTitleScreenIndex(currentMenuIndex);
        switch (currentMenuIndex) {
        case(0):
            return make_tuple(false, "New Simulation");
        case(1):
            return make_tuple(false, "Load Simulation");
        case(2):
            return make_tuple(false, "Options");
        case(3):
            return make_tuple(false, "Credits");
        case(4):
            return make_tuple(true, "Exiting the game, doesn't matter");
        deafult:
            break;
        }
    }
    else if (currentMenu == "New Simulation") {
        currentMenuIndex = normalizeNewSimulationScreenIndex(currentMenuIndex);
        switch (currentMenuIndex) {
        case(14):
            return make_tuple(false, "Title Screen");
		default: //note, this makes the code smaller to write but it makes the error cases (that shouldn't arise) hard to handle.
			return make_tuple(true, "New Simulation");
		}
    }
    else if (currentMenu == "Load Simulation") {
        currentMenuIndex = normalizeLoadSimulationScreenIndex(currentMenuIndex);
        switch (currentMenuIndex) {
        case(0):
            return make_tuple(false, "Title Screen");
        }
    }
    else if (currentMenu == "Options") {
        return make_tuple(false, "Title Screen");
    }
    else if (currentMenu == "Credits") {
        return make_tuple(false, "Title Screen");
    }
    return make_tuple(false, currentMenu);
}

void loadNewMenu(string newMenu) {
    if (newMenu == "Title Screen") {
        setupTitleScreen();
    }
    else if (newMenu == "New Simulation") {
        setupNewSimulationScreen();
    } 
    else if (newMenu == "Load Simulation") {
        setupLoadSimulationScreen();
    }
    else if (newMenu == "Options") {
        setupOptionsScreen();
    }
    else if (newMenu == "Credits") {
        setupCreditsScreen();
    }
}

int normalizeScreenIndex(int abnormalIndex, int maxMenuIndex) {
	if (abnormalIndex < 0) {
		while (abnormalIndex < 0) {
			abnormalIndex += maxMenuIndex;
		}
		return abnormalIndex;
	}
	else if (abnormalIndex > maxMenuIndex - 1) {
		while (abnormalIndex > maxMenuIndex - 1) {
			abnormalIndex -= maxMenuIndex;
		}
		return abnormalIndex;
	}
	else {
		return abnormalIndex;
	}
}

//Title Screen Functions
void setupTitleScreen() {
    al_set_window_title(mainDisplay, "Project Psi Title Screen");
    al_clear_to_color(screenBackgroundColour);
    al_draw_ustr(screenTitleFont,
        screenOptionsColour,
        SCREENWIDTH*0.5,
        SCREENHEIGHT*0.005,
        ALLEGRO_ALIGN_CENTRE,
        mainMenuScreenTitle
    );
	//Horizontal Bar
    al_draw_rectangle(
        0,
        SCREENHEIGHT*0.193,
        SCREENWIDTH,
        SCREENHEIGHT*0.197,
        screenOptionsColour,
        7
    );
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        SCREENWIDTH*0.5,
        SCREENHEIGHT*0.25,
        ALLEGRO_ALIGN_CENTRE,
        newSimulationString
    );
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        SCREENWIDTH*0.5,
        SCREENHEIGHT*0.40,
        ALLEGRO_ALIGN_CENTRE,
        loadSimulationString
    );
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        SCREENWIDTH*0.5,
        SCREENHEIGHT*0.55,
        ALLEGRO_ALIGN_CENTRE,
        optionsString
    );
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        SCREENWIDTH*0.5,
        SCREENHEIGHT*0.70,
        ALLEGRO_ALIGN_CENTRE,
        creditsString
    );
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        SCREENWIDTH*0.5,
        SCREENHEIGHT*0.85,
        ALLEGRO_ALIGN_CENTRE,
        quitString
    );
    drawTriangle(float(SCREENWIDTH)*0.35, float(SCREENHEIGHT)*0.285, 1, screenOptionsColour);
    drawTriangle(float(SCREENWIDTH)*0.65, float(SCREENHEIGHT)*0.285, -1, screenOptionsColour);
    al_flip_display();
}

int normalizeTitleScreenIndex(int abnormalIndex) {
	return normalizeScreenIndex(abnormalIndex, titleScreenMenuItems);
}

void moveTitleScreenDown(int currentMenuIndex) {
    drawTitleScreenWithSelection(currentMenuIndex, currentMenuIndex + 1);
}

void moveTitleScreenUp(int currentMenuIndex) {
    drawTitleScreenWithSelection(currentMenuIndex, currentMenuIndex - 1);
}

void drawTitleScreenWithSelection(int previousSelection, int newSelection) {
    //These are in format leftTriangleX1, triangleY, rightTriangleX1
    float titleScreenArrows[][3] = {
        { float(SCREENWIDTH)*0.35, float(SCREENHEIGHT)*0.285, float(SCREENWIDTH)*0.65 },
        { float(SCREENWIDTH)*0.345, float(SCREENHEIGHT)*0.435, float(SCREENWIDTH)*0.665 },
        { float(SCREENWIDTH)*0.4, float(SCREENHEIGHT)*0.585, float(SCREENWIDTH)*0.6 },
        { float(SCREENWIDTH)*0.41, float(SCREENHEIGHT)*0.735, float(SCREENWIDTH)*0.59 },
        { float(SCREENWIDTH)*0.43, float(SCREENHEIGHT)*0.885, float(SCREENWIDTH)*0.57 },
    };

	previousSelection = normalizeTitleScreenIndex(previousSelection);
	newSelection = normalizeTitleScreenIndex(newSelection);

    al_flip_display();
    drawTriangle(titleScreenArrows[previousSelection][0], titleScreenArrows[previousSelection][1], 1, screenBackgroundColour);
    drawTriangle(titleScreenArrows[previousSelection][2], titleScreenArrows[previousSelection][1], -1, screenBackgroundColour);
    drawTriangle(titleScreenArrows[newSelection][0], titleScreenArrows[newSelection][1], 1, screenOptionsColour);
    drawTriangle(titleScreenArrows[newSelection][2], titleScreenArrows[newSelection][1], -1, screenOptionsColour);
    al_flip_display();
}

//New Simulation Screen Functions
void setupNewSimulationScreen() {
    al_clear_to_color(screenBackgroundColour);
    al_draw_ustr(screenTitleFont,
        screenOptionsColour,
        SCREENWIDTH*0.5,
        SCREENHEIGHT*0.005,
        ALLEGRO_ALIGN_CENTRE,
        newSimulationScreenTitle
    );
	//Horizontal Bar
    al_draw_rectangle(
        0,
        SCREENHEIGHT*0.193,
        SCREENWIDTH,
        SCREENHEIGHT*0.197,
        screenOptionsColour,
        7
    );
	//Vertical Bar
    al_draw_rectangle(
        SCREENWIDTH*0.4995,
        SCREENHEIGHT*0.193,
        SCREENWIDTH*0.5005,
        SCREENHEIGHT*0.903,
        screenOptionsColour,
        1
    );
	//Lefthand Side Options
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.1,
		SCREENHEIGHT*0.2,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationLeftp1prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.2,
		SCREENHEIGHT*0.2,
		ALLEGRO_ALIGN_LEFT,
		newSimulationLeftp1value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.1,
		SCREENHEIGHT*0.3,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationLeftp2prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.2,
		SCREENHEIGHT*0.3,
		ALLEGRO_ALIGN_LEFT,
		newSimulationLeftp2value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.1,
		SCREENHEIGHT*0.4,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationLeftp3prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.2,
		SCREENHEIGHT*0.4,
		ALLEGRO_ALIGN_LEFT,
		newSimulationLeftp3value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.1,
		SCREENHEIGHT*0.5,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationLeftp4prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.2,
		SCREENHEIGHT*0.5,
		ALLEGRO_ALIGN_LEFT,
		newSimulationLeftp4value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.1,
		SCREENHEIGHT*0.6,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationLeftp5prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.2,
		SCREENHEIGHT*0.6,
		ALLEGRO_ALIGN_LEFT,
		newSimulationLeftp5value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.1,
		SCREENHEIGHT*0.7,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationLeftp6prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.2,
		SCREENHEIGHT*0.7,
		ALLEGRO_ALIGN_LEFT,
		newSimulationLeftp6value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.1,
		SCREENHEIGHT*0.8,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationLeftp7prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.2,
		SCREENHEIGHT*0.8,
		ALLEGRO_ALIGN_LEFT,
		newSimulationLeftp7value
	);
	//Righthand Side Options
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.6,
		SCREENHEIGHT*0.2,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationRightp1prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.7,
		SCREENHEIGHT*0.2,
		ALLEGRO_ALIGN_LEFT,
		newSimulationRightp1value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.6,
		SCREENHEIGHT*0.3,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationRightp2prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.7,
		SCREENHEIGHT*0.3,
		ALLEGRO_ALIGN_LEFT,
		newSimulationRightp2value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.6,
		SCREENHEIGHT*0.4,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationRightp3prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.7,
		SCREENHEIGHT*0.4,
		ALLEGRO_ALIGN_LEFT,
		newSimulationRightp3value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.6,
		SCREENHEIGHT*0.5,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationRightp4prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.7,
		SCREENHEIGHT*0.5,
		ALLEGRO_ALIGN_LEFT,
		newSimulationRightp4value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.6,
		SCREENHEIGHT*0.6,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationRightp5prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.7,
		SCREENHEIGHT*0.6,
		ALLEGRO_ALIGN_LEFT,
		newSimulationRightp5value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.6,
		SCREENHEIGHT*0.7,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationRightp6prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.7,
		SCREENHEIGHT*0.7,
		ALLEGRO_ALIGN_LEFT,
		newSimulationRightp6value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.6,
		SCREENHEIGHT*0.8,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationRightp7prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH*0.7,
		SCREENHEIGHT*0.8,
		ALLEGRO_ALIGN_LEFT,
		newSimulationRightp7value
	);
	//Horizontal Bar
	al_draw_rectangle(
		0,
		SCREENHEIGHT*0.903,
		SCREENWIDTH,
		SCREENHEIGHT*0.907,
		screenOptionsColour,
		7
	);
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        SCREENWIDTH*0.5,
        SCREENHEIGHT*0.9,
        ALLEGRO_ALIGN_CENTRE,
        newSimulationGoBackString
    );
    drawTriangle(float(SCREENWIDTH)*0.49, float(SCREENHEIGHT)*0.235, -1, screenOptionsColour);
    al_flip_display();
}

int normalizeNewSimulationScreenIndex(int abnormalIndex) {
	return normalizeScreenIndex(abnormalIndex, newSimulationScreenMenuItems);
}

void moveNewSimulationScreenDown(int currentMenuIndex) {
	drawNewSimulationScreenWithSelection(currentMenuIndex, currentMenuIndex + 1);
}

void moveNewSimulationScreenUp(int currentMenuIndex) {
	drawNewSimulationScreenWithSelection(currentMenuIndex, currentMenuIndex - 1);
}

void drawNewSimulationScreenWithSelection(int previousSelection, int newSelection) {
	//These are in format leftTriangleX1, triangleY, rightTriangleX1
	float newSimulationScreenArrows[][3] = {
		{ float(SCREENWIDTH)*0.49, float(SCREENHEIGHT)*0.235, 0},
		{ float(SCREENWIDTH)*0.49, float(SCREENHEIGHT)*0.335, 0},
		{ float(SCREENWIDTH)*0.49, float(SCREENHEIGHT)*0.435, 0},
		{ float(SCREENWIDTH)*0.49, float(SCREENHEIGHT)*0.535, 0},
		{ float(SCREENWIDTH)*0.49, float(SCREENHEIGHT)*0.635, 0},
		{ float(SCREENWIDTH)*0.49, float(SCREENHEIGHT)*0.735, 0},
		{ float(SCREENWIDTH)*0.49, float(SCREENHEIGHT)*0.835, 0},
		{ float(SCREENWIDTH)*0.99, float(SCREENHEIGHT)*0.235, 0},
		{ float(SCREENWIDTH)*0.99, float(SCREENHEIGHT)*0.335, 0},
		{ float(SCREENWIDTH)*0.99, float(SCREENHEIGHT)*0.435, 0},
		{ float(SCREENWIDTH)*0.99, float(SCREENHEIGHT)*0.535, 0},
		{ float(SCREENWIDTH)*0.99, float(SCREENHEIGHT)*0.635, 0},
		{ float(SCREENWIDTH)*0.99, float(SCREENHEIGHT)*0.735, 0},
		{ float(SCREENWIDTH)*0.99, float(SCREENHEIGHT)*0.835, 0},
		{ float(SCREENWIDTH)*0.4, float(SCREENHEIGHT)*0.935, float(SCREENWIDTH)*0.6}
	};

	previousSelection = normalizeNewSimulationScreenIndex(previousSelection);
	newSelection = normalizeNewSimulationScreenIndex(newSelection);

	al_flip_display();
	if (newSelection == newSimulationScreenMenuItems-1) {
		drawTriangle(newSimulationScreenArrows[previousSelection][0], newSimulationScreenArrows[previousSelection][1], -1, screenBackgroundColour);
		drawTriangle(newSimulationScreenArrows[newSelection][0], newSimulationScreenArrows[newSelection][1], 1, screenOptionsColour);
		drawTriangle(newSimulationScreenArrows[newSelection][2], newSimulationScreenArrows[newSelection][1], -1, screenOptionsColour);
	}
	else if (previousSelection == newSimulationScreenMenuItems-1) {
		drawTriangle(newSimulationScreenArrows[previousSelection][0], newSimulationScreenArrows[previousSelection][1], 1, screenBackgroundColour);
		drawTriangle(newSimulationScreenArrows[previousSelection][2], newSimulationScreenArrows[previousSelection][1], -1, screenBackgroundColour);
		drawTriangle(newSimulationScreenArrows[newSelection][0], newSimulationScreenArrows[newSelection][1], -1, screenOptionsColour);
	}
	else {
		drawTriangle(newSimulationScreenArrows[previousSelection][0], newSimulationScreenArrows[previousSelection][1], -1, screenBackgroundColour);
		drawTriangle(newSimulationScreenArrows[newSelection][0], newSimulationScreenArrows[newSelection][1], -1, screenOptionsColour);
	}
	al_flip_display();
}

void updateNewSimulationScreenString(int currentMenuItemIndex, char updateChar) {
	currentMenuItemIndex = normalizeNewSimulationScreenIndex(currentMenuItemIndex);
	auto screenItem = allNewSimulationScreenOptions[currentMenuItemIndex];
	auto screenPositions = allNewSimulationScreenPositions[currentMenuItemIndex];
	int rectangleEndPosition = 0;
	if (currentMenuItemIndex > 0 || currentMenuItemIndex < 8) {
		rectangleEndPosition = SCREENWIDTH * 0.45;
	}
	else {
		rectangleEndPosition = SCREENWIDTH;
	}
	al_flip_display();
	al_draw_filled_rectangle(
		SCREENWIDTH * (get<0>(screenPositions)),
		SCREENHEIGHT * (get<1>(screenPositions) + 0.015),
		rectangleEndPosition,
		SCREENHEIGHT * (get<1>(screenPositions) + 0.095),
		screenBackgroundColour
	);
	al_ustr_append_chr(&get<1>(screenItem), updateChar);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH * get<0>(screenPositions),
		SCREENHEIGHT * get<1>(screenPositions),
		ALLEGRO_ALIGN_LEFT,
		&get<1>(screenItem)
	);
	al_flip_display();
	get<1>(allNewSimulationScreenOptions[currentMenuItemIndex]) = get<1>(screenItem);
}

void removeCharFromNewSimluationScreenString(int currentMenuItemIndex) {
	currentMenuItemIndex = normalizeNewSimulationScreenIndex(currentMenuItemIndex);
	auto screenItem = allNewSimulationScreenOptions[currentMenuItemIndex];
	auto screenPositions = allNewSimulationScreenPositions[currentMenuItemIndex];
	int rectangleEndPosition = 0;
	if (currentMenuItemIndex > 0 || currentMenuItemIndex < 8) {
		rectangleEndPosition = SCREENWIDTH * 0.45;
	}
	else {
		rectangleEndPosition = SCREENWIDTH;
	}
	al_flip_display();
	al_draw_filled_rectangle(
		SCREENWIDTH * (get<0>(screenPositions)),
		SCREENHEIGHT * (get<1>(screenPositions) + 0.015),
		rectangleEndPosition,
		SCREENHEIGHT * (get<1>(screenPositions) + 0.095),
		screenBackgroundColour
	);
	al_ustr_remove_chr(&get<1>(screenItem), al_ustr_offset(&get<1>(screenItem), al_ustr_length(&get<1>(screenItem))-1));
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		SCREENWIDTH * get<0>(screenPositions),
		SCREENHEIGHT * get<1>(screenPositions),
		ALLEGRO_ALIGN_LEFT,
		&get<1>(screenItem)
	);
	al_flip_display();
	get<1>(allNewSimulationScreenOptions[currentMenuItemIndex]) = get<1>(screenItem);
}


//Load Simulation Screen Functions
void setupLoadSimulationScreen()
{
    al_clear_to_color(screenBackgroundColour);
    al_draw_ustr(screenTitleFont,
        screenOptionsColour,
        SCREENWIDTH*0.5,
        SCREENHEIGHT*0.005,
        ALLEGRO_ALIGN_CENTRE,
        loadSimulationScreenTitle
    );
	//Horizontal Bar
    al_draw_rectangle(
        0,
        SCREENHEIGHT*0.193,
        SCREENWIDTH,
        SCREENHEIGHT*0.197,
        screenOptionsColour,
        7
    );
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        SCREENWIDTH*0.5,
        SCREENHEIGHT*0.5,
        ALLEGRO_ALIGN_CENTRE,
        loadSimulationStringOne
    );
	//Horizontal Bar
	al_draw_rectangle(
		0,
		SCREENHEIGHT*0.903,
		SCREENWIDTH,
		SCREENHEIGHT*0.907,
		screenOptionsColour,
		7
	);
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        SCREENWIDTH*0.5,
        SCREENHEIGHT*0.90,
        ALLEGRO_ALIGN_CENTRE,
        loadSimulationGoBackString
    );
    drawTriangle(float(SCREENWIDTH)*0.4, float(SCREENHEIGHT)*0.935, 1, screenOptionsColour);
    drawTriangle(float(SCREENWIDTH)*0.6, float(SCREENHEIGHT)*0.935, -1, screenOptionsColour);
    al_flip_display();
}

int normalizeLoadSimulationScreenIndex(int abnormalIndex) {
	return normalizeScreenIndex(abnormalIndex, loadSimulationScreenMenuItems);
}

//Options Screen Functions
void setupOptionsScreen()
{
    al_clear_to_color(screenBackgroundColour);
    al_draw_ustr(screenTitleFont,
        screenOptionsColour,
        SCREENWIDTH*0.5,
        SCREENHEIGHT*0.005,
        ALLEGRO_ALIGN_CENTRE,
        optionsScreenTitle
    );
	//Horizontal Bar
    al_draw_rectangle(
        0,
        SCREENHEIGHT*0.193,
        SCREENWIDTH,
        SCREENHEIGHT*0.197,
        screenOptionsColour,
        7
    );
    al_draw_ustr(screenOptionsSmallFont,
        screenOptionsColour,
        SCREENWIDTH*0.005,
        SCREENHEIGHT*0.2,
        ALLEGRO_ALIGN_LEFT,
        optionsStringOne
    );
    al_draw_ustr(screenOptionsSmallFont,
        screenOptionsColour,
        SCREENWIDTH*0.005,
        SCREENHEIGHT*0.28,
        ALLEGRO_ALIGN_LEFT,
        optionsStringTwo
    );
    al_draw_ustr(screenOptionsSmallFont,
        screenOptionsColour,
        SCREENWIDTH*0.005,
        SCREENHEIGHT*0.36,
        ALLEGRO_ALIGN_LEFT,
        optionsStringThree
    );
    al_draw_ustr(screenOptionsSmallFont,
        screenOptionsColour,
        SCREENWIDTH*0.005,
        SCREENHEIGHT*0.44,
        ALLEGRO_ALIGN_LEFT,
        optionsStringFour
    );
    al_draw_ustr(screenOptionsSmallFont,
        screenOptionsColour,
        SCREENWIDTH*0.005,
        SCREENHEIGHT*0.52,
        ALLEGRO_ALIGN_LEFT,
        optionsStringFive
    );
	//Horizontal Bar
	al_draw_rectangle(
		0,
		SCREENHEIGHT*0.903,
		SCREENWIDTH,
		SCREENHEIGHT*0.907,
		screenOptionsColour,
		7
	);
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        SCREENWIDTH*0.5,
        SCREENHEIGHT*0.9,
        ALLEGRO_ALIGN_CENTRE,
        optionsGoBackString
    );
    drawTriangle(float(SCREENWIDTH)*0.4, float(SCREENHEIGHT)*0.935, 1, screenOptionsColour);
    drawTriangle(float(SCREENWIDTH)*0.6, float(SCREENHEIGHT)*0.935, -1, screenOptionsColour);
    al_flip_display();
}

//Credits Screen Functions
void setupCreditsScreen()
{
    al_clear_to_color(screenBackgroundColour);
    al_draw_ustr(screenTitleFont,
        screenOptionsColour,
        SCREENWIDTH*0.5,
        SCREENHEIGHT*0.005,
        ALLEGRO_ALIGN_CENTRE,
        creditsScreenTitle
    );
	//Horizontal Bar
    al_draw_rectangle(
        0,
        SCREENHEIGHT*0.193,
        SCREENWIDTH,
        SCREENHEIGHT*0.197,
        screenOptionsColour,
        7
    );
    al_draw_ustr(screenOptionsSmallFont,
        screenOptionsColour,
        SCREENWIDTH*0.005,
        SCREENHEIGHT*0.2,
        ALLEGRO_ALIGN_LEFT,
        creditsStringOne
    );
    al_draw_ustr(screenOptionsSmallFont,
        screenOptionsColour,
        SCREENWIDTH*0.005,
        SCREENHEIGHT*0.28,
        ALLEGRO_ALIGN_LEFT,
        creditsStringTwo
    );
    al_draw_ustr(screenOptionsSmallFont,
        screenOptionsColour,
        SCREENWIDTH*0.005,
        SCREENHEIGHT*0.36,
        ALLEGRO_ALIGN_LEFT,
        creditsStringThree
    );
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        SCREENWIDTH*0.5,
        SCREENHEIGHT*0.70,
        ALLEGRO_ALIGN_CENTRE,
        creditsStringFour
    );
	//Horizontal Bar
	al_draw_rectangle(
		0,
		SCREENHEIGHT*0.903,
		SCREENWIDTH,
		SCREENHEIGHT*0.907,
		screenOptionsColour,
		7
	);
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        SCREENWIDTH*0.5,
        SCREENHEIGHT*0.9,
        ALLEGRO_ALIGN_CENTRE,
        creditsGoBackString
    );
    drawTriangle(float(SCREENWIDTH)*0.4, float(SCREENHEIGHT)*0.935, 1, screenOptionsColour);
    drawTriangle(float(SCREENWIDTH)*0.6, float(SCREENHEIGHT)*0.935, -1, screenOptionsColour);
    al_flip_display();
}

//Initialization Functions
int initAddons() {
	const char * fontPath = "assets\\testFont.ttf";
    if (!al_init() && !al_init_font_addon() && !al_install_keyboard()) {
        cout << "failed to initialize allegro!" << endl;
        return -1;
    }
    if (!al_init_font_addon()) {
        cout << "failed to initialize the font addon!" << endl;
        return -1;
    }
    if (!al_init_ttf_addon()) {
        cout << "failed to initialize the ttf font addon!" << endl;
        return -1;
    }
    if (!al_install_keyboard()) {
        cout << "failed to initialize the keyboard!" << endl;
        return -1;
    }
    if (!al_init_primitives_addon()) {
        cout << "failed to initialize the primitives addon!" << endl;
        return -1;
    }
    settingsDisplay = al_create_display(SCREENWIDTH, SCREENHEIGHT);
    if (!settingsDisplay) {
        cout << "failed to create display!" << endl;
        return -1;
    }
    screenOptionsFont = al_load_ttf_font(fontPath, SCREENWIDTH / 25.6, 0);
    if (!screenOptionsFont) {
        cout << "Could not load \"testFont.ttf\"" << endl;
        cout << "Make sure the correct font is in the executable location!" << endl;
        screenOptionsFont = al_create_builtin_font();
    }
    screenOptionsSmallFont = al_load_ttf_font(fontPath, SCREENWIDTH / 36.6, 0);
    if (!screenOptionsSmallFont) {
        cout << "Could not load \"testFont.ttf\"" << endl;
        cout << "Make sure the correct font is in the executable location!" << endl;
        screenOptionsSmallFont = al_create_builtin_font();
    }
    screenTitleFont = al_load_ttf_font(fontPath, SCREENWIDTH / 12.8, 0);
    if (!screenTitleFont) {
        cout << "Could not load \"testFont.ttf\"" << endl;
        cout << "Make sure the correct font is in the executable location!" << endl;
        screenTitleFont = al_create_builtin_font();
    }
    mainEventQueue = al_create_event_queue();
    al_register_event_source(mainEventQueue, al_get_display_event_source(settingsDisplay));
    al_register_event_source(mainEventQueue, al_get_keyboard_event_source());
    al_set_window_title(mainDisplay, "Project Psi Launcher");
}

//List of Bugs to track down

//Todo in the future
    //Get the menu system working with the mouse as well, for now keyboard controls will have to work
    //Setup the new simulation menu
		//Still need to parse the values from the ustr values.
		//Also need to make sure that the strings don't excede a maximum length visible
			//This means this display will overflow, its hard to draw text on a screen it turns out

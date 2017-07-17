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
static int screenWidth;
static int screenHeight;

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
ALLEGRO_USTR *newSimulationGoBackString = al_ustr_new("Go Back");
const int newSimulationScreenMenuItems = 1; //Don't count the title in here
ALLEGRO_USTR *allNewSimulationScreenOptions[newSimulationScreenMenuItems] = {
    newSimulationGoBackString
}; //add new menu options to this array, make sure to increment maxMenuItems, so far this is just for us to keep track of them

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

//Title Screen Functions
void setupTitleScreen();
int normalizeTitleScreenIndex(int);
void moveTitleScreenDown(int, int);
void moveTitleScreenUp(int, int);
void drawTitleScreenWithSelection(int, int, int);

//New Simulation Functions
void setupNewSimulationScreen();
int normalizeNewSimulationScreenIndex(int);

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

    int currentMenuIndex = 0;
    string currentMenu = "Title Screen";
    while (!quit) {
        ALLEGRO_EVENT event;
        al_wait_for_event(mainEventQueue, &event);
        switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE: //This triggers when you hit the x on the window
            quit = true;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
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
                    quit = get<0>(response);
                    loadNewMenu(get<1>(response));
                    currentMenu = get<1>(response);
                    currentMenuIndex = 0;
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
                    moveTitleScreenDown(currentMenuIndex, titleScreenMenuItems);
                }
                else if (currentMenu == "New Simulation") {

                }
                else if (currentMenu == "Load Simulation") {

                }
                currentMenuIndex++;
                break;
            case ALLEGRO_KEY_S:
                if (currentMenu == "Title Screen") {
                    moveTitleScreenDown(currentMenuIndex, titleScreenMenuItems);
                }
                else if (currentMenu == "New Simulation") {

                }
                else if (currentMenu == "Load Simulation") {

                }
                currentMenuIndex++;
                break;
            case ALLEGRO_KEY_UP:
                if (currentMenu == "Title Screen") {
                    moveTitleScreenUp(currentMenuIndex, titleScreenMenuItems);
                }
                else if (currentMenu == "New Simulation") {

                }
                else if (currentMenu == "Load Simulation") {

                }
                currentMenuIndex--;
                break;
            case ALLEGRO_KEY_W:
                if (currentMenu == "Title Screen") {
                    moveTitleScreenUp(currentMenuIndex, titleScreenMenuItems);
                }
                else if (currentMenu == "New Simulation") {

                }
                else if (currentMenu == "Load Simulation") {

                }
                currentMenuIndex--;
                break;
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
            topLeftX + screenWidth*0.02, topLeftY + screenHeight*0.02,
            topLeftX, topLeftY + screenHeight* 0.04,
            colour);
    }
    else {
        al_draw_filled_triangle(topLeftX, topLeftY,
            topLeftX - screenWidth*0.02, topLeftY + screenHeight*0.02,
            topLeftX, topLeftY + screenHeight* 0.04,
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
        case(0):
            return make_tuple(false, "Title Screen");
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

//Title Screen Functions
void setupTitleScreen() {
    al_set_window_title(mainDisplay, "Project Psi Title Screen");
    al_clear_to_color(screenBackgroundColour);
    al_draw_ustr(screenTitleFont,
        screenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.005,
        ALLEGRO_ALIGN_CENTRE,
        mainMenuScreenTitle
    );
    al_draw_rectangle(
        0,
        screenHeight*0.193,
        screenWidth,
        screenHeight*0.197,
        screenOptionsColour,
        7
    );
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.25,
        ALLEGRO_ALIGN_CENTRE,
        newSimulationString
    );
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.40,
        ALLEGRO_ALIGN_CENTRE,
        loadSimulationString
    );
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.55,
        ALLEGRO_ALIGN_CENTRE,
        optionsString
    );
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.70,
        ALLEGRO_ALIGN_CENTRE,
        creditsString
    );
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.85,
        ALLEGRO_ALIGN_CENTRE,
        quitString
    );
    drawTriangle(float(screenWidth)*0.35, float(screenHeight)*0.285, 1, screenOptionsColour);
    drawTriangle(float(screenWidth)*0.65, float(screenHeight)*0.285, -1, screenOptionsColour);
    al_flip_display();
}

int normalizeTitleScreenIndex(int abnormalIndex) {
    return abs(abnormalIndex) % titleScreenMenuItems;
}

void moveTitleScreenDown(int currentMenuIndex, int maxMenuItems) {
    drawTitleScreenWithSelection(currentMenuIndex, currentMenuIndex + 1, maxMenuItems);
}

void moveTitleScreenUp(int currentMenuIndex, int maxMenuItems) {
    drawTitleScreenWithSelection(currentMenuIndex, currentMenuIndex - 1, maxMenuItems);
}

void drawTitleScreenWithSelection(int previousSelection, int newSelection, int maxMenuItems) {
    //These are in format leftTriangleX1, triangleY, rightTriangleX1
    float titleScreenArrows[][3] = {
        { float(screenWidth)*0.35, float(screenHeight)*0.285, float(screenWidth)*0.65 },
        { float(screenWidth)*0.345, float(screenHeight)*0.435, float(screenWidth)*0.665 },
        { float(screenWidth)*0.4, float(screenHeight)*0.585, float(screenWidth)*0.6 },
        { float(screenWidth)*0.41, float(screenHeight)*0.735, float(screenWidth)*0.59 },
        { float(screenWidth)*0.43, float(screenHeight)*0.885, float(screenWidth)*0.57 },
    };

    al_flip_display();
    previousSelection = abs(previousSelection % maxMenuItems);
    newSelection = abs(newSelection % maxMenuItems);
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
        screenWidth*0.5,
        screenHeight*0.005,
        ALLEGRO_ALIGN_CENTRE,
        newSimulationScreenTitle
    );
    al_draw_rectangle(
        0,
        screenHeight*0.193,
        screenWidth,
        screenHeight*0.197,
        screenOptionsColour,
        7
    );
    al_draw_rectangle(
        screenWidth*0.4995,
        screenHeight*0.193,
        screenWidth*0.5005,
        screenHeight*0.84,
        screenOptionsColour,
        1
    );    
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.85,
        ALLEGRO_ALIGN_CENTRE,
        newSimulationGoBackString
    );
    drawTriangle(float(screenWidth)*0.4, float(screenHeight)*0.885, 1, screenOptionsColour);
    drawTriangle(float(screenWidth)*0.6, float(screenHeight)*0.885, -1, screenOptionsColour);
    al_flip_display();
}

int normalizeNewSimulationScreenIndex(int abnormalIndex) {
    return abs(abnormalIndex) % newSimulationScreenMenuItems;
}

//Load Simulation Screen Functions
void setupLoadSimulationScreen()
{
    al_clear_to_color(screenBackgroundColour);
    al_draw_ustr(screenTitleFont,
        screenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.005,
        ALLEGRO_ALIGN_CENTRE,
        loadSimulationScreenTitle
    );
    al_draw_rectangle(
        0,
        screenHeight*0.193,
        screenWidth,
        screenHeight*0.197,
        screenOptionsColour,
        7
    );
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.5,
        ALLEGRO_ALIGN_CENTRE,
        loadSimulationStringOne
    );
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.85,
        ALLEGRO_ALIGN_CENTRE,
        loadSimulationGoBackString
    );
    drawTriangle(float(screenWidth)*0.4, float(screenHeight)*0.885, 1, screenOptionsColour);
    drawTriangle(float(screenWidth)*0.6, float(screenHeight)*0.885, -1, screenOptionsColour);
    al_flip_display();
}

int normalizeLoadSimulationScreenIndex(int abnormalIndex) {
    return abs(abnormalIndex) % loadSimulationScreenMenuItems;
}

//Options Screen Functions
void setupOptionsScreen()
{
    al_clear_to_color(screenBackgroundColour);
    al_draw_ustr(screenTitleFont,
        screenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.005,
        ALLEGRO_ALIGN_CENTRE,
        optionsScreenTitle
    );
    al_draw_rectangle(
        0,
        screenHeight*0.193,
        screenWidth,
        screenHeight*0.197,
        screenOptionsColour,
        7
    );
    al_draw_ustr(screenOptionsSmallFont,
        screenOptionsColour,
        screenWidth*0.005,
        screenHeight*0.2,
        ALLEGRO_ALIGN_LEFT,
        optionsStringOne
    );
    al_draw_ustr(screenOptionsSmallFont,
        screenOptionsColour,
        screenWidth*0.005,
        screenHeight*0.28,
        ALLEGRO_ALIGN_LEFT,
        optionsStringTwo
    );
    al_draw_ustr(screenOptionsSmallFont,
        screenOptionsColour,
        screenWidth*0.005,
        screenHeight*0.36,
        ALLEGRO_ALIGN_LEFT,
        optionsStringThree
    );
    al_draw_ustr(screenOptionsSmallFont,
        screenOptionsColour,
        screenWidth*0.005,
        screenHeight*0.44,
        ALLEGRO_ALIGN_LEFT,
        optionsStringFour
    );
    al_draw_ustr(screenOptionsSmallFont,
        screenOptionsColour,
        screenWidth*0.005,
        screenHeight*0.52,
        ALLEGRO_ALIGN_LEFT,
        optionsStringFive
    );
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.85,
        ALLEGRO_ALIGN_CENTRE,
        optionsGoBackString
    );
    drawTriangle(float(screenWidth)*0.4, float(screenHeight)*0.885, 1, screenOptionsColour);
    drawTriangle(float(screenWidth)*0.6, float(screenHeight)*0.885, -1, screenOptionsColour);
    al_flip_display();
}

//Credits Screen Functions
void setupCreditsScreen()
{
    al_clear_to_color(screenBackgroundColour);
    al_draw_ustr(screenTitleFont,
        screenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.005,
        ALLEGRO_ALIGN_CENTRE,
        creditsScreenTitle
    );
    al_draw_rectangle(
        0,
        screenHeight*0.193,
        screenWidth,
        screenHeight*0.197,
        screenOptionsColour,
        7
    );
    al_draw_ustr(screenOptionsSmallFont,
        screenOptionsColour,
        screenWidth*0.005,
        screenHeight*0.2,
        ALLEGRO_ALIGN_LEFT,
        creditsStringOne
    );
    al_draw_ustr(screenOptionsSmallFont,
        screenOptionsColour,
        screenWidth*0.005,
        screenHeight*0.28,
        ALLEGRO_ALIGN_LEFT,
        creditsStringTwo
    );
    al_draw_ustr(screenOptionsSmallFont,
        screenOptionsColour,
        screenWidth*0.005,
        screenHeight*0.36,
        ALLEGRO_ALIGN_LEFT,
        creditsStringThree
    );
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.70,
        ALLEGRO_ALIGN_CENTRE,
        creditsStringFour
    );
    al_draw_ustr(screenOptionsFont,
        screenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.85,
        ALLEGRO_ALIGN_CENTRE,
        creditsGoBackString
    );
    drawTriangle(float(screenWidth)*0.4, float(screenHeight)*0.885, 1, screenOptionsColour);
    drawTriangle(float(screenWidth)*0.6, float(screenHeight)*0.885, -1, screenOptionsColour);
    al_flip_display();
}

//Initialization Functions
int initAddons() {
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
    settingsDisplay = al_create_display(1280, 720);
    if (!settingsDisplay) {
        cout << "failed to create display!" << endl;
        return -1;
    }

    screenOptionsFont = al_load_ttf_font("C:/Users/Bryton/Desktop/projectPsiResources/testFont.ttf", 50, 0);
    if (!screenOptionsFont) {
        cout << "Could not load \"testFont.ttf\"" << endl;
        cout << "Make sure the correct font is in the executable location!" << endl;
        screenOptionsFont = al_create_builtin_font();
    }

    screenOptionsSmallFont = al_load_ttf_font("C:/Users/Bryton/Desktop/projectPsiResources/testFont.ttf", 35, 0);
    if (!screenOptionsSmallFont) {
        cout << "Could not load \"testFont.ttf\"" << endl;
        cout << "Make sure the correct font is in the executable location!" << endl;
        screenOptionsSmallFont = al_create_builtin_font();
    }

    screenTitleFont = al_load_ttf_font("C:/Users/Bryton/Desktop/projectPsiResources/testFont.ttf", 108, 0);
    if (!screenTitleFont) {
        cout << "Could not load \"testFont.ttf\"" << endl;
        cout << "Make sure the correct font is in the executable location!" << endl;
        screenTitleFont = al_create_builtin_font();
    }

    mainEventQueue = al_create_event_queue();
    al_register_event_source(mainEventQueue, al_get_display_event_source(settingsDisplay));
    al_register_event_source(mainEventQueue, al_get_keyboard_event_source());
    screenHeight = al_get_display_height(settingsDisplay);
    screenWidth = al_get_display_width(settingsDisplay);
    al_set_window_title(mainDisplay, "Project Psi Launcher");
}

//List of Bugs to track down
    //Sometimes when navigating through the menus, the up/down arrow keys will swap directional functionalities
        //To replicate: Go into and out of menus a bunch and press the up/down arrows
        //This seems to happen with negative values, probably just doing a check wrong

//Todo in the future
    //Get the menu system working with the mouse as well, for now keyboard controls will have to work
    //Figure out how to load in fonts from the Resource Files location isntead of the main menu
    //Setup the new simulation menu
    //setup the load simulation menu
    //setup the options menu
    //setup the credits menu
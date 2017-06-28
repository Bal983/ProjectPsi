//C++ Includes
#include <iostream>
#include <stdio.h>

//Our Includes
#include "mainMenu.h"

//Allegro Includes
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

mainMenu::mainMenu(int screenWidth, int screenHeight)
{
    myDisplay = NULL;
    myTextColour = al_map_rgb_f(0.8706, 0.7216, 0.5294); //burlywood colour
    myBackgroundColour = al_map_rgb_f(0, 0, 0); //black colour
    myOptionsFont = NULL;
    myTitleFont = NULL;
    myEventQueue;
    titleString = al_ustr_new("Project Psi");
    newSimulationString = al_ustr_new("New Simulation");
    loadSimulationString = al_ustr_new("Load Simulation");
    optionsString = al_ustr_new("Options");
    creditsString = al_ustr_new("Credits");
    quitString = al_ustr_new("Quit");

    //When adding new menu options, add them to this array and modify the maxMenuItems value in the .h file
    allTitleScreenOptions[0] = newSimulationString;
    allTitleScreenOptions[1] = loadSimulationString;
    allTitleScreenOptions[2] = optionsString;
    allTitleScreenOptions[3] = creditsString;
    allTitleScreenOptions[4] = quitString;

    myScreenWidth = screenWidth;
    myScreenHeight = screenHeight;
    float trianglePositions[maxMenuItems][4] = {
        { float(screenWidth)*0.35, float(screenHeight)*0.285, float(screenWidth)*0.65, float(screenHeight)*0.285 },
        { float(screenWidth)*0.345, float(screenHeight)*0.435, float(screenWidth)*0.665, float(screenHeight)*0.435 },
        { float(screenWidth)*0.4, float(screenHeight)*0.585, float(screenWidth)*0.6, float(screenHeight)*0.585 },
        { float(screenWidth)*0.41, float(screenHeight)*0.735, float(screenWidth)*0.59, float(screenHeight)*0.735 },
        { float(screenWidth)*0.43, float(screenHeight)*0.885, float(screenWidth)*0.57, float(screenHeight)*0.885 },
    };
    initAddons(screenWidth, screenHeight);
    setupMenu();
}

mainMenu::~mainMenu()
{
}

void mainMenu::initAddons(int screenWidth, int screenHeight) {
    if (!al_init() && !al_init_font_addon() && !al_install_keyboard()) {
        cout << "failed to initialize allegro!" << endl;
    }

    if (!al_init_font_addon()) {
        cout << "failed to initialize the font addon!" << endl;
    }

    if (!al_init_ttf_addon()) {
        cout << "failed to initialize the ttf font addon!" << endl;
    }

    if (!al_install_keyboard()) {
        cout << "failed to initialize the keyboard!" << endl;
    }

    if (!al_init_primitives_addon()) {
        cout << "failed to initialize the primitives addon!" << endl;
    }

    myDisplay = al_create_display(1280, 720);
    if (!myDisplay) {
        cout << "failed to create Main Display!" << endl;
    }

    myOptionsFont = al_load_ttf_font("C:/Users/Bryton/Desktop/projectPsiResources/testFont.ttf", 50, 0);
    if (!myOptionsFont) {
        cout << "Could not load \"testFont.ttf\"" << endl;
        cout << "Make sure the correct font is in the executable location!" << endl;
        myOptionsFont = al_create_builtin_font();
    }

    myTitleFont = al_load_ttf_font("C:/Users/Bryton/Desktop/projectPsiResources/testFont.ttf", 108, 0);
    if (!myTitleFont) {
        cout << "Could not load \"testFont.ttf\"" << endl;
        cout << "Make sure the correct font is in the executable location!" << endl;
        myTitleFont = al_create_builtin_font();
    }

    myEventQueue = al_create_event_queue();
    al_register_event_source(myEventQueue, al_get_display_event_source(myDisplay));
    al_register_event_source(myEventQueue, al_get_keyboard_event_source());
}

void mainMenu::setupMenu()
{
    al_clear_to_color(myBackgroundColour);
    al_draw_ustr(myTitleFont,
        myTextColour,
        myScreenWidth*0.5,
        myScreenHeight*0.005,
        ALLEGRO_ALIGN_CENTRE,
        titleString
    );
    al_draw_ustr(myOptionsFont,
        myTextColour,
        myScreenWidth*0.5,
        myScreenHeight*0.25,
        ALLEGRO_ALIGN_CENTRE,
        newSimulationString
    );
    al_draw_ustr(myOptionsFont,
        myTextColour,
        myScreenWidth*0.5,
        myScreenHeight*0.40,
        ALLEGRO_ALIGN_CENTRE,
        loadSimulationString
    );
    al_draw_ustr(myOptionsFont,
        myTextColour,
        myScreenWidth*0.5,
        myScreenHeight*0.55,
        ALLEGRO_ALIGN_CENTRE,
        optionsString
    );
    al_draw_ustr(myOptionsFont,
        myTextColour,
        myScreenWidth*0.5,
        myScreenHeight*0.70,
        ALLEGRO_ALIGN_CENTRE,
        creditsString
    );
    al_draw_ustr(myOptionsFont,
        myTextColour,
        myScreenWidth*0.5,
        myScreenHeight*0.85,
        ALLEGRO_ALIGN_CENTRE,
        quitString
    );
    drawTriangles(float(myScreenWidth)*0.35, float(myScreenHeight)*0.285, 1, myTextColour);
    drawTriangles(float(myScreenWidth)*0.65, float(myScreenHeight)*0.285, -1, myTextColour);
    al_flip_display();
}

int mainMenu::getMaxMenuItems()
{
    return maxMenuItems;
}

int mainMenu::adjustMenuIndexAgainstMaxIndex(int currentMenuIndex) {
    if (currentMenuIndex < 0) {
        return (currentMenuIndex + maxMenuItems);
    }
    else if (currentMenuIndex > maxMenuItems - 1) {
        return (currentMenuIndex - maxMenuItems);
    }
    else {
        return currentMenuIndex;
    }
}

void mainMenu::drawTriangles(float topLeftX, float topLeftY, int direction, ALLEGRO_COLOR colour) {
    if (direction > 0) {
        al_draw_filled_triangle(topLeftX, topLeftY,
            topLeftX + myScreenWidth*0.02, topLeftY + myScreenHeight*0.02,
            topLeftX, topLeftY + myScreenHeight* 0.04,
            colour);
    }
    else {
        al_draw_filled_triangle(topLeftX, topLeftY,
            topLeftX - myScreenWidth*0.02, topLeftY + myScreenHeight*0.02,
            topLeftX, topLeftY + myScreenHeight* 0.04,
            colour);
    }
}

bool mainMenu::processMenu(int menuIndex) {
    switch (menuIndex) {
    case 0:
        cout << "New Simulation" << endl;
        break;
    case 1:
        cout << "Load Simulation" << endl;
        break;
    case 2:
        cout << "Options" << endl;
        break;
    case 3:
        cout << "Credits" << endl;
        break;
    case 4:
        cout << "Exit" << endl;
        return true;
        break;
    default:
        cout << "This menu doesn't exist, did you forget to add it to the process menu function?" << endl;
    }
    return false;
}

void mainMenu::drawMenuWithSelection(int previousSelection, int newSelection) {
    al_flip_display();
    previousSelection = adjustMenuIndexAgainstMaxIndex(previousSelection);
    newSelection = adjustMenuIndexAgainstMaxIndex(newSelection);
    drawTriangles(trianglePositions[previousSelection][0], trianglePositions[previousSelection][1], 1, myBackgroundColour);
    drawTriangles(trianglePositions[previousSelection][2], trianglePositions[previousSelection][3], -1, myBackgroundColour);
    drawTriangles(trianglePositions[newSelection][0], trianglePositions[newSelection][1], 1, myTextColour);
    drawTriangles(trianglePositions[newSelection][2], trianglePositions[newSelection][3], -1, myTextColour);
    al_flip_display();
}

void mainMenu::moveMenuSelectionDown(int currentMenuIndex) {
    drawMenuWithSelection(currentMenuIndex, adjustMenuIndexAgainstMaxIndex(currentMenuIndex + 1));
}

void mainMenu::moveMenuSelectionUp(int currentMenuIndex) {
    drawMenuWithSelection(currentMenuIndex, adjustMenuIndexAgainstMaxIndex(currentMenuIndex - 1));
}

ALLEGRO_EVENT mainMenu::waitForEvent() {
    ALLEGRO_EVENT event;
    al_wait_for_event(myEventQueue, &event);
    return event;
}

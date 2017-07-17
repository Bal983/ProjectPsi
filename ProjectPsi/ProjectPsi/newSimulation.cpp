//C++ Includes
#include <iostream>
#include <stdio.h>

//Our Includes
#include "newSimulation.h"

//Allegro Includes
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

using namespace std;


newSimulation::newSimulation(int screenWidth, int screenHeight)
{
    myDisplay = NULL;
    myTextColour = al_map_rgb_f(0.8706, 0.7216, 0.5294); //burlywood colour
    myBackgroundColour = al_map_rgb_f(0, 0, 0); //black colour
    myOptionsFont = NULL;
    myTitleFont = NULL;
    myEventQueue;
    titleString = al_ustr_new("Project Psi");
    goBackString = al_ustr_new("Back to Main Menu");

    //When adding new menu options, add them to this array and modify the maxMenuItems value in the .h file
    allTitleScreenOptions[0] = goBackString;

    myScreenWidth = screenWidth;
    myScreenHeight = screenHeight;

    //Figure out an easier way to code this so its not so hardcoded
    trianglePositions[0][0] = float(screenWidth)*0.33;
    trianglePositions[0][1] = float(screenHeight)*0.85;
    trianglePositions[0][2] = float(screenWidth)*0.67;
    initAddons(screenWidth, screenHeight);
    setupMenu();
}

newSimulation::~newSimulation()
{
}

void newSimulation::drawTriangles(float, float, int, ALLEGRO_COLOR)
{
}

void newSimulation::drawMenuWithSelection(int, int)
{
}

void newSimulation::setupMenu()
{
}

void newSimulation::initAddons(int, int)
{
}

int newSimulation::getMaxMenuItems()
{
    return 0;
}

int newSimulation::adjustMenuIndexAgainstMaxIndex(int)
{
    return 0;
}

tuple<bool, int> newSimulation::processMenu(int)
{
    return make_tuple(false, 0);
}

void newSimulation::moveMenuSelectionUp(int)
{
}

void newSimulation::moveMenuSelectionDown(int)
{
}

ALLEGRO_EVENT newSimulation::waitForEvent()
{
    return ALLEGRO_EVENT();
}

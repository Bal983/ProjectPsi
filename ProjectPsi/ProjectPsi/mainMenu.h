#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include "baseMenu.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

class mainMenu: public baseMenu
{
    static const int maxMenuItems = 5;

private:
    ALLEGRO_DISPLAY *myDisplay;
    ALLEGRO_EVENT_QUEUE *myEventQueue;
    ALLEGRO_COLOR myTextColour;
    ALLEGRO_COLOR myBackgroundColour;
    ALLEGRO_FONT *myOptionsFont;
    ALLEGRO_FONT *myTitleFont;
    ALLEGRO_USTR *titleString;
    ALLEGRO_USTR *newSimulationString;
    ALLEGRO_USTR *loadSimulationString;
    ALLEGRO_USTR *optionsString;
    ALLEGRO_USTR *creditsString;
    ALLEGRO_USTR *quitString;
    ALLEGRO_USTR *allTitleScreenOptions[maxMenuItems];
    int myScreenWidth;
    int myScreenHeight;
    float trianglePositions[maxMenuItems][4];
    void drawTriangles(float, float, int, ALLEGRO_COLOR);
    void drawMenuWithSelection(int, int);
    void setupMenu();
    void initAddons(int, int);
public:
    mainMenu(int, int);
    ~mainMenu();
    int getMaxMenuItems();
    int adjustMenuIndexAgainstMaxIndex(int);
    bool processMenu(int);
    void moveMenuSelectionUp(int);
    void moveMenuSelectionDown(int);
    ALLEGRO_EVENT waitForEvent();
};
#endif

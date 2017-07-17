#pragma once
#ifndef NEWSIMULATION_H
#define NEWSIMULATION_H

#include "baseMenu.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <tuple>

class newSimulation : public baseMenu
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
    ALLEGRO_USTR *goBackString;
    ALLEGRO_USTR *allTitleScreenOptions[maxMenuItems];
    int myScreenWidth;
    int myScreenHeight;
    float trianglePositions[][3];
    void drawTriangles(float, float, int, ALLEGRO_COLOR);
    void drawMenuWithSelection(int, int);
    void setupMenu();
    void initAddons(int, int);
public:
    newSimulation(int, int);
    ~newSimulation();
    int getMaxMenuItems();
    int adjustMenuIndexAgainstMaxIndex(int);
    std::tuple<bool, int> processMenu(int);
    void moveMenuSelectionUp(int);
    void moveMenuSelectionDown(int);
    ALLEGRO_EVENT waitForEvent();
};
#endif
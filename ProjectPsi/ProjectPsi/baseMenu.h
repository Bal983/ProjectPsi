#pragma once
#ifndef BASEMENU_H
#define BASEMENU_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
class baseMenu
{
private:
    virtual void drawTriangles(float, float, int, ALLEGRO_COLOR) = 0;
    virtual void drawMenuWithSelection(int, int) = 0;
    virtual void initAddons(int, int) = 0;
    virtual void setupMenu() = 0;
public:
    virtual int getMaxMenuItems() = 0;
    virtual void moveMenuSelectionUp(int) = 0;
    virtual void moveMenuSelectionDown(int) = 0;
    virtual int adjustMenuIndexAgainstMaxIndex(int) = 0;
    virtual bool processMenu(int) = 0;
    virtual ALLEGRO_EVENT waitForEvent() = 0;

};
#endif



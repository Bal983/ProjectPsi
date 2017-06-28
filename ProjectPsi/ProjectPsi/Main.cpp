//C++ Includes
#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>

//Allegro Includes
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

//Our Includes
#include "mainMenu.h"

using namespace std;

//Additional Variables used frequently
bool quit = false;
int screenWidth = 1280;
int screenHeight = 720;

int main(int argc, char **argv) {
    mainMenu *theMenu = new mainMenu(screenWidth, screenHeight);

    int currentMenuIndex = 0;
    while (!quit) {
        currentMenuIndex = (theMenu)->adjustMenuIndexAgainstMaxIndex(currentMenuIndex);

        ALLEGRO_EVENT event = (theMenu)->waitForEvent();
        switch (event.type) {
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            quit = true;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_ESCAPE:
                cout << "Escape key pressed" << endl;
                quit = true;
                break;
            case ALLEGRO_KEY_ENTER:
                cout << "Enter key pressed on menu: " << (abs(currentMenuIndex) % (theMenu)->getMaxMenuItems()) << endl;
                quit = (theMenu)->processMenu(currentMenuIndex);
                break;
            case ALLEGRO_KEY_DOWN:
                (theMenu)->moveMenuSelectionDown(currentMenuIndex);
                currentMenuIndex++;
                break;
            case ALLEGRO_KEY_S:
                (theMenu)->moveMenuSelectionDown(currentMenuIndex);
                currentMenuIndex++;
                break;
            case ALLEGRO_KEY_UP:
                (theMenu)->moveMenuSelectionUp(currentMenuIndex);
                currentMenuIndex--;
                break;
            case ALLEGRO_KEY_W:
                (theMenu)->moveMenuSelectionUp(currentMenuIndex);
                currentMenuIndex--;
                break;
            }
        }
    }

    return 0;
}

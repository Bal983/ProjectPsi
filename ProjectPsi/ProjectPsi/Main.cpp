//C++ includes
#include <stdio.h>
#include <string>
#include <iostream>
#include <cmath>

//Allegro includes
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

using namespace std;

//Variables
ALLEGRO_DISPLAY *settingsDisplay = NULL;
ALLEGRO_DISPLAY *mainDisplay = NULL;
ALLEGRO_EVENT_QUEUE *mainEventQueue = NULL;

//Title Screen Variables
ALLEGRO_USTR *titleString = al_ustr_new("Project Psi");
ALLEGRO_USTR *newSimulationString = al_ustr_new("New Simulation");
ALLEGRO_USTR *loadSimulationString = al_ustr_new("Load Simulation");
ALLEGRO_USTR *optionsString = al_ustr_new("Options");
ALLEGRO_USTR *creditsString = al_ustr_new("Credits");
ALLEGRO_USTR *quitString = al_ustr_new("Quit");
const int maxMenuItems = 5;
ALLEGRO_USTR *allTitleScreenOptions[maxMenuItems] = {
    newSimulationString,
    loadSimulationString,
    optionsString,
    creditsString,
    quitString
}; //add new menu options to this array, make sure to increment maxMenuItems

//Colours and Fonts
ALLEGRO_COLOR titleScreenOptionsColour = al_map_rgb_f(0.8706, 0.7216, 0.5294); //burlywood colour
ALLEGRO_COLOR titleScreenBackgroundColour = al_map_rgb_f(0, 0, 0); //black colour
ALLEGRO_FONT *titleScreenOptionsFont = NULL;
ALLEGRO_FONT *titleScreenTitleFont = NULL;

//Additional Variables used frequently
bool quit = false;
int screenWidth;
int screenHeight;

//Function prototypes so I can keep being a java programmer
void setupTitleScreen();
int initAddons();
void drawMenuWithSelection(int, int, float[maxMenuItems][4]);
void drawTriangle(float, float, int, ALLEGRO_COLOR);
void moveMenuDown(int, float[maxMenuItems][4]);
void moveMenuUp(int, float[maxMenuItems][4]);

int main(int argc, char **argv) {

    if (initAddons() == -1) {
        return -1;
    }

    setupTitleScreen();
    //These are in format leftTriangleX1, leftTriangleY1, rightTriangleX1, rightTriangleY1
    float trianglePositions[maxMenuItems][4] = {
        { float(screenWidth)*0.35, float(screenHeight)*0.285, float(screenWidth)*0.65, float(screenHeight)*0.285 },
        { float(screenWidth)*0.345, float(screenHeight)*0.435, float(screenWidth)*0.665, float(screenHeight)*0.435 },
        { float(screenWidth)*0.4, float(screenHeight)*0.585, float(screenWidth)*0.6, float(screenHeight)*0.585 },
        { float(screenWidth)*0.41, float(screenHeight)*0.735, float(screenWidth)*0.59, float(screenHeight)*0.735 },
        { float(screenWidth)*0.43, float(screenHeight)*0.885, float(screenWidth)*0.57, float(screenHeight)*0.885 },
    };

    int currentMenuIndex = 0;
    while (!quit) {
        ALLEGRO_EVENT event;
        al_wait_for_event(mainEventQueue, &event);
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
                cout << "Enter key pressed on menu: " << (currentMenuIndex % maxMenuItems) << endl;
                break;
            case ALLEGRO_KEY_DOWN:
                moveMenuDown(currentMenuIndex, trianglePositions);
                currentMenuIndex++;
                break;
            case ALLEGRO_KEY_S:
                moveMenuDown(currentMenuIndex, trianglePositions);
                currentMenuIndex++;
                break;
            case ALLEGRO_KEY_UP:
                moveMenuUp(currentMenuIndex, trianglePositions);
                currentMenuIndex--;
                break;
            case ALLEGRO_KEY_W:
                moveMenuUp(currentMenuIndex, trianglePositions);
                currentMenuIndex--;
                break;
            }
        }
    }

    return 0;
}
void moveMenuDown(int currentMenuIndex, float trianglePositions[maxMenuItems][4]) {
    cout << "Down key pressed" << endl;
    drawMenuWithSelection(currentMenuIndex, currentMenuIndex + 1, trianglePositions);
}

void moveMenuUp(int currentMenuIndex, float trianglePositions[maxMenuItems][4]) {
    cout << "Up key pressed" << endl;
    drawMenuWithSelection(currentMenuIndex, currentMenuIndex - 1, trianglePositions);
}

void drawMenuWithSelection(int previousSelection, int newSelection, float trianglePositions[maxMenuItems][4]) {
    al_flip_display();
    previousSelection = abs(previousSelection % maxMenuItems);
    newSelection = abs(newSelection % maxMenuItems);
    drawTriangle(trianglePositions[previousSelection][0], trianglePositions[previousSelection][1], 1, titleScreenBackgroundColour);
    drawTriangle(trianglePositions[previousSelection][2], trianglePositions[previousSelection][3], -1, titleScreenBackgroundColour);
    drawTriangle(trianglePositions[newSelection][0], trianglePositions[newSelection][1], 1, titleScreenOptionsColour);
    drawTriangle(trianglePositions[newSelection][2], trianglePositions[newSelection][3], -1, titleScreenOptionsColour);
    al_flip_display();
}

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

    titleScreenOptionsFont = al_load_ttf_font("C:/Users/Bryton/Desktop/projectPsiResources/testFont.ttf", 50, 0);
    if (!titleScreenOptionsFont) {
        cout << "Could not load \"testFont.ttf\"" << endl;
        cout << "Make sure the correct font is in the executable location!" << endl;
        titleScreenOptionsFont = al_create_builtin_font();
    }

    titleScreenTitleFont = al_load_ttf_font("C:/Users/Bryton/Desktop/projectPsiResources/testFont.ttf", 108, 0);
    if (!titleScreenTitleFont) {
        cout << "Could not load \"testFont.ttf\"" << endl;
        cout << "Make sure the correct font is in the executable location!" << endl;
        titleScreenTitleFont = al_create_builtin_font();
    }

    mainEventQueue = al_create_event_queue();
    al_register_event_source(mainEventQueue, al_get_display_event_source(settingsDisplay));
    al_register_event_source(mainEventQueue, al_get_keyboard_event_source());
}

void setupTitleScreen() {
    screenHeight = al_get_display_height(settingsDisplay);
    screenWidth = al_get_display_width(settingsDisplay);
    al_set_window_title(mainDisplay, "Project Psi Title Screen");
    al_clear_to_color(titleScreenBackgroundColour);
    al_draw_ustr(titleScreenTitleFont,
        titleScreenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.005,
        ALLEGRO_ALIGN_CENTRE,
        titleString
    );
    al_draw_ustr(titleScreenOptionsFont,
        titleScreenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.25,
        ALLEGRO_ALIGN_CENTRE,
        newSimulationString
    );
    al_draw_ustr(titleScreenOptionsFont,
        titleScreenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.40,
        ALLEGRO_ALIGN_CENTRE,
        loadSimulationString
    );
    al_draw_ustr(titleScreenOptionsFont,
        titleScreenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.55,
        ALLEGRO_ALIGN_CENTRE,
        optionsString
    );
    al_draw_ustr(titleScreenOptionsFont,
        titleScreenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.70,
        ALLEGRO_ALIGN_CENTRE,
        creditsString
    );
    al_draw_ustr(titleScreenOptionsFont,
        titleScreenOptionsColour,
        screenWidth*0.5,
        screenHeight*0.85,
        ALLEGRO_ALIGN_CENTRE,
        quitString
    );
    drawTriangle(float(screenWidth)*0.35, float(screenHeight)*0.285, 1, titleScreenOptionsColour);
    drawTriangle(float(screenWidth)*0.65, float(screenHeight)*0.285, -1, titleScreenOptionsColour);
    al_flip_display();
}

void drawTriangle(float topLeftX, float topLeftY, int direction, ALLEGRO_COLOR colour) {
    if (direction > 0) {
        cout << "drawing left triangle" << endl;
        al_draw_filled_triangle(topLeftX, topLeftY,
            topLeftX + screenWidth*0.02, topLeftY + screenHeight*0.02,
            topLeftX, topLeftY + screenHeight* 0.04,
            colour);
    }
    else{
        cout << "drawing right triangle" << endl;
        al_draw_filled_triangle(topLeftX, topLeftY,
            topLeftX - screenWidth*0.02, topLeftY + screenHeight*0.02,
            topLeftX, topLeftY + screenHeight* 0.04,
            colour);
    }

}

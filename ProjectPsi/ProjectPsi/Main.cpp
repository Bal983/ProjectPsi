//C++ includes
#include <stdio.h>
#include <string>
#include <iostream>

//Allegro includes
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using namespace std;

//Variables
ALLEGRO_DISPLAY *settingsDisplay = NULL;
ALLEGRO_DISPLAY *mainDisplay = NULL;
ALLEGRO_EVENT_QUEUE *mainEventQueue = NULL;

//Title Screen Variables
ALLEGRO_USTR *titleString = al_ustr_new("Project Psi");
ALLEGRO_USTR *newGameString = al_ustr_new("New Simulation");
ALLEGRO_USTR *loadGameString = al_ustr_new("Load Simulation");
ALLEGRO_USTR *optionsString = al_ustr_new("Options");
ALLEGRO_USTR *creditsString = al_ustr_new("Credits");
ALLEGRO_USTR *quitString = al_ustr_new("Quit");
ALLEGRO_COLOR titleScreenTextColour = al_map_rgb_f(0.8706, 0.7216, 0.5294); //burlywood colour
ALLEGRO_COLOR titleScreenBackgroundColour = al_map_rgb_f(0, 0, 0); //black colour
ALLEGRO_FONT *titleScreenOptionsFont = NULL;
ALLEGRO_FONT *titleScreenTitleFont = NULL;

bool quit = false;

//Function prototypes so I can keep being a java programmer
void setupTitleScreen();
void debugMessagePrint(string);

int main(int argc, char **argv) {
    if (!al_init() && !al_init_font_addon() && !al_install_keyboard()) {
        debugMessagePrint("failed to initialize allegro!");
        return -1;
    }
    if (!al_init_font_addon()) {
        debugMessagePrint("failed to initialize the font addon!");
        return -1;
    }
    if (!al_init_ttf_addon()) {
        debugMessagePrint("failed to initialize the ttf font addon!");
        return -1;
    }
    if (!al_install_keyboard()) {
        debugMessagePrint("failed to initialize the keyboard!");
        return -1;
    }
    settingsDisplay = al_create_display(1280, 720);
    if (!settingsDisplay) {
        debugMessagePrint("failed to create display!");
        return -1;
    }

    titleScreenOptionsFont = al_load_ttf_font("C:/Users/Bryton/Desktop/projectPsiResources/testFont.ttf", 50, 0);
    if (!titleScreenOptionsFont) {
        debugMessagePrint("Could not load the title screen options font");
        debugMessagePrint("Make sure the correct font is in the executable location!");
        titleScreenOptionsFont = al_create_builtin_font();
    }

    titleScreenTitleFont = al_load_ttf_font("C:/Users/Bryton/Desktop/projectPsiResources/testFont.ttf", 108, 0);
    if (!titleScreenTitleFont) {
        debugMessagePrint("Could not load \"testFont.ttf\"");
        debugMessagePrint("Make sure the correct font is in the executable location!");
        titleScreenTitleFont = al_create_builtin_font();
    }

    mainEventQueue = al_create_event_queue();
    al_register_event_source(mainEventQueue, al_get_display_event_source(settingsDisplay));
    al_register_event_source(mainEventQueue, al_get_keyboard_event_source());

    setupTitleScreen();
    al_flip_display();

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
                debugMessagePrint("Escape key pressed");
                quit = true;
                break;
            case ALLEGRO_KEY_DOWN:
                debugMessagePrint("Down arrow key pressed");
                break;
            case ALLEGRO_KEY_UP:
                debugMessagePrint("Up arrow key pressed");
            }
        }
    }

    return 0;
}

void setupTitleScreen() {
    al_set_window_title(mainDisplay, "Project Psi Title Screen");
    al_clear_to_color(titleScreenBackgroundColour);
    al_draw_ustr(titleScreenTitleFont,
        titleScreenTextColour,
        al_get_display_width(settingsDisplay)*0.5,
        al_get_display_height(settingsDisplay)*0.005,
        ALLEGRO_ALIGN_CENTRE,
        titleString
    );
    al_draw_ustr(titleScreenOptionsFont,
        titleScreenTextColour,
        al_get_display_width(settingsDisplay)*0.5,
        al_get_display_height(settingsDisplay)*0.25,
        ALLEGRO_ALIGN_CENTRE,
        newGameString
    );
    al_draw_ustr(titleScreenOptionsFont,
        titleScreenTextColour,
        al_get_display_width(settingsDisplay)*0.5,
        al_get_display_height(settingsDisplay)*0.40,
        ALLEGRO_ALIGN_CENTRE,
        loadGameString
    );
    al_draw_ustr(titleScreenOptionsFont,
        titleScreenTextColour,
        al_get_display_width(settingsDisplay)*0.5,
        al_get_display_height(settingsDisplay)*0.55,
        ALLEGRO_ALIGN_CENTRE,
        optionsString
    );
    al_draw_ustr(titleScreenOptionsFont,
        titleScreenTextColour,
        al_get_display_width(settingsDisplay)*0.5,
        al_get_display_height(settingsDisplay)*0.70,
        ALLEGRO_ALIGN_CENTRE,
        creditsString
    );
    al_draw_ustr(titleScreenOptionsFont,
        titleScreenTextColour,
        al_get_display_width(settingsDisplay)*0.5,
        al_get_display_height(settingsDisplay)*0.85,
        ALLEGRO_ALIGN_CENTRE,
        quitString
    );
}

void debugMessagePrint(string messageToPrint) {
    cout << messageToPrint << endl;
}
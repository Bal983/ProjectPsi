//
// Made by Bryton Leason for project Psi
//

#pragma once
#ifndef MENUSYSTEM_HEADER
#define MENUSYSTEM_HEADER

//C++ includes
#include <tuple>

//Allegro includes
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

//Other includes
#include "AllegroSettings.h"

using namespace std;

class GraphicsSystem {
private:
	//Generic functions
	void drawTriangle(float, float, int, ALLEGRO_COLOR);
	tuple<bool, string> processMenu(string, int);
	void loadNewMenu(string);
	int normalizeScreenIndex(int, int);

	//Variables used to initialize the simulation
	string initializationValues[15];

	//Title Screen
	ALLEGRO_USTR *mainMenuScreenTitle = al_ustr_new("Project Psi");
	ALLEGRO_USTR *newSimulationString = al_ustr_new("New Simulation");
	ALLEGRO_USTR *loadSimulationString = al_ustr_new("Load Simulation");
	ALLEGRO_USTR *controlsString = al_ustr_new("Controls");
	ALLEGRO_USTR *creditsString = al_ustr_new("Credits");
	ALLEGRO_USTR *quitString = al_ustr_new("Quit");
	static const int titleScreenMenuItems = 5; //Don't count the title in here
	ALLEGRO_USTR *allTitleScreenOptions[titleScreenMenuItems] = {
		newSimulationString,
		loadSimulationString,
		controlsString,
		creditsString,
		quitString
	}; //add new menu options to this array, make sure to increment maxMenuItems, so far this is just for us to keep track of them
	int normalizeTitleScreenIndex(int);
	void moveTitleScreenDown(int);
	void moveTitleScreenUp(int);
	void drawTitleScreenWithSelection(int, int);

	//New Simulation Screen
	ALLEGRO_USTR *newSimulationScreenTitle = al_ustr_new("New Simulation");
	ALLEGRO_USTR *newSimulationLeftp1prompt = al_ustr_new("Placeholder:");
	ALLEGRO_USTR *newSimulationLeftp2prompt = al_ustr_new("Placeholder:");
	ALLEGRO_USTR *newSimulationLeftp3prompt = al_ustr_new("Placeholder:");
	ALLEGRO_USTR *newSimulationLeftp4prompt = al_ustr_new("Placeholder:");
	ALLEGRO_USTR *newSimulationLeftp5prompt = al_ustr_new("Placeholder:");
	ALLEGRO_USTR *newSimulationLeftp6prompt = al_ustr_new("Placeholder:");
	ALLEGRO_USTR *newSimulationLeftp7prompt = al_ustr_new("Placeholder:");
	ALLEGRO_USTR *newSimulationLeftp1value = al_ustr_new(initializationValues[0].c_str());
	ALLEGRO_USTR *newSimulationLeftp2value = al_ustr_new(initializationValues[1].c_str());
	ALLEGRO_USTR *newSimulationLeftp3value = al_ustr_new(initializationValues[2].c_str());
	ALLEGRO_USTR *newSimulationLeftp4value = al_ustr_new(initializationValues[3].c_str());
	ALLEGRO_USTR *newSimulationLeftp5value = al_ustr_new(initializationValues[4].c_str());
	ALLEGRO_USTR *newSimulationLeftp6value = al_ustr_new(initializationValues[5].c_str());
	ALLEGRO_USTR *newSimulationLeftp7value = al_ustr_new(initializationValues[6].c_str());
	ALLEGRO_USTR *newSimulationRightp1prompt = al_ustr_new("Placeholder:");
	ALLEGRO_USTR *newSimulationRightp2prompt = al_ustr_new("Placeholder:");
	ALLEGRO_USTR *newSimulationRightp3prompt = al_ustr_new("Placeholder:");
	ALLEGRO_USTR *newSimulationRightp4prompt = al_ustr_new("Placeholder:");
	ALLEGRO_USTR *newSimulationRightp5prompt = al_ustr_new("Placeholder:");
	ALLEGRO_USTR *newSimulationRightp6prompt = al_ustr_new("Placeholder:");
	ALLEGRO_USTR *newSimulationRightp7prompt = al_ustr_new("Placeholder:");
	ALLEGRO_USTR *newSimulationRightp1value = al_ustr_new(initializationValues[7].c_str());
	ALLEGRO_USTR *newSimulationRightp2value = al_ustr_new(initializationValues[8].c_str());
	ALLEGRO_USTR *newSimulationRightp3value = al_ustr_new(initializationValues[9].c_str());
	ALLEGRO_USTR *newSimulationRightp4value = al_ustr_new(initializationValues[10].c_str());
	ALLEGRO_USTR *newSimulationRightp5value = al_ustr_new(initializationValues[11].c_str());
	ALLEGRO_USTR *newSimulationRightp6value = al_ustr_new(initializationValues[12].c_str());
	ALLEGRO_USTR *newSimulationRightp7value = al_ustr_new(initializationValues[13].c_str());
	ALLEGRO_USTR *newSimulationGoBackString = al_ustr_new("Go Back");
	ALLEGRO_USTR *newSimulationStartString = al_ustr_new("Start");
	ALLEGRO_USTR *newSimulationExportConfiguartionString = al_ustr_new("Export");
	static const int newSimulationScreenMenuItems = 17; //Don't count the title in here
	tuple<ALLEGRO_USTR, ALLEGRO_USTR, string> allNewSimulationScreenOptions[newSimulationScreenMenuItems] = {
		make_tuple(*newSimulationLeftp1prompt, *newSimulationLeftp1value, initializationValues[0]),
		make_tuple(*newSimulationLeftp2prompt, *newSimulationLeftp2value, initializationValues[1]),
		make_tuple(*newSimulationLeftp3prompt, *newSimulationLeftp3value, initializationValues[2]),
		make_tuple(*newSimulationLeftp4prompt, *newSimulationLeftp4value, initializationValues[3]),
		make_tuple(*newSimulationLeftp5prompt, *newSimulationLeftp5value, initializationValues[4]),
		make_tuple(*newSimulationLeftp6prompt, *newSimulationLeftp6value, initializationValues[5]),
		make_tuple(*newSimulationLeftp7prompt, *newSimulationLeftp7value, initializationValues[6]),
		make_tuple(*newSimulationRightp1prompt, *newSimulationRightp1value, initializationValues[7]),
		make_tuple(*newSimulationRightp2prompt, *newSimulationRightp2value, initializationValues[8]),
		make_tuple(*newSimulationRightp3prompt, *newSimulationRightp3value, initializationValues[9]),
		make_tuple(*newSimulationRightp4prompt, *newSimulationRightp4value, initializationValues[10]),
		make_tuple(*newSimulationRightp5prompt, *newSimulationRightp5value, initializationValues[11]),
		make_tuple(*newSimulationRightp6prompt, *newSimulationRightp6value, initializationValues[12]),
		make_tuple(*newSimulationRightp7prompt, *newSimulationRightp7value, initializationValues[13]),
		make_tuple(*newSimulationGoBackString, *newSimulationGoBackString, initializationValues[14]),
		make_tuple(*newSimulationStartString, *newSimulationStartString, initializationValues[14]),
		make_tuple(*newSimulationExportConfiguartionString, *newSimulationExportConfiguartionString, initializationValues[14])
	}; //add new menu options to this array, make sure to increment maxMenuItems, so far this is just for us to keep track of them
	tuple<float, float> allNewSimulationScreenPositions[newSimulationScreenMenuItems] = {
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
		make_tuple(0.475, 1),
		make_tuple(0, 0),
		make_tuple(0, 0)
	};//this is the format of width position/height position
	//these are the positions corresponding to the values of the above tuples, only the values not the prompts.
	//We need to find a better way to do this
	//Note: the last one maps to the middle and the far right for the purpose of drawing the "black bar"
	void setupNewSimulationScreen();
	int normalizeNewSimulationScreenIndex(int);
	void moveNewSimulationScreenDown(int);
	void moveNewSimulationScreenUp(int);
	void drawNewSimulationScreenWithSelection(int, int);
	void updateNewSimulationScreenString(int, char);
	void removeCharFromNewSimluationScreenString(int);
	void exportSimluationConfiguration();

	//Load Simulation Screen
	ALLEGRO_USTR *loadSimulationScreenTitle = al_ustr_new("Load Simulation");
	ALLEGRO_USTR *loadSimulationStringOne = al_ustr_new("Loading Simulation Coming Soon!");
	ALLEGRO_USTR *loadSimulationGoBackString = al_ustr_new("Go Back");
	static const int loadSimulationScreenMenuItems = 2; //Don't count the title in here
	ALLEGRO_USTR *allLoadSimulationScreenOptions[loadSimulationScreenMenuItems] = {
		loadSimulationGoBackString,
		loadSimulationStringOne
	}; //add new menu options to this array, make sure to increment maxMenuItems, so far this is just for us to keep track of them
	void setupLoadSimulationScreen();
	int normalizeLoadSimulationScreenIndex(int);

	//Controls Screen
	ALLEGRO_USTR *controlsScreenTitle = al_ustr_new("Options");
	ALLEGRO_USTR *controlsGoBackString = al_ustr_new("Go Back");
	ALLEGRO_USTR *controlsStringOne = al_ustr_new("Press up arrow or w to move up in the menu");
	ALLEGRO_USTR *controlsStringTwo = al_ustr_new("Press down arrow or s to move down in the menu");
	ALLEGRO_USTR *controlsStringThree = al_ustr_new("Press escape at any time to close the launcher");
	ALLEGRO_USTR *controlsStringFour = al_ustr_new("Press enter at any to confirm your selection");
	ALLEGRO_USTR *controlsStringFive = al_ustr_new("Press backspace to move back in the menu system");
	static const int optionsScreenMenuItems = 6; //Don't count the title in here
	ALLEGRO_USTR *allOptionsScreenOptions[optionsScreenMenuItems] = {
		controlsGoBackString,
		controlsStringOne,
		controlsStringTwo,
		controlsStringThree,
		controlsStringFour,
		controlsStringFive
	}; //add new menu options to this array, make sure to increment maxMenuItems, so far this is just for us to keep track of them
	void setupControlsScreen();

	//Credits Screen
	ALLEGRO_USTR *creditsScreenTitle = al_ustr_new("Credits");
	ALLEGRO_USTR *creditsGoBackString = al_ustr_new("Go Back");
	ALLEGRO_USTR *creditsStringOne = al_ustr_new("Project Psi was created by Bryton Leason and Sam Horovatin");
	ALLEGRO_USTR *creditsStringTwo = al_ustr_new("This project is for the purpose of learning about AI and making something we can be proud of");
	ALLEGRO_USTR *creditsStringThree = al_ustr_new("We are using allegro and trying to do as much of the code on our own as possible");
	ALLEGRO_USTR *creditsStringFour = al_ustr_new("Thanks for playing with our simulator!");
	static const int creditsScreenMenuItems = 5; //Don't count the title in here
	ALLEGRO_USTR *allCreditsScreenOptions[creditsScreenMenuItems] = {
		creditsGoBackString,
		creditsStringOne,
		creditsStringTwo,
		creditsStringThree,
		creditsStringFour
	}; //add new menu options to this array, make sure to increment maxMenuItems, so far this is just for us to keep track of them
	void setupCreditsScreen();

	//Simulation Screen
	ALLEGRO_USTR *simulationScreenTitle = al_ustr_new("Simulation");
	void setupSimulationScreen();
public:
	//Constructors
	GraphicsSystem();

	//Controller
	int handleControl();
	void handleGameControl();

	//Getters/Setters
	string *getInitializationValues();

	//Init Functions
	void setupTitleScreen();
	int initAddons();
};
#endif
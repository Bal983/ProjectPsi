//
// Made by Bryton Leason for project Psi
//

//C++ includes
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <tuple>
#include <sstream>

//Allegro includes
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

//Other includes
#include "AllegroSettings.h"
#include "GraphicsSystem.h"

using namespace std;

GraphicsSystem::GraphicsSystem() {}

int GraphicsSystem::handleControl()
{
	bool quit = false;
	bool valueInputMode = false;
	int currentMenuIndex = 0;
	string currentMenu = "Title Screen";
	while (!quit) {
		ALLEGRO_EVENT event;
		al_wait_for_event(settingsEventQueue, &event);
		if (!valueInputMode) {
			switch (event.type) {
			case ALLEGRO_EVENT_DISPLAY_CLOSE: //This triggers when you hit the x on the window
				quit = true;
				break;
			case ALLEGRO_EVENT_KEY_CHAR:
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
						valueInputMode = get<0>(response);
						if (!valueInputMode) {
							loadNewMenu(get<1>(response));
							currentMenu = get<1>(response);
							if (currentMenu == "Simulation") {
								return 1;
							}
							currentMenuIndex = 0;
						}
					}
					else if (currentMenu == "Load Simulation") {
						auto response = processMenu("Load Simulation", currentMenuIndex);
						quit = get<0>(response);
						loadNewMenu(get<1>(response));
						currentMenu = get<1>(response);
						currentMenuIndex = 0;
					}
					else if (currentMenu == "Controls") {
						auto response = processMenu("Controls", currentMenuIndex);
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
						moveTitleScreenDown(currentMenuIndex);
					}
					else if (currentMenu == "New Simulation") {
						moveNewSimulationScreenDown(currentMenuIndex);
					}
					else if (currentMenu == "Load Simulation") {

					}
					currentMenuIndex++;
					break;
				case ALLEGRO_KEY_S:
					if (currentMenu == "Title Screen") {
						moveTitleScreenDown(currentMenuIndex);
					}
					else if (currentMenu == "New Simulation") {
						moveNewSimulationScreenDown(currentMenuIndex);
					}
					else if (currentMenu == "Load Simulation") {

					}
					currentMenuIndex++;
					break;
				case ALLEGRO_KEY_UP:
					if (currentMenu == "Title Screen") {
						moveTitleScreenUp(currentMenuIndex);
					}
					else if (currentMenu == "New Simulation") {
						moveNewSimulationScreenUp(currentMenuIndex);
					}
					else if (currentMenu == "Load Simulation") {

					}
					currentMenuIndex--;
					break;
				case ALLEGRO_KEY_W:
					if (currentMenu == "Title Screen") {
						moveTitleScreenUp(currentMenuIndex);
					}
					else if (currentMenu == "New Simulation") {
						moveNewSimulationScreenUp(currentMenuIndex);
					}
					else if (currentMenu == "Load Simulation") {

					}
					currentMenuIndex--;
					break;
				}
			}
		}
		else {
			switch (event.type) {
			case ALLEGRO_EVENT_KEY_CHAR:
				switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_ENTER:
					valueInputMode = false;
					break;
				case ALLEGRO_KEY_ESCAPE:
					quit = true;
					break;
				case ALLEGRO_KEY_BACKSPACE:
					if (currentMenu == "New Simulation") {
						removeCharFromNewSimluationScreenString(currentMenuIndex);
					}
					break;
				default:
					if (currentMenu == "New Simulation") {
						updateNewSimulationScreenString(currentMenuIndex, event.keyboard.unichar);
					}
					break;
				}
			}
		}
	}
}

void GraphicsSystem::handleGameControl()
{
	bool quit = false;
	while (!quit) {
		ALLEGRO_EVENT event;
		al_wait_for_event(mainEventQueue, &event);
		switch (event.type) {
		case ALLEGRO_EVENT_DISPLAY_CLOSE: //This triggers when you hit the x on the window
			quit = true;
			break;
		case ALLEGRO_EVENT_KEY_CHAR:
			switch (event.keyboard.keycode) {
			case ALLEGRO_KEY_ESCAPE:
				quit = true;
				break;
			}
		}
	}
}

void GraphicsSystem::drawTriangle(float topLeftX, float topLeftY, int direction, ALLEGRO_COLOR colour)
{
	if (direction > 0) {
		al_draw_filled_triangle(topLeftX, topLeftY,
			topLeftX + LAUNCHER_SCREENWIDTH*0.02, topLeftY + LAUNCHER_SCREENHEIGHT*0.02,
			topLeftX, topLeftY + LAUNCHER_SCREENHEIGHT* 0.04,
			colour);
	}
	else {
		al_draw_filled_triangle(topLeftX, topLeftY,
			topLeftX - LAUNCHER_SCREENWIDTH*0.02, topLeftY + LAUNCHER_SCREENHEIGHT*0.02,
			topLeftX, topLeftY + LAUNCHER_SCREENHEIGHT* 0.04,
			colour);
	}
}

tuple<bool, string> GraphicsSystem::processMenu(string currentMenu, int currentMenuIndex)
{
	if (currentMenu == "Title Screen") {
		currentMenuIndex = normalizeTitleScreenIndex(currentMenuIndex);
		switch (currentMenuIndex) {
		case(0):
			return make_tuple(false, "New Simulation");
		case(1):
			return make_tuple(false, "Load Simulation");
		case(2):
			return make_tuple(false, "Controls");
		case(3):
			return make_tuple(false, "Credits");
		case(4):
			return make_tuple(true, "Exiting the game, doesn't matter");
		default:
			break;
		}
	}
	else if (currentMenu == "New Simulation") {
		currentMenuIndex = normalizeNewSimulationScreenIndex(currentMenuIndex);
		switch (currentMenuIndex) {
		case(14):
			return make_tuple(false, "Title Screen");
		case(15):
			exportSimluationConfiguration();
			return make_tuple(false, "New Simulation");
		case(16):
			return make_tuple(false, "Simulation");
		default: //note, this makes the code smaller to write but it makes the error cases (that shouldn't arise) hard to handle.
			return make_tuple(true, "New Simulation");
		}
	}
	else if (currentMenu == "Load Simulation") {
		currentMenuIndex = normalizeLoadSimulationScreenIndex(currentMenuIndex);
		switch (currentMenuIndex) {
		case(0):
			return make_tuple(false, "Title Screen");
		}
	}
	else if (currentMenu == "Controls") {
		return make_tuple(false, "Title Screen");
	}
	else if (currentMenu == "Credits") {
		return make_tuple(false, "Title Screen");
	}
	return make_tuple(false, currentMenu);
}

void GraphicsSystem::loadNewMenu(string newMenu)
{
	if (newMenu == "Title Screen") {
		setupTitleScreen();
	}
	else if (newMenu == "New Simulation") {
		setupNewSimulationScreen();
	}
	else if (newMenu == "Load Simulation") {
		setupLoadSimulationScreen();
	}
	else if (newMenu == "Controls") {
		setupControlsScreen();
	}
	else if (newMenu == "Credits") {
		setupCreditsScreen();
	}
	else if (newMenu == "Simulation") {
		setupSimulationScreen();
	}
}

int GraphicsSystem::normalizeScreenIndex(int abnormalIndex, int maxMenuIndex)
{
	if (abnormalIndex < 0) {
		while (abnormalIndex < 0) {
			abnormalIndex += maxMenuIndex;
		}
		return abnormalIndex;
	}
	else if (abnormalIndex > maxMenuIndex - 1) {
		while (abnormalIndex > maxMenuIndex - 1) {
			abnormalIndex -= maxMenuIndex;
		}
		return abnormalIndex;
	}
	else {
		return abnormalIndex;
	}
}

string * GraphicsSystem::getInitializationValues()
{
	return initializationValues;
}

void GraphicsSystem::setupTitleScreen()
{
	al_set_window_title(mainDisplay, "Project Psi Title Screen");
	al_clear_to_color(menuScreenBackgroundColour);
	al_draw_ustr(screenTitleFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.5,
		LAUNCHER_SCREENHEIGHT*0.005,
		ALLEGRO_ALIGN_CENTRE,
		mainMenuScreenTitle
	);
	//Horizontal Bar
	al_draw_rectangle(
		0,
		LAUNCHER_SCREENHEIGHT*0.193,
		LAUNCHER_SCREENWIDTH,
		LAUNCHER_SCREENHEIGHT*0.197,
		screenOptionsColour,
		7
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.5,
		LAUNCHER_SCREENHEIGHT*0.25,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationString
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.5,
		LAUNCHER_SCREENHEIGHT*0.40,
		ALLEGRO_ALIGN_CENTRE,
		loadSimulationString
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.5,
		LAUNCHER_SCREENHEIGHT*0.55,
		ALLEGRO_ALIGN_CENTRE,
		controlsString
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.5,
		LAUNCHER_SCREENHEIGHT*0.70,
		ALLEGRO_ALIGN_CENTRE,
		creditsString
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.5,
		LAUNCHER_SCREENHEIGHT*0.85,
		ALLEGRO_ALIGN_CENTRE,
		quitString
	);
	drawTriangle(float(LAUNCHER_SCREENWIDTH)*0.35, float(LAUNCHER_SCREENHEIGHT)*0.285, 1, screenOptionsColour);
	drawTriangle(float(LAUNCHER_SCREENWIDTH)*0.65, float(LAUNCHER_SCREENHEIGHT)*0.285, -1, screenOptionsColour);
	al_flip_display();
}

int GraphicsSystem::normalizeTitleScreenIndex(int abnormalIndex)
{
	return normalizeScreenIndex(abnormalIndex, titleScreenMenuItems);
}

void GraphicsSystem::moveTitleScreenDown(int currentMenuIndex)
{
	drawTitleScreenWithSelection(currentMenuIndex, currentMenuIndex + 1);
}

void GraphicsSystem::moveTitleScreenUp(int currentMenuIndex)
{
	drawTitleScreenWithSelection(currentMenuIndex, currentMenuIndex - 1);
}

void GraphicsSystem::drawTitleScreenWithSelection(int previousSelection, int newSelection)
{
	//These are in format leftTriangleX1, triangleY, rightTriangleX1
	float titleScreenArrows[][3] = {
		{ float(LAUNCHER_SCREENWIDTH)*0.35, float(LAUNCHER_SCREENHEIGHT)*0.285, float(LAUNCHER_SCREENWIDTH)*0.65 },
		{ float(LAUNCHER_SCREENWIDTH)*0.345, float(LAUNCHER_SCREENHEIGHT)*0.435, float(LAUNCHER_SCREENWIDTH)*0.665 },
		{ float(LAUNCHER_SCREENWIDTH)*0.4, float(LAUNCHER_SCREENHEIGHT)*0.585, float(LAUNCHER_SCREENWIDTH)*0.6 },
		{ float(LAUNCHER_SCREENWIDTH)*0.405, float(LAUNCHER_SCREENHEIGHT)*0.74, float(LAUNCHER_SCREENWIDTH)*0.59 },
		{ float(LAUNCHER_SCREENWIDTH)*0.43, float(LAUNCHER_SCREENHEIGHT)*0.885, float(LAUNCHER_SCREENWIDTH)*0.57 },
	};

	previousSelection = normalizeTitleScreenIndex(previousSelection);
	newSelection = normalizeTitleScreenIndex(newSelection);

	al_flip_display();
	drawTriangle(titleScreenArrows[previousSelection][0], titleScreenArrows[previousSelection][1], 1, menuScreenBackgroundColour);
	drawTriangle(titleScreenArrows[previousSelection][2], titleScreenArrows[previousSelection][1], -1, menuScreenBackgroundColour);
	drawTriangle(titleScreenArrows[newSelection][0], titleScreenArrows[newSelection][1], 1, screenOptionsColour);
	drawTriangle(titleScreenArrows[newSelection][2], titleScreenArrows[newSelection][1], -1, screenOptionsColour);
	al_flip_display();
}

void GraphicsSystem::setupNewSimulationScreen()
{
	al_clear_to_color(menuScreenBackgroundColour);
	al_draw_ustr(screenTitleFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.5,
		LAUNCHER_SCREENHEIGHT*0.005,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationScreenTitle
	);
	//Horizontal Bar
	al_draw_filled_rectangle(
		0,
		LAUNCHER_SCREENHEIGHT*0.193,
		LAUNCHER_SCREENWIDTH,
		LAUNCHER_SCREENHEIGHT*0.197,
		screenOptionsColour
	);
	//Vertical Bar
	al_draw_filled_rectangle(
		LAUNCHER_SCREENWIDTH*0.4995,
		LAUNCHER_SCREENHEIGHT*0.193,
		LAUNCHER_SCREENWIDTH*0.5005,
		LAUNCHER_SCREENHEIGHT*0.903,
		screenOptionsColour
	);
	//Lefthand Side Options
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.1,
		LAUNCHER_SCREENHEIGHT*0.2,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationLeftp1prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.2,
		LAUNCHER_SCREENHEIGHT*0.2,
		ALLEGRO_ALIGN_LEFT,
		newSimulationLeftp1value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.1,
		LAUNCHER_SCREENHEIGHT*0.3,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationLeftp2prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.2,
		LAUNCHER_SCREENHEIGHT*0.3,
		ALLEGRO_ALIGN_LEFT,
		newSimulationLeftp2value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.1,
		LAUNCHER_SCREENHEIGHT*0.4,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationLeftp3prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.2,
		LAUNCHER_SCREENHEIGHT*0.4,
		ALLEGRO_ALIGN_LEFT,
		newSimulationLeftp3value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.1,
		LAUNCHER_SCREENHEIGHT*0.5,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationLeftp4prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.2,
		LAUNCHER_SCREENHEIGHT*0.5,
		ALLEGRO_ALIGN_LEFT,
		newSimulationLeftp4value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.1,
		LAUNCHER_SCREENHEIGHT*0.6,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationLeftp5prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.2,
		LAUNCHER_SCREENHEIGHT*0.6,
		ALLEGRO_ALIGN_LEFT,
		newSimulationLeftp5value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.1,
		LAUNCHER_SCREENHEIGHT*0.7,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationLeftp6prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.2,
		LAUNCHER_SCREENHEIGHT*0.7,
		ALLEGRO_ALIGN_LEFT,
		newSimulationLeftp6value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.1,
		LAUNCHER_SCREENHEIGHT*0.8,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationLeftp7prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.2,
		LAUNCHER_SCREENHEIGHT*0.8,
		ALLEGRO_ALIGN_LEFT,
		newSimulationLeftp7value
	);
	//Righthand Side Options
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.6,
		LAUNCHER_SCREENHEIGHT*0.2,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationRightp1prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.7,
		LAUNCHER_SCREENHEIGHT*0.2,
		ALLEGRO_ALIGN_LEFT,
		newSimulationRightp1value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.6,
		LAUNCHER_SCREENHEIGHT*0.3,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationRightp2prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.7,
		LAUNCHER_SCREENHEIGHT*0.3,
		ALLEGRO_ALIGN_LEFT,
		newSimulationRightp2value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.6,
		LAUNCHER_SCREENHEIGHT*0.4,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationRightp3prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.7,
		LAUNCHER_SCREENHEIGHT*0.4,
		ALLEGRO_ALIGN_LEFT,
		newSimulationRightp3value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.6,
		LAUNCHER_SCREENHEIGHT*0.5,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationRightp4prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.7,
		LAUNCHER_SCREENHEIGHT*0.5,
		ALLEGRO_ALIGN_LEFT,
		newSimulationRightp4value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.6,
		LAUNCHER_SCREENHEIGHT*0.6,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationRightp5prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.7,
		LAUNCHER_SCREENHEIGHT*0.6,
		ALLEGRO_ALIGN_LEFT,
		newSimulationRightp5value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.6,
		LAUNCHER_SCREENHEIGHT*0.7,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationRightp6prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.7,
		LAUNCHER_SCREENHEIGHT*0.7,
		ALLEGRO_ALIGN_LEFT,
		newSimulationRightp6value
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.6,
		LAUNCHER_SCREENHEIGHT*0.8,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationRightp7prompt
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.7,
		LAUNCHER_SCREENHEIGHT*0.8,
		ALLEGRO_ALIGN_LEFT,
		newSimulationRightp7value
	);
	//Horizontal Bar
	al_draw_filled_rectangle(
		0,
		LAUNCHER_SCREENHEIGHT*0.903,
		LAUNCHER_SCREENWIDTH,
		LAUNCHER_SCREENHEIGHT*0.907,
		screenOptionsColour
	);
	//Bottom of the screen options
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.5,
		LAUNCHER_SCREENHEIGHT*0.9,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationGoBackString
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.1,
		LAUNCHER_SCREENHEIGHT*0.9,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationExportConfiguartionString
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.9,
		LAUNCHER_SCREENHEIGHT*0.9,
		ALLEGRO_ALIGN_CENTRE,
		newSimulationStartString
	);
	drawTriangle(float(LAUNCHER_SCREENWIDTH)*0.49, float(LAUNCHER_SCREENHEIGHT)*0.235, -1, screenOptionsColour);
	al_flip_display();
}

int GraphicsSystem::normalizeNewSimulationScreenIndex(int abnormalIndex)
{
	return normalizeScreenIndex(abnormalIndex, newSimulationScreenMenuItems);
}

void GraphicsSystem::moveNewSimulationScreenDown(int currentMenuIndex)
{
	drawNewSimulationScreenWithSelection(currentMenuIndex, currentMenuIndex + 1);
}

void GraphicsSystem::moveNewSimulationScreenUp(int currentMenuIndex)
{
	drawNewSimulationScreenWithSelection(currentMenuIndex, currentMenuIndex - 1);
}

void GraphicsSystem::drawNewSimulationScreenWithSelection(int previousSelection, int newSelection)
{
	//These are in format leftTriangleX1, triangleY, rightTriangleX1
	float newSimulationScreenArrows[][3] = {
		{ float(LAUNCHER_SCREENWIDTH)*0.49, float(LAUNCHER_SCREENHEIGHT)*0.235, 0 },
		{ float(LAUNCHER_SCREENWIDTH)*0.49, float(LAUNCHER_SCREENHEIGHT)*0.335, 0 },
		{ float(LAUNCHER_SCREENWIDTH)*0.49, float(LAUNCHER_SCREENHEIGHT)*0.435, 0 },
		{ float(LAUNCHER_SCREENWIDTH)*0.49, float(LAUNCHER_SCREENHEIGHT)*0.535, 0 },
		{ float(LAUNCHER_SCREENWIDTH)*0.49, float(LAUNCHER_SCREENHEIGHT)*0.635, 0 },
		{ float(LAUNCHER_SCREENWIDTH)*0.49, float(LAUNCHER_SCREENHEIGHT)*0.735, 0 },
		{ float(LAUNCHER_SCREENWIDTH)*0.49, float(LAUNCHER_SCREENHEIGHT)*0.835, 0 },
		{ float(LAUNCHER_SCREENWIDTH)*0.99, float(LAUNCHER_SCREENHEIGHT)*0.235, 0 },
		{ float(LAUNCHER_SCREENWIDTH)*0.99, float(LAUNCHER_SCREENHEIGHT)*0.335, 0 },
		{ float(LAUNCHER_SCREENWIDTH)*0.99, float(LAUNCHER_SCREENHEIGHT)*0.435, 0 },
		{ float(LAUNCHER_SCREENWIDTH)*0.99, float(LAUNCHER_SCREENHEIGHT)*0.535, 0 },
		{ float(LAUNCHER_SCREENWIDTH)*0.99, float(LAUNCHER_SCREENHEIGHT)*0.635, 0 },
		{ float(LAUNCHER_SCREENWIDTH)*0.99, float(LAUNCHER_SCREENHEIGHT)*0.735, 0 },
		{ float(LAUNCHER_SCREENWIDTH)*0.99, float(LAUNCHER_SCREENHEIGHT)*0.835, 0 },
		{ float(LAUNCHER_SCREENWIDTH)*0.4, float(LAUNCHER_SCREENHEIGHT)*0.935, float(LAUNCHER_SCREENWIDTH)*0.6 },
		{ float(LAUNCHER_SCREENWIDTH)*0.015, float(LAUNCHER_SCREENHEIGHT)*0.935, float(LAUNCHER_SCREENWIDTH)*0.185 },
		{ float(LAUNCHER_SCREENWIDTH)*0.82, float(LAUNCHER_SCREENHEIGHT)*0.935, float(LAUNCHER_SCREENWIDTH)*0.98 }
	};

	previousSelection = normalizeNewSimulationScreenIndex(previousSelection);
	newSelection = normalizeNewSimulationScreenIndex(newSelection);

	al_flip_display();
	if (newSelection >= 14 && previousSelection >= 14) {
		drawTriangle(newSimulationScreenArrows[previousSelection][0], newSimulationScreenArrows[previousSelection][1], 1, menuScreenBackgroundColour);
		drawTriangle(newSimulationScreenArrows[previousSelection][2], newSimulationScreenArrows[previousSelection][1], -1, menuScreenBackgroundColour);
		drawTriangle(newSimulationScreenArrows[newSelection][0], newSimulationScreenArrows[newSelection][1], 1, screenOptionsColour);
		drawTriangle(newSimulationScreenArrows[newSelection][2], newSimulationScreenArrows[newSelection][1], -1, screenOptionsColour);
	}
	if (newSelection >= 14) {
		drawTriangle(newSimulationScreenArrows[previousSelection][0], newSimulationScreenArrows[previousSelection][1], -1, menuScreenBackgroundColour);
		drawTriangle(newSimulationScreenArrows[newSelection][0], newSimulationScreenArrows[newSelection][1], 1, screenOptionsColour);
		drawTriangle(newSimulationScreenArrows[newSelection][2], newSimulationScreenArrows[newSelection][1], -1, screenOptionsColour);
	}
	else if (previousSelection >= 14) {
		drawTriangle(newSimulationScreenArrows[previousSelection][0], newSimulationScreenArrows[previousSelection][1], 1, menuScreenBackgroundColour);
		drawTriangle(newSimulationScreenArrows[previousSelection][2], newSimulationScreenArrows[previousSelection][1], -1, menuScreenBackgroundColour);
		drawTriangle(newSimulationScreenArrows[newSelection][0], newSimulationScreenArrows[newSelection][1], -1, screenOptionsColour);
	}
	else {
		drawTriangle(newSimulationScreenArrows[previousSelection][0], newSimulationScreenArrows[previousSelection][1], -1, menuScreenBackgroundColour);
		drawTriangle(newSimulationScreenArrows[newSelection][0], newSimulationScreenArrows[newSelection][1], -1, screenOptionsColour);
	}
	al_flip_display();
}

void GraphicsSystem::updateNewSimulationScreenString(int currentMenuItemIndex, char updateChar)
{
	currentMenuItemIndex = normalizeNewSimulationScreenIndex(currentMenuItemIndex);
	auto screenItem = allNewSimulationScreenOptions[currentMenuItemIndex];
	auto screenPositions = allNewSimulationScreenPositions[currentMenuItemIndex];
	int rectangleEndPosition = 0;
	if (currentMenuItemIndex >= 0 && currentMenuItemIndex < 7) {
		rectangleEndPosition = LAUNCHER_SCREENWIDTH * 0.45;
	}
	else {
		rectangleEndPosition = LAUNCHER_SCREENWIDTH * 0.95;
	}
	if (al_ustr_length(&get<1>(screenItem)) < 10) {
		al_flip_display();
		al_draw_filled_rectangle(
			LAUNCHER_SCREENWIDTH * (get<0>(screenPositions)),
			LAUNCHER_SCREENHEIGHT * (get<1>(screenPositions) + 0.015),
			rectangleEndPosition,
			LAUNCHER_SCREENHEIGHT * (get<1>(screenPositions) + 0.095),
			menuScreenBackgroundColour
		);
		al_ustr_append_chr(&get<1>(screenItem), updateChar);
		al_draw_ustr(screenOptionsFont,
			screenOptionsColour,
			LAUNCHER_SCREENWIDTH * get<0>(screenPositions),
			LAUNCHER_SCREENHEIGHT * get<1>(screenPositions),
			ALLEGRO_ALIGN_LEFT,
			&get<1>(screenItem)
		);
		al_flip_display();
		get<1>(allNewSimulationScreenOptions[currentMenuItemIndex]) = get<1>(screenItem);

		initializationValues[currentMenuItemIndex] += updateChar;
	}
	else {
		cout << "String cannot be longer than 10 characters!" << endl;
	}
}

void GraphicsSystem::removeCharFromNewSimluationScreenString(int currentMenuItemIndex)
{
	currentMenuItemIndex = normalizeNewSimulationScreenIndex(currentMenuItemIndex);
	auto screenItem = allNewSimulationScreenOptions[currentMenuItemIndex];
	auto screenPositions = allNewSimulationScreenPositions[currentMenuItemIndex];
	int rectangleEndPosition = 0;
	cout << currentMenuItemIndex << endl;
	if (currentMenuItemIndex >= 0 && currentMenuItemIndex < 7) {
		rectangleEndPosition = LAUNCHER_SCREENWIDTH * 0.45;
	}
	else {
		rectangleEndPosition = LAUNCHER_SCREENWIDTH * 0.95;
	}
	cout << rectangleEndPosition << endl;
	if (al_ustr_length(&get<1>(screenItem)) > 0) {
		al_flip_display();
		al_draw_filled_rectangle(
			LAUNCHER_SCREENWIDTH * (get<0>(screenPositions) - 0.001),
			LAUNCHER_SCREENHEIGHT * (get<1>(screenPositions) - 0.00249),
			rectangleEndPosition,
			LAUNCHER_SCREENHEIGHT * (get<1>(screenPositions) + 0.095),
			menuScreenBackgroundColour
		);
		al_ustr_remove_chr(&get<1>(screenItem), al_ustr_offset(&get<1>(screenItem), al_ustr_length(&get<1>(screenItem)) - 1));
		al_draw_ustr(screenOptionsFont,
			screenOptionsColour,
			LAUNCHER_SCREENWIDTH * get<0>(screenPositions),
			LAUNCHER_SCREENHEIGHT * get<1>(screenPositions),
			ALLEGRO_ALIGN_LEFT,
			&get<1>(screenItem)
		);
		al_flip_display();
		get<1>(allNewSimulationScreenOptions[currentMenuItemIndex]) = get<1>(screenItem);

		initializationValues[currentMenuItemIndex] = initializationValues[currentMenuItemIndex].substr(0, initializationValues[currentMenuItemIndex].size() - 1);
	}
}

void GraphicsSystem::exportSimluationConfiguration()
{
	cout << "Creating a file and exporting the list of rules we have generated" << endl;
	time_t currentTimeSinceEpoch = std::time(nullptr);
	stringstream streamForString;
	streamForString << currentTimeSinceEpoch;
	ofstream exportFile;
	string fileNameString = "simulationSettingsExport_" + streamForString.str() + ".txt";
	cout << "\tConfiguration File will be named " << fileNameString << endl;
	exportFile.open(fileNameString);
	exportFile << "||===================================================||\n";
	exportFile << "||     Project Psi Exported Configuration Setting    ||\n";
	exportFile << "||   Created By Bryton Leason and Samual Horovatin   ||\n";
	exportFile << "||===================================================||\n";
	exportFile << "||   Currently this file isn't used for importing    ||\n";
	exportFile << "|| In the future it will be and this will be removed ||\n";
	exportFile << "||===================================================||\n\n";
	exportFile << "//This value is used for something\n";
	exportFile << "Left Placeholder 1 Value is:  " << initializationValues[0] << "\n\n";
	exportFile << "//This value is used for something\n";
	exportFile << "Left Placeholder 2 Value is:  " << initializationValues[1] << "\n\n";
	exportFile << "//This value is used for something\n";
	exportFile << "Left Placeholder 3 Value is:  " << initializationValues[2] << "\n\n";
	exportFile << "//This value is used for something\n";
	exportFile << "Left Placeholder 4 Value is:  " << initializationValues[3] << "\n\n";
	exportFile << "//This value is used for something\n";
	exportFile << "Left Placeholder 5 Value is:  " << initializationValues[4] << "\n\n";
	exportFile << "//This value is used for something\n";
	exportFile << "Left Placeholder 6 Value is:  " << initializationValues[5] << "\n\n";
	exportFile << "//This value is used for something\n";
	exportFile << "Left Placeholder 7 Value is:  " << initializationValues[6] << "\n\n";
	exportFile << "//This value is used for something\n";
	exportFile << "Right Placeholder 1 Value is: " << initializationValues[7] << "\n\n";
	exportFile << "//This value is used for something\n";
	exportFile << "Right Placeholder 2 Value is: " << initializationValues[8] << "\n\n";
	exportFile << "//This value is used for something\n";
	exportFile << "Right Placeholder 3 Value is: " << initializationValues[9] << "\n\n";
	exportFile << "//This value is used for something\n";
	exportFile << "Right Placeholder 4 Value is: " << initializationValues[10] << "\n\n";
	exportFile << "//This value is used for something\n";
	exportFile << "Right Placeholder 5 Value is: " << initializationValues[11] << "\n\n";
	exportFile << "//This value is used for something\n";
	exportFile << "Right Placeholder 6 Value is: " << initializationValues[12] << "\n\n";
	exportFile << "//This value is used for something\n";
	exportFile << "Right Placeholder 7 Value is: " << initializationValues[13] << "\n\n";
	exportFile.close();
}

//Load Simulation Screen Functions
void GraphicsSystem::setupLoadSimulationScreen()
{
	al_clear_to_color(menuScreenBackgroundColour);
	al_draw_ustr(screenTitleFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.5,
		LAUNCHER_SCREENHEIGHT*0.005,
		ALLEGRO_ALIGN_CENTRE,
		loadSimulationScreenTitle
	);
	//Horizontal Bar
	al_draw_rectangle(
		0,
		LAUNCHER_SCREENHEIGHT*0.193,
		LAUNCHER_SCREENWIDTH,
		LAUNCHER_SCREENHEIGHT*0.197,
		screenOptionsColour,
		7
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.5,
		LAUNCHER_SCREENHEIGHT*0.5,
		ALLEGRO_ALIGN_CENTRE,
		loadSimulationStringOne
	);
	//Horizontal Bar
	al_draw_rectangle(
		0,
		LAUNCHER_SCREENHEIGHT*0.903,
		LAUNCHER_SCREENWIDTH,
		LAUNCHER_SCREENHEIGHT*0.907,
		screenOptionsColour,
		7
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.5,
		LAUNCHER_SCREENHEIGHT*0.90,
		ALLEGRO_ALIGN_CENTRE,
		loadSimulationGoBackString
	);
	drawTriangle(float(LAUNCHER_SCREENWIDTH)*0.4, float(LAUNCHER_SCREENHEIGHT)*0.935, 1, screenOptionsColour);
	drawTriangle(float(LAUNCHER_SCREENWIDTH)*0.6, float(LAUNCHER_SCREENHEIGHT)*0.935, -1, screenOptionsColour);
	al_flip_display();
}

int GraphicsSystem::normalizeLoadSimulationScreenIndex(int abnormalIndex)
{
	return normalizeScreenIndex(abnormalIndex, loadSimulationScreenMenuItems);
}

//Options Screen Functions
void GraphicsSystem::setupControlsScreen()
{
	al_clear_to_color(menuScreenBackgroundColour);
	al_draw_ustr(screenTitleFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.5,
		LAUNCHER_SCREENHEIGHT*0.005,
		ALLEGRO_ALIGN_CENTRE,
		controlsScreenTitle
	);
	//Horizontal Bar
	al_draw_rectangle(
		0,
		LAUNCHER_SCREENHEIGHT*0.193,
		LAUNCHER_SCREENWIDTH,
		LAUNCHER_SCREENHEIGHT*0.197,
		screenOptionsColour,
		7
	);
	al_draw_ustr(screenOptionsSmallFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.005,
		LAUNCHER_SCREENHEIGHT*0.2,
		ALLEGRO_ALIGN_LEFT,
		controlsStringOne
	);
	al_draw_ustr(screenOptionsSmallFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.005,
		LAUNCHER_SCREENHEIGHT*0.28,
		ALLEGRO_ALIGN_LEFT,
		controlsStringTwo
	);
	al_draw_ustr(screenOptionsSmallFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.005,
		LAUNCHER_SCREENHEIGHT*0.36,
		ALLEGRO_ALIGN_LEFT,
		controlsStringThree
	);
	al_draw_ustr(screenOptionsSmallFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.005,
		LAUNCHER_SCREENHEIGHT*0.44,
		ALLEGRO_ALIGN_LEFT,
		controlsStringFour
	);
	al_draw_ustr(screenOptionsSmallFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.005,
		LAUNCHER_SCREENHEIGHT*0.52,
		ALLEGRO_ALIGN_LEFT,
		controlsStringFive
	);
	//Horizontal Bar
	al_draw_rectangle(
		0,
		LAUNCHER_SCREENHEIGHT*0.903,
		LAUNCHER_SCREENWIDTH,
		LAUNCHER_SCREENHEIGHT*0.907,
		screenOptionsColour,
		7
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.5,
		LAUNCHER_SCREENHEIGHT*0.9,
		ALLEGRO_ALIGN_CENTRE,
		controlsGoBackString
	);
	drawTriangle(float(LAUNCHER_SCREENWIDTH)*0.4, float(LAUNCHER_SCREENHEIGHT)*0.935, 1, screenOptionsColour);
	drawTriangle(float(LAUNCHER_SCREENWIDTH)*0.6, float(LAUNCHER_SCREENHEIGHT)*0.935, -1, screenOptionsColour);
	al_flip_display();
}

//Credits Screen Functions
void GraphicsSystem::setupCreditsScreen()
{
	al_clear_to_color(menuScreenBackgroundColour);
	al_draw_ustr(screenTitleFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.5,
		LAUNCHER_SCREENHEIGHT*0.005,
		ALLEGRO_ALIGN_CENTRE,
		creditsScreenTitle
	);
	//Horizontal Bar
	al_draw_rectangle(
		0,
		LAUNCHER_SCREENHEIGHT*0.193,
		LAUNCHER_SCREENWIDTH,
		LAUNCHER_SCREENHEIGHT*0.197,
		screenOptionsColour,
		7
	);
	al_draw_ustr(screenOptionsSmallFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.005,
		LAUNCHER_SCREENHEIGHT*0.2,
		ALLEGRO_ALIGN_LEFT,
		creditsStringOne
	);
	al_draw_ustr(screenOptionsSmallFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.005,
		LAUNCHER_SCREENHEIGHT*0.28,
		ALLEGRO_ALIGN_LEFT,
		creditsStringTwo
	);
	al_draw_ustr(screenOptionsSmallFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.005,
		LAUNCHER_SCREENHEIGHT*0.36,
		ALLEGRO_ALIGN_LEFT,
		creditsStringThree
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.5,
		LAUNCHER_SCREENHEIGHT*0.70,
		ALLEGRO_ALIGN_CENTRE,
		creditsStringFour
	);
	//Horizontal Bar
	al_draw_rectangle(
		0,
		LAUNCHER_SCREENHEIGHT*0.903,
		LAUNCHER_SCREENWIDTH,
		LAUNCHER_SCREENHEIGHT*0.907,
		screenOptionsColour,
		7
	);
	al_draw_ustr(screenOptionsFont,
		screenOptionsColour,
		LAUNCHER_SCREENWIDTH*0.5,
		LAUNCHER_SCREENHEIGHT*0.9,
		ALLEGRO_ALIGN_CENTRE,
		creditsGoBackString
	);
	drawTriangle(float(LAUNCHER_SCREENWIDTH)*0.4, float(LAUNCHER_SCREENHEIGHT)*0.935, 1, screenOptionsColour);
	drawTriangle(float(LAUNCHER_SCREENWIDTH)*0.6, float(LAUNCHER_SCREENHEIGHT)*0.935, -1, screenOptionsColour);
	al_flip_display();
}

//Simulation Screen
void GraphicsSystem::setupSimulationScreen() {
	al_destroy_display(settingsDisplay);

	mainDisplay = al_create_display(GAME_SCREENWIDTH, GAME_SCREENHEIGHT);
	mainEventQueue = al_create_event_queue();
	al_register_event_source(mainEventQueue, al_get_display_event_source(mainDisplay));
	al_register_event_source(mainEventQueue, al_get_keyboard_event_source());
	al_set_window_title(mainDisplay, "Project Psi");

	al_clear_to_color(gameScreenBackgroundColour);
	al_draw_ustr(screenTitleFont,
		screenOptionsColour,
		GAME_SCREENWIDTH*0.5,
		GAME_SCREENHEIGHT*0.005,
		ALLEGRO_ALIGN_CENTRE,
		simulationScreenTitle
	);
	//Horizontal Bar
	al_draw_rectangle(
		0,
		GAME_SCREENHEIGHT*0.193,
		GAME_SCREENWIDTH,
		GAME_SCREENHEIGHT*0.197,
		screenOptionsColour,
		7
	);
	al_flip_display();
}

//Initialization Functions
int GraphicsSystem::initAddons() {

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
	settingsDisplay = al_create_display(LAUNCHER_SCREENWIDTH, LAUNCHER_SCREENHEIGHT);
	if (!settingsDisplay) {
		cout << "failed to create display!" << endl;
		return -1;
	}
	screenOptionsFont = al_load_ttf_font(font1Path, LAUNCHER_SCREENWIDTH / 25.6, 0);
	if (!screenOptionsFont) {
		cout << "Could not load \"testFont.ttf\"" << endl;
		cout << "Make sure the correct font is in the executable location!" << endl;
		screenOptionsFont = al_create_builtin_font();
	}
	screenOptionsSmallFont = al_load_ttf_font(font1Path, LAUNCHER_SCREENWIDTH / 36.6, 0);
	if (!screenOptionsSmallFont) {
		cout << "Could not load \"testFont.ttf\"" << endl;
		cout << "Make sure the correct font is in the executable location!" << endl;
		screenOptionsSmallFont = al_create_builtin_font();
	}
	screenTitleFont = al_load_ttf_font(font1Path, LAUNCHER_SCREENWIDTH / 12.8, 0);
	if (!screenTitleFont) {
		cout << "Could not load \"testFont.ttf\"" << endl;
		cout << "Make sure the correct font is in the executable location!" << endl;
		screenTitleFont = al_create_builtin_font();
	}
	settingsEventQueue = al_create_event_queue();
	al_register_event_source(settingsEventQueue, al_get_display_event_source(settingsDisplay));
	al_register_event_source(settingsEventQueue, al_get_keyboard_event_source());
	al_set_window_title(settingsDisplay, "Project Psi Launcher");

	return 0;
}

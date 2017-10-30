#pragma once
#ifndef ALLEGRO_HEADER
#define ALLEGRO_HEADER
	//Allegro includes
	#include <allegro5/allegro.h>
	#include <allegro5/allegro_font.h>
	#include <allegro5/allegro_ttf.h>
	#include <allegro5/allegro_primitives.h>

	//TODO: set up Linux support of windowed full screen
	#ifdef _WIN32
		#include <Windows.h>
		static const int GAME_SCREENWIDTH = GetSystemMetrics(SM_CXSCREEN);
		static const int GAME_SCREENHEIGHT = GetSystemMetrics(SM_CYSCREEN);
	#else
		//Try to keep only 16:9 resolution setups
		static const int GAME_SCREENWIDTH = 1280;
		static const int GAME_SCREENHEIGHT = 720;
	#endif
	static const int LAUNCHER_SCREENWIDTH = 1280;
	static const int LAUNCHER_SCREENHEIGHT = 720;

	//Generic Variables
	static const char * font1Path = "assets\\testFont.ttf";
	static ALLEGRO_DISPLAY *settingsDisplay = NULL;
	static ALLEGRO_DISPLAY *mainDisplay = NULL;
	static ALLEGRO_EVENT_QUEUE *mainEventQueue = NULL;
	static bool quit = false;
	static ALLEGRO_COLOR screenOptionsColour = al_map_rgb_f(0.8706, 0.7216, 0.5294); //burlywood colour
	static ALLEGRO_COLOR screenBackgroundColour = al_map_rgb_f(0, 0, 0); //black colour
	static ALLEGRO_FONT *screenOptionsFont = NULL;
	static ALLEGRO_FONT *screenOptionsSmallFont = NULL;
	static ALLEGRO_FONT *screenTitleFont = NULL;
#endif

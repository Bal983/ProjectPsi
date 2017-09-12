#pragma once

//TODO: set up Linux support of windowed full screen
#ifdef _WIN32
	//Sets screen to full screen windowed. Hard set for windows.
	#include <Windows.h>
	static const int SCREENWIDTH = GetSystemMetrics(SM_CXSCREEN);
	static const int SCREENHEIGHT = GetSystemMetrics(SM_CYSCREEN);
#else
	//Try to keep only 16:9 resolution setups
	static const int SCREENWIDTH = 1280;
	static const int SCREENHEIGHT = 720;
#endif

	//Generic Variables
	const char * font1Path = "assets\\testFont.ttf";
	ALLEGRO_DISPLAY *settingsDisplay = NULL;
	ALLEGRO_DISPLAY *mainDisplay = NULL;
	ALLEGRO_EVENT_QUEUE *mainEventQueue = NULL;
	bool quit = false;

//
// Made by Bryton Leason for project Psi
//

#pragma once
#ifndef GAMEMANAGER_HEADER
#define GAMEMANAGER_HEADER
#include "GameGenerator.h"
#include "GraphicsSystem.h"

class GameManager {
private:
	GameGenerator *gameGenerator;
	GraphicsSystem *graphicsSystem;
public:
	GameManager(GameGenerator*, GraphicsSystem*);
	void handleControl();
};
#endif
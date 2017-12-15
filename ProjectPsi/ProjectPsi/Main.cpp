//
// Made by Bryton Leason for project Psi
//

#include "AllegroSettings.h"
#include "GameGenerator.h"
#include "GameManager.h"
#include "GraphicsSystem.h"

int main(int argc, char **argv) {
	GraphicsSystem *graphicsSystem = new GraphicsSystem();

    if (graphicsSystem->initAddons() == -1) {
        return -1;
    }

	graphicsSystem->setupTitleScreen();

	int result = graphicsSystem->handleControl();
	switch(result) {
	case(0):
		return 0;
		break;
	case(1): //This is the case we are generating a game
		GameGenerator * gameGenerator = new GameGenerator(GAME_SCREENWIDTH*0.5, GAME_SCREENHEIGHT*0.5, graphicsSystem->getInitializationValues());
		gameGenerator->generate();
		gameGenerator->printMapToFile(); //Uncomment this if you want to see the generated array, it'll print to a file
		GameManager * manager = new GameManager(gameGenerator, graphicsSystem);
		manager->handleControl();
	}

    return 0;
}

//List of Bugs to track down
	//Sometimes the menu system gets into a weird state, figure out why
		//I think all of the "weird state" situations are now resolved.

//Todo in the future
	//Turn the logic surrounding the case statement above to make use of enumerations so it is a lot more clear
    //Get the menu system working with the mouse as well, for now keyboard controls will have to work

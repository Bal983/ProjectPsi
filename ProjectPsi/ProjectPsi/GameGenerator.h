//
// Made by Bryton Leason for project Psi
//

#pragma once
#ifndef GAMEGENERATOR_HEADER
#define GAMEGENERATOR_HEADER
#include <vector>

class GameGenerator {
	private:
		int widthOfBoard;
		int heightOfBoard;
		std::vector<std::vector<int>> gameBoard;
		std::string initValues[15];
		void generateSand();
		void generateSnow();
		void generateForest();
		void generateJungle();
		void generateRivers();
		void generateOceans();
		void smooth();
	public:
		GameGenerator(int, int, std::string values[15]);
		void generate();
		void printMapToFile();
};
#endif
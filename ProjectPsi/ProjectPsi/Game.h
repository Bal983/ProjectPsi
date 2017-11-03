#pragma once
#ifndef GAME_HEADER
#define GAME_HEADER
#include <vector>

class Game {
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
	public:
		Game(int, int, std::string values[15]);
		void generate();
		void smooth();
		void run();
		void printMapToFile();
};
#endif
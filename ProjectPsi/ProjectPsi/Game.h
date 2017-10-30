#pragma once
#ifndef GAME_HEADER
#define GAME_HEADER

class Game {
	private:
		int widthOfBoard;
		int heightOfBoard;
		std::string initValues[15];
	public:
		Game(int, int, std::string values[15]);
		void generate();
		void run();
};
#endif
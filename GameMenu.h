#pragma once
#include "Game.h"

class GameMenu
{
	Game* game = nullptr;

public:
	void intructions();
	void printMenu();
	void startNewGame(bool color);
};
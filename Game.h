#pragma once
#include <iostream>
#include <cctype>

using std::cout;
using std::cin;


#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "Coord.h"
#include "Board.h"
#include "BoardShapes.h"


class Game
{

public:
	static const int NUM_GHOSTS = 2;

private:
	BoardShapes _myBoard;
	Board _board; 
	Pacman _pacman;
	Ghost* _ghosts[NUM_GHOSTS];
	bool _gameOver;
	bool color;

public:
	Game(bool color);
	~Game();

	void GameLoop();
	void initGhosts();
	bool isGameOver();
	bool isWon();
	void movePac(Cell** board, char userKey);
	bool isGhostInCell(Coord newPacPos, int* index);
	void moveGhost(Ghost& ghost, Cell** board);
	bool isPacmanInCell(Coord currPacPos, Coord newGhostPos);
	void userPressESC(char& userKey);
	void deleteGhosts();

};



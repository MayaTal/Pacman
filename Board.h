#pragma once

#include <iostream>
#include <cctype>
using namespace std;

#include "Ghost.h"
#include "Pacman.h"


class Board
{
public:
	static const int ROWS = 21;
	static const int COLS = 80;

private:
	int row, col;
	Cell** the_board;
	Coord pacmanPos;
	Coord ghostCoords[2];
	int numOfBreadCrumbs;
public:
	Board(const int _row, const int _col, char** pattern);
	~Board();

	//GET
	inline const int getRowSize() const { return row; }
	inline const int getColSize() const { return col; }
	Coord getPacmanPosition() const { return pacmanPos; };
	Cell** getBoard() const { return the_board; }
	int getNumOfBreadCrumbs()const { return numOfBreadCrumbs; }
	Coord getGhostPos(int ghostNum);//TODO if out of arr boundary - do something but not fly, ask amir


	void printBoard(bool color) const;
	void deleteTheBoard();



};


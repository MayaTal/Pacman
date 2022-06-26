#include "Board.h"

Board::Board(const int _row, const int _col, char** pattern)
	:row(_row), col(_col)
{
	numOfBreadCrumbs = 0;
	int currGhost = 0;
	the_board = new Cell * [row];

	for (int i = 0; i < row; i++)
	{
		the_board[i] = new Cell[col];
		for (int j = 0; j < col; j++)
		{
			the_board[i][j].setCoord(i, j);
			switch (pattern[i][j])
			{
			case ' ':
				the_board[i][j].setSign(Cell::SIGN::NONE);
				break;
			case '@':
				the_board[i][j].setSign(Cell::SIGN::PACMAN);
				pacmanPos.setX(i);
				pacmanPos.setY(j);
				break;
			case '.':
				the_board[i][j].setSign(Cell::SIGN::BreadCrumbs);
				numOfBreadCrumbs++;
				break;
			case '#':
				the_board[i][j].setSign(Cell::SIGN::WALL);
				break;
			case '$':
				the_board[i][j].setSign(Cell::SIGN::GHOST_ON_CRUMB);
				ghostCoords[currGhost].setX(i);
				ghostCoords[currGhost].setY(j);
				currGhost++;
				break;
			default:
				break;
			}
		}
	}
}

void Board::printBoard(bool color)const
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			switch (the_board[i][j].getSign())
			{
			case Cell::SIGN::NONE:
				cout << ' ';
				break;
			case Cell::SIGN::PACMAN:
				if (color)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				cout << '@';
				break;
			case Cell::SIGN::BreadCrumbs:
				if (color)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
				cout << '.';
				break;
			case Cell::SIGN::WALL:
				if (color)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
				cout << '#';
				break;
			case Cell::GHOST_ON_CRUMB:
				if (color)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << '$';
				break;
			case Cell::GHOST_ON_NONE:
				if (color)
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				cout << ' ';
				break;
			default:
				break;
			}
		}
		cout << "\n";
	}

	cout << "\nLIVES:\nSCORE:" << endl;

}

Coord Board::getGhostPos(int ghostNum)
{
	return ghostCoords[ghostNum];
}


void Board::deleteTheBoard()
{
	for (int i = 0; i < ROWS; ++i)
	{
		delete the_board[i];
	}
	delete the_board;
}

Board:: ~Board()
{
	deleteTheBoard();
}

#include "Game.h"

Game::Game(bool color):
	_board(Board::ROWS, Board::COLS, (char**)_myBoard.board_shape_1), _pacman(_board.getPacmanPosition())
{
	initGhosts();

	_gameOver = false;
	this->color = color;
};

/*This function is running the game*/
void Game::GameLoop()
{
	
	_board.printBoard(color);
	_pacman.printLives(color);
	_pacman.printScore(color);

	char userKey = _getch();

	bool flag = true;

	while (!_gameOver)
	{
		while (!_kbhit() && !_gameOver)
		{
			Sleep(150);

			if (userKey == Cell::ESC)
				userPressESC(userKey);

			movePac(_board.getBoard(), userKey);

			if (flag)
			{
				for (int i = 0; i < NUM_GHOSTS; ++i)
				{
					moveGhost(*(_ghosts[i]), _board.getBoard());
				}

				flag = false;
			}
			else
			{
				flag = true;
			}


			if (isGameOver() || isWon())
			{
				_gameOver = true;
			}
		}
		if (!_gameOver)
		{
			userKey = _getch();
		}
	}
	system("cls");

	if (isGameOver())
	{
		if (color)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			cout << "\n\n\t\t\t\tGAME OVER!" << endl;
	}
	else/*The user won*/
	{
		if (color)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << "\n\n\t\t\t\tYOU WON! CONGRATULATION! :)" << endl;
	}

	userKey = _getch();
}
/*This function checks if the game is over*/
bool Game::isGameOver()
{
	bool res = false;
	if (_pacman.getLives() == 0)
	{
		res = true;
	}
	return res;
}

void Game::initGhosts()
{

	for (int i = 0; i < NUM_GHOSTS; ++i)
	{
		_ghosts[i] = new Ghost(_board.getGhostPos(i).getX(), _board.getGhostPos(i).getY());
	}

}

/*This function checks if the user is won, if he ate all the breadCrumbs*/
bool Game::isWon()
{
	bool res = false;

	if (_pacman.getScore() == _board.getNumOfBreadCrumbs())
	{
		res = true;
	}
	return res;
}

/*This function pauses the game until the user press ESC again*/
void Game::userPressESC(char& userKey)
{
	do
	{
		//system("Color 0A");
		gotoxy(7, 22);
		cout << "\t\t\t\t Game paused, press ESC again to continue";
		userKey = _getch();

	} while (userKey != Cell::ESC);
	userKey = 0;

	gotoxy(7, 22);
	cout << "\t\t\t\t                                         ";
	//system("color 07");
}


/*This function moves the pacman*/
void Game::movePac(Cell** board, char userKey)
{
	Coord toWhere = _pacman.setDirection(userKey); /*get the pamcan new direction*/

	Cell oldPos = board[_pacman.getCurrentPos().getX()][_pacman.getCurrentPos().getY()];
	Cell newPos = board[toWhere.getX()][toWhere.getY()];

	_pacman.checkCollision(newPos, oldPos, color);

	/*Updates the signs in the cells of the board */
	board[oldPos.getCoord().getX()][oldPos.getCoord().getY()].setSign(oldPos.getSign());
	board[newPos.getCoord().getX()][newPos.getCoord().getY()].setSign(newPos.getSign());

	int index;
	if (isGhostInCell(newPos.getCoord(), &index))
	{
		_pacman.pacmanHitsGhost(newPos, oldPos, color);
	}
}

bool Game::isGhostInCell(Coord newPacPos, int* index)
{
	bool res = false;
	for (int i = 0; i < NUM_GHOSTS; ++i)
	{
		if ((newPacPos.getX() == _ghosts[i]->getCurrentPos().getX()) &&
			(newPacPos.getY() == _ghosts[i]->getCurrentPos().getY()))
		{
			res = true;
			*index = i;
		}

	}
	return res;
}

/*This function moves the ghosts*/
void Game::moveGhost(Ghost& ghost, Cell** board)
{
	Cell toWhere = ghost.setDirection(board);/*get the ghost new direction*/

	Cell oldPos = board[ghost.getCurrentPos().getX()][ghost.getCurrentPos().getY()];
	Cell newPos = board[toWhere.getCoord().getX()][toWhere.getCoord().getY()];

	ghost.checkCollision(newPos, oldPos, board, color);

	/*Updates the signs in the cells of the board */
	board[oldPos.getCoord().getX()][oldPos.getCoord().getY()].setSign(oldPos.getSign());
	board[newPos.getCoord().getX()][newPos.getCoord().getY()].setSign(newPos.getSign());

	if (isPacmanInCell(_pacman.getCurrentPos(), newPos.getCoord()))
	{
		_pacman.pacmanHitsGhost(newPos, oldPos, color);
	}
}

bool Game::isPacmanInCell(Coord currPacPos, Coord newGhostPos)
{
	return(((currPacPos.getX() == newGhostPos.getX()) &&
		(currPacPos.getY() == newGhostPos.getY())));
}

void Game::deleteGhosts()
{
	for (int i = 0; i < NUM_GHOSTS; ++i)
	{
		delete _ghosts[i];
	}
}

Game::~Game()
{
	deleteGhosts();
}

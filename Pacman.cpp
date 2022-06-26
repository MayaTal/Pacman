#include "Pacman.h"

/*This function sets the pacman direction according to the user key*/
Coord Pacman::setDirection(char userDir)
{
	int x, y;

	x = currentPos.getX();
	y = currentPos.getY();

	Coord newPos(x, y);

	getDirectionUser(userDir);

	switch (direction)
	{
	case UP:
		x--;
		break;
	case DOWN:
		x++;
		break;
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;
	default:
		break;
	}

	/*Updates the new position according the direction*/
	newPos.setX(x);
	newPos.setY(y);

	return { newPos };
}

/*This function converts user key to specific direction */
void Pacman::getDirectionUser(char userDir)
{
	if (userDir == 'A' || userDir == 'a')
	{
		direction = DIRECTION::LEFT;
	}
	if (userDir == 'D' || userDir == 'd')
	{
		direction = DIRECTION::RIGHT;
	}
	if (userDir == 'W' || userDir == 'w')
	{
		direction = DIRECTION::UP;
	}
	if (userDir == 'X' || userDir == 'x')
	{
		direction = DIRECTION::DOWN;
	}
	if (userDir == 'S' || userDir == 's')
	{
		direction = DIRECTION::STAY;
	}
}


void Pacman::setLives(const int newLives)
{
	lives = newLives;
}
void Pacman::setScore(const int newScore)
{
	score = newScore;
}
void Pacman::setCurrentPos(const Coord& newPos)
{
	currentPos = newPos;
}

/*This function checks all the pacman's collision options - walll, breadCrumb or none*/
void Pacman::checkCollision(Cell& newPos, Cell& oldPos, bool color)
{
	if (newPos.getSign() == Cell::SIGN::WALL) /*if the pacman hits a wall, it stays in it's position*/
	{
		gotoxy(oldPos.getCoord().getY(), oldPos.getCoord().getX());
		if (color)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		cout << '@';


		currentPos = oldPos.getCoord();
	}
	else if (newPos.getSign() == Cell::SIGN::BreadCrumbs || newPos.getSign() == Cell::SIGN::NONE)
	{
		pacmanEatFood(newPos, oldPos, color);
		Tunnel(newPos, color);
	}

}


/*This function brings the pacman to it's starting position and takes one life of the pacman*/
void Pacman::pacmanHitsGhost(Cell& newPos, Cell& oldPos, bool color)
{
	gotoxy(oldPos.getCoord().getY(), oldPos.getCoord().getX());
	cout << ' ';
	oldPos.setSign(Cell::SIGN::NONE); /*Updates the sign in the cell*/

	newPos.setCoord(startPos.getX(), startPos.getY()); /*Brings back pacman to his start position*/
	gotoxy(newPos.getCoord().getY(), newPos.getCoord().getX());
	if (color)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << '@';
	newPos.setSign(Cell::SIGN::PACMAN);/*Updates the sign in the cell*/

	currentPos = newPos.getCoord();

	lives--; /*Updates pacman's lives*/

	printLives(color);
}

/*This function checks if the pacman got into a tunnel and acts according to it*/
void Pacman::Tunnel(Cell& newPos, bool color)
{
	Coord LTUNNEL = Coord(10, 0);
	Coord RTUNNEL = Coord(10, 79);
	Coord UTUNNEL = Coord(0, 40);
	Coord DTUNNEL = Coord(20, 40);

	if ((newPos.getCoord().getX() == LTUNNEL.getX()) && (newPos.getCoord().getY() == LTUNNEL.getY()))
	{
		updatePosAfterTunnel(newPos, RTUNNEL, color);
	}
	else if ((newPos.getCoord().getX() == RTUNNEL.getX()) && (newPos.getCoord().getY() == RTUNNEL.getY()))
	{
		updatePosAfterTunnel(newPos, LTUNNEL, color);
	}
	else if ((newPos.getCoord().getX() == UTUNNEL.getX()) && (newPos.getCoord().getY() == UTUNNEL.getY()))
	{
		updatePosAfterTunnel(newPos, DTUNNEL, color);
	}
	else if ((newPos.getCoord().getX() == DTUNNEL.getX()) && (newPos.getCoord().getY() == DTUNNEL.getY()))
	{
		updatePosAfterTunnel(newPos, UTUNNEL, color);

	}

	currentPos = newPos.getCoord();
}

/*This function updates pacman's new position*/
void Pacman::updatePosAfterTunnel(Cell& newPos, Coord tunnel, bool color)
{
	gotoxy(newPos.getCoord().getY(), newPos.getCoord().getX());
	cout << ' ';
	newPos.setSign(Cell::SIGN::NONE);

	gotoxy(tunnel.getY(), tunnel.getX());
	if (color)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << '@';
	newPos.setCoord(tunnel.getX(), tunnel.getY());
	newPos.setSign(Cell::SIGN::PACMAN);
}

/*This function checks if the pacman ate breadCrumb, and updates the score*/
void Pacman::pacmanEatFood(Cell& newPos, Cell& oldPos, bool color)
{
	if (newPos.getSign() == Cell::SIGN::BreadCrumbs)
	{
		score++;
		printScore(color);
	}

	gotoxy(oldPos.getCoord().getY(), oldPos.getCoord().getX());
	cout << ' ';
	oldPos.setSign(Cell::SIGN::NONE);

	gotoxy(newPos.getCoord().getY(), newPos.getCoord().getX());
	if (color)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << '@';
	newPos.setSign(Cell::SIGN::PACMAN);

	currentPos = newPos.getCoord();
}
//TODO define numbers
void Pacman::printLives(bool color)const
{
	gotoxy(LIVES::LIVES_COL, LIVES::LIVES_ROW);
	if(color)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << lives;
}

void Pacman::printScore(bool color)const
{
	gotoxy(SCORE::SCORE_COL, SCORE::SCORE_ROW);
	if (color)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	cout << score;
}

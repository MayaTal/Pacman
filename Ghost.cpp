#include"Ghost.h"

/*This function sets the ghost's direction according to the user key*/
Cell Ghost::setDirection(Cell** board)
{
	int x, y;
	int dir = rand() % 4;
	direction = (DIRECTION)dir;

	Cell newPos;

	x = currentPos.getX();
	y = currentPos.getY();

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

	newPos.setCoord(x, y);
	newPos.setSign(board[x][y].getSign());

	return { newPos };
}
/*This function only deals with collision with wall or food or none*/
void Ghost::checkCollision(Cell& newPos, Cell& oldPos, Cell** board, bool color)
{
	if (isTunnel(newPos))
	{
		ghostHitsTunnel(newPos, board);
	}
	if (newPos.getSign() == Cell::SIGN::WALL)
	{
		ghostHitsWalls(newPos, board);
	}

	ghostMovementOK(newPos, oldPos, color);

}

/*This function runs until the ghost changes it's direction from the tunnel*/
void Ghost::ghostHitsTunnel(Cell& newPos, Cell** board)
{
	while (isTunnel(newPos))
	{
		newPos = setDirection(board);
	}
}


bool Ghost::isTunnel(Cell& newPos)
{
	Coord LTUNNEL = Coord(10, 0);
	Coord RTUNNEL = Coord(10, 79);
	Coord UTUNNEL = Coord(0, 40);
	Coord DTUNNEL = Coord(20, 40);

	return (((newPos.getCoord().getX() == LTUNNEL.getX()) && (newPos.getCoord().getY() == LTUNNEL.getY())) ||
		((newPos.getCoord().getX() == RTUNNEL.getX()) && (newPos.getCoord().getY() == RTUNNEL.getY())) || 
		(newPos.getCoord().getX() == LTUNNEL.getX()) && (newPos.getCoord().getY() == LTUNNEL.getY()) || 
		(newPos.getCoord().getX() == UTUNNEL.getX()) && (newPos.getCoord().getY() == UTUNNEL.getY()));

}

/*This function runs until the ghost changes it's direction from the walls*/
void Ghost::ghostHitsWalls(Cell& newPos, Cell** board)
{
	while (newPos.getSign() == Cell::SIGN::WALL)
	{
		newPos = setDirection(board);
	}
}


/*This fction updates the ghost's new position*/
void Ghost::ghostMovementOK(Cell& newPos, Cell& oldPos, bool color)
{
	if (newPos.getSign() == Cell::SIGN::BreadCrumbs)
	{
		newPos.setSign(Cell::SIGN::GHOST_ON_CRUMB);
	}
	else if (newPos.getSign() == Cell::SIGN::NONE)
	{
		newPos.setSign(Cell::SIGN::GHOST_ON_NONE);
	}
	gotoxy(newPos.getCoord().getY(), newPos.getCoord().getX());
	if (color)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	cout << '$';

	gotoxy(oldPos.getCoord().getY(), oldPos.getCoord().getX());
	if (oldPos.getSign() == Cell::SIGN::GHOST_ON_CRUMB || oldPos.getSign() == Cell::SIGN::BreadCrumbs)
	{
		if (color)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		cout << '.';
		oldPos.setSign(Cell::SIGN::BreadCrumbs);
	}
	else
	{
		cout << ' ';
		oldPos.setSign(Cell::SIGN::NONE);
	}

	currentPos = newPos.getCoord();
}

void Ghost::setCurrentPos(const Coord& newPos)
{
	currentPos = newPos;
}

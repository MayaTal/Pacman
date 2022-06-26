#pragma once

#include "GoToXY.h"
#include "Coord.h"
#include "Cell.h"

class Ghost
{
public:
	enum DIRECTION { UP, DOWN, LEFT, RIGHT, STAY };
private:
	Coord startPos;
	Coord currentPos;
	DIRECTION direction;
public:
	Ghost(int startX, int startY)
		:startPos(startX, startY), currentPos(startX, startY)
	{
		direction = DIRECTION::STAY;
	}

	//GET
	Coord getCurrentPos() const { return currentPos; }
	Coord getStartPos() const { return startPos; }

	//SET
	void setCurrentPos(const Coord& newPos);

	Cell setDirection(Cell** board);
	void checkCollision(Cell& newPos, Cell& oldPos, Cell** board, bool color);
	void ghostHitsWalls(Cell& newPos, Cell** board);
	void ghostMovementOK(Cell& newPos, Cell& oldPos, bool color);
	bool isTunnel(Cell& newPos);
	void ghostHitsTunnel(Cell& newPos, Cell** board);
};

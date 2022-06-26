#pragma once
#include "Coord.h"
#include "Cell.h"
#include "GoToXY.h"


class Pacman
{
public:
	enum DIRECTION { UP, DOWN, LEFT, RIGHT, STAY };
	enum LIVES { LIVES_ROW = 22, LIVES_COL = 7};
	enum SCORE { SCORE_ROW = 23, SCORE_COL = 7 };
	
private:
	Coord startPos;
	Coord currentPos;
	DIRECTION direction;
	int lives;
	int score;


public:
	Pacman(Coord initialPosition)
		:startPos(initialPosition), currentPos(initialPosition)
	{
		direction = DIRECTION::STAY;
		lives = 3;
		score = 0;
	}

	//GET
	int getLives()const { return lives; }
	int getScore() const { return score; }
	Coord getCurrentPos() const { return currentPos; }
	Coord getStartPos()const { return startPos; }

	//SET
	void setLives(const int newLives);
	void setScore(const int newScore);
	void setCurrentPos(const Coord& newPos);

	Coord setDirection(char userDir); 
	void getDirectionUser(char userDir);
	void checkCollision(Cell& newPos, Cell& oldPos, bool color);
	void pacmanHitsGhost(Cell& newPos, Cell& oldPos, bool color);
	void pacmanEatFood(Cell& newPos, Cell& oldPos, bool color);
	void printLives(bool color) const;
	void printScore(bool color) const;
	void Tunnel(Cell& newPos, bool color);
	void updatePosAfterTunnel(Cell& newPos, Coord tunnel, bool color);

};
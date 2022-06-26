#pragma once

#include <iostream>
#include <cctype>
using namespace std;
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

class Cell
{
public:
	enum SIGN { PACMAN, BreadCrumbs, WALL, NONE, GHOST_ON_CRUMB, GHOST_ON_NONE };
	static Coord LTUNNEL;
	static Coord RTUNNEL;
	static const int ESC = 27;

private:
	Coord position;
	SIGN contains;

public:
	Cell() : position(position), contains(NONE) {}

	//GET
	SIGN getSign() const
	{
		return contains;
	}
	Coord getCoord()const
	{
		return position;
	}


	//SET
	void setCoord(const int newX, const int newY)
	{
		position.setX(newX);
		position.setY(newY);
	}
	void setSign(const SIGN newSign)
	{
		contains = newSign;
	}
};
/*
 * Position.cpp
 *
 *  Created on: Feb 14, 2015
 *      Author: rmin
 */

#include "Position.h"

Position::Position(int x, int y) {
	this->x = x;
	this->y = y;
}

Position::Position(const Position &position) {
	this->x = position.x;
	this->y = position.y;
}

void Position::operator = (const Position &source)
{
	this->x = source.x;
	this->y = source.y;
}

Position Position::getNextPos(Direction dir) {
	if (x % 2 == 1)
		switch (dir) {
		case NORTH:
			return Position(x, y + 1);

		case SOUTH:
			return Position(x, y - 1);

		case NORTH_EAST:
			return Position(x + 1, y);

		case NORTH_WEST:
			return Position(x - 1, y);

		case SOUTH_EAST:
			return Position(x + 1, y - 1);

		case SOUTH_WEST:
			return Position(x - 1, y - 1);
		}
	else {
		switch (dir) {
		case NORTH:
			return Position(x, y + 1);

		case SOUTH:
			return Position(x, y - 1);

		case NORTH_EAST:
			return Position(x + 1, y + 1);

		case NORTH_WEST:
			return Position(x - 1, y + 1);

		case SOUTH_EAST:
			return Position(x + 1, y);

		case SOUTH_WEST:
			return Position(x - 1, y);

		}
	}
	return Position(0,0);
}

int Position::getX() {
	return x;
}

int Position::getY() {
	return y;
}

std::ostream& operator << (std::ostream& out,Position pos) {
	out << pos.getX() << " " << pos.getY();
	return out;
}

bool Position::operator == (Position &source) {
	if(this->x == source.getX() && this->y == source.getY())
		return true;
	return false;
}

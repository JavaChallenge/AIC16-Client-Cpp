/*
 * Position.h
 *
 *  Created on: Feb 14, 2015
 *      Author: rmin
 */

#ifndef POSITION_H_
#define POSITION_H_

#include <iostream>

#include "Direction.h"

class Position {
	int x;
	int y;
public:
	Position(int x = 0, int y = 0);
	Position(const Position &position);

	void operator = (const Position &source);
	bool operator == (Position &source);
	Position getNextPos(Direction dir);
	int getX();
    int getY();
    friend std::ostream& operator << (std::ostream& out,Position pos);
};
#endif /* POSITION_H_ */

/*
 * MapSize.cpp
 *
 *  Created on: Feb 14, 2015
 *      Author: rmin
 */

#include "MapSize.h"

MapSize::MapSize(int width, int height) : width(width), height(height) {
	// TODO Auto-generated constructor stub
}

MapSize::~MapSize() {
	// TODO Auto-generated destructor stub
}

const int MapSize::getWidth()
{
	return width;
}

const int MapSize::getHeight()
{
	return height;
}

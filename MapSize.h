/*
 * MapSize.h
 *
 *  Created on: Feb 14, 2015
 *      Author: rmin
 */

#ifndef MAPSIZE_H_
#define MAPSIZE_H_

class MapSize {
private:
	int width,height;
public:
	MapSize(int width = 100,int height = 100);
	virtual ~MapSize();
	const int getWidth();
	const int getHeight();
};

#endif /* MAPSIZE_H_ */

/*
 * Map.h
 *
 *  Created on: Feb 14, 2015
 *      Author: rmin
 */

#ifndef MAP_H_
#define MAP_H_

#include "Block.h"
#include "MapSize.h"
#include <vector>
#include "StaticData.h"
#include "Constants.h"
#include <string>
#include <map>

class Map {
private:
	int width,height;
	Block*** blocks;
	MapSize mapSize;
	std::map<std::string,Position*> idToPos;

public:
	Map(MapSize &mapSize, std::vector<Json::Value> &mapData);
	bool setChange(Json::Value &value);
	bool isBlockType(std::string type);
	Block* at(Position &pos);
	Block* at(int x,int y);
	virtual ~Map();
};

#endif /* MAP_H_ */

/*
 * Map.cpp
 *
 *  Created on: Feb 14, 2015
 *      Author: rmin
 */

#include "Map.h"

Map::Map(MapSize &mapSize, std::vector<Json::Value> &mapData) {
	blocks = (Block***) new Block**[mapSize.getHeight()];
	for (int i = 0; i < mapSize.getHeight(); i++) {
		blocks[i] = (Block**) new Block*[mapSize.getWidth()];
	}

	for (int i = 0; i < mapSize.getHeight(); i++)
		for (int j = 0; j < mapSize.getWidth(); j++) {
			blocks[i][j] = NULL;
		}

	for (int i = 0; i < (int) mapData.size(); i++) {
		if (isBlockType(mapData[i][Constants::BLOCK_KEY_TYPE].asString())) {
			Position *pos = new Position(
					mapData[i][Constants::GAME_OBJECT_KEY_POSITION][Constants::POSITION_KEY_X].asInt(),
					mapData[i][Constants::GAME_OBJECT_KEY_POSITION][Constants::POSITION_KEY_Y].asInt());
			idToPos[mapData[i][Constants::GAME_OBJECT_KEY_ID].asString()] = pos;
			setChange(mapData[i]);
		}
	}

	this->mapSize = mapSize;
}

bool Map::setChange(Json::Value& value) {
	Position *pos = idToPos[value[Constants::GAME_OBJECT_KEY_ID].asString()];
	if (at(*pos) == NULL) {
		blocks[pos->getY()][pos->getX()] = new Block(value);
	} else {
		at(*pos)->setChange(value);
	}
	return true;
}

bool Map::isBlockType(std::string type) {
	if (type == Constants::BLOCK_TYPE_NONE
			|| type == Constants::BLOCK_TYPE_NORMAL
			|| type == Constants::BLOCK_TYPE_MITOSIS
			|| type == Constants::BLOCK_TYPE_RESOURCE
			|| type == Constants::BLOCK_TYPE_IMPASSABLE)
		return true;
	return false;
}

Block* Map::at(Position &pos) {
	return blocks[pos.getY()][pos.getX()];
}

Block* Map::at(int x, int y) {
	return blocks[y][x];
}

Map::~Map() {
	for(std::map<std::string,Position*>::iterator it = idToPos.begin(); it != idToPos.end(); it++)
	{
		delete (*it).second;
	}
	idToPos.clear();

	for (int i = 0; i < mapSize.getHeight(); i++)
		for (int j = 0; j < mapSize.getWidth(); j++)
			if (blocks[i][j] != NULL)
				delete blocks[i][j];
	for (int i = 0; i < mapSize.getHeight(); i++)
		delete blocks[i];
	delete blocks;
}

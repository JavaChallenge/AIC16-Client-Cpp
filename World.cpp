/*
 * World.cpp
 *
 *  Created on: Feb 15, 2015
 *      Author: rmin
 */

#include "World.h"

World::World(EventHandler* eventHandler, ClientInitInfo *initInfo, Map *map) {
	// TODO Auto-generated constructor stub
	this->eventHandler = eventHandler;
	this->teams = initInfo->getTeams();
	this->myId = initInfo->getYourInfo().getId();
	this->myName = initInfo->getYourInfo().getName();
	this->mapSize = initInfo->getMapSize();
	this->blockCoefficient = initInfo->getBlockCoefficient();
	Constants::BLOCK_HEIGHT_COEFFICIENT = this->blockCoefficient;
	this->map = map;
	this->turn = initInfo->getTurn();
}

World::~World() {
	// TODO Auto-generated destructor stub
	delete map;
}

std::vector<std::string>& World::getTeams() {
	return teams;
}

int World::getMyId() {
	return myId;
}

std::string World::getMyName() {
	return myName;
}

MapSize World::getMapSize() {
	return mapSize;
}

Map* World::getMap() {
	return map;
}

int World::getTurn() {
	return turn;
}

void World::setTurn(int turn) {
	this->turn = turn;
}

void World::addCell(Cell *cell) {
	std::string id = cell->getId();
	allCells[id] = cell;
	allVisitedCells[id] = cell;
	if (cell->getTeamId() == myId) {
		myCells[id] = cell;
	} else {
		enemyCells[id] = cell;
	}
}

void World::visibleCell(Cell *cell) {
	std::string id = cell->getId();
	allCells[id] = cell;
	allVisitedCells[id] = cell;
	if (cell->getTeamId() == myId) {
		myCells[id] = cell;
	} else {
		enemyCells[id] = cell;
	}
	invisibleCells.erase(id);
}

void World::invisibleCell(Cell *cell) {
	std::string id = cell->getId();
	invisibleCells[id] = cell;
	if (allCells.find(id) != allCells.end())
		allCells.erase(id);
	if (myCells.find(id) != myCells.end())
		myCells.erase(id);
	if (enemyCells.find(id) != enemyCells.end())
		enemyCells.erase(id);
}

void World::killCell(Cell *cell) {
	std::string id = cell->getId();
	if (allVisitedCells.find(id) != allVisitedCells.end())
		allVisitedCells.erase(id);

	if (allCells.find(id) != allCells.end())
		allCells.erase(id);

	if (myCells.find(id) != myCells.end())
		myCells.erase(id);

	if (enemyCells.find(id) != enemyCells.end())
		enemyCells.erase(id);

	if (invisibleCells.find(id) != invisibleCells.end())
		invisibleCells.erase(id);
}

std::vector<Cell*> World::getAllCells() {
	std::vector<Cell*> res;
	for (std::map<std::string, Cell*>::iterator it = allCells.begin();
			it != allCells.end(); it++)
		res.push_back((*it).second);
	return res;
}

std::vector<Cell*> World::getMyCells() {
	std::vector<Cell*> res;
	for (std::map<std::string, Cell*>::iterator it = myCells.begin();
			it != myCells.end(); it++)
		res.push_back((*it).second);
	return res;
}

std::vector<Cell*> World::getEnemyCells() {
	std::vector<Cell*> res;
	for (std::map<std::string, Cell*>::iterator it = enemyCells.begin();
			it != enemyCells.end(); it++)
		res.push_back((*it).second);
	return res;
}

std::map<std::string, Cell*> World::getAllCellsMap() {
	return allCells;
}

std::map<std::string, Cell*> World::getMyCellsMap() {
	return myCells;
}

std::map<std::string, Cell*> World::getEnemyCellsMap() {
	return enemyCells;
}

void World::setStaticChange(Json::Value &msg) {
	map->setChange(msg);
}

void World::setDynamicChange(Json::Value &msg) {
	std::string id = msg[Constants::GAME_OBJECT_KEY_ID].asString();
	std::map<std::string,Cell*>::iterator it = allVisitedCells.find(id);
	Cell *cell = (*it).second;
	if (it == allVisitedCells.end()) {
		Cell *c = new Cell(eventHandler, msg);
		addCell(c);
	} else {
		if (msg[Constants::GAME_OBJECT_KEY_TYPE] != Json::Value::null
				&& msg[Constants::GAME_OBJECT_KEY_TYPE].asString()
						== Constants::GAME_OBJECT_TYPE_DESTROYED) {
			// cell is dead
			killCell(cell);
		}
		else if(cell->getTeamId() != this->getMyId())
		{
			//is opponent
			if(msg[Constants::CELL_KEY_VISIBLE] != Json::Value::null)
			{
				int vis = msg[Constants::CELL_KEY_VISIBLE].asInt();
				if(vis == 0)
				{
					//cell exited from visible area
					invisibleCell(cell);
				}
				else
				{
					//cell return to visible area
					visibleCell(cell);
					cell->setChange(msg);
				}
			}
			else
			{
				cell->setChange(msg);
			}
		}
		else
		{
			cell->setChange(msg);
		}
	}
}

void World::clearDynamic() {
	for (std::map<std::string,Cell*>::iterator it = allCells.begin(); it != allCells.end(); it++) {
		delete (*it).second;
	}
	allCells.clear();
	myCells.clear();
	enemyCells.clear();
}

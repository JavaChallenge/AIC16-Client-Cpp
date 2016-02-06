/*
 * World.h
 *
 *  Created on: Feb 15, 2015
 *      Author: rmin
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <vector>
#include <map>
#include <string>
#include "MapSize.h"
#include "ClientInitInfo.h"
#include "EventHandler.h"
#include "DynamicData.h"
#include "Cell.h"
#include "Map.h"

class World {
	std::vector<std::string> teams;
	int myId;
	std::string myName;
	MapSize mapSize;
	Map *map;
	int turn, blockCoefficient;
	std::map<std::string, Cell*> allCells;
	std::map<std::string, Cell*> myCells;
	std::map<std::string, Cell*> enemyCells;
	std::map<std::string, Cell*> allVisitedCells;
	std::map<std::string, Cell*> invisibleCells;
	EventHandler* eventHandler;
public:
	World(EventHandler* eventHandler, ClientInitInfo *initInfo, Map *map);
	virtual ~World();
	void clearDynamic();
	std::vector<std::string>& getTeams();
	int getMyId();
	std::string getMyName();
	MapSize getMapSize();
	Map* getMap();
	int getTurn();
	void setTurn(int turn);
	void addCell(Cell *cell);
	void visibleCell(Cell *cell);
	void invisibleCell(Cell *cell);
	void killCell(Cell *cell);

	std::vector<Cell*> getAllCells();
	std::vector<Cell*> getMyCells();
	std::vector<Cell*> getEnemyCells();

	std::map<std::string, Cell*> getAllCellsMap();
	std::map<std::string, Cell*> getMyCellsMap();
	std::map<std::string, Cell*> getEnemyCellsMap();

	void setStaticChange(Json::Value &msg);
	void setDynamicChange(Json::Value &msg);
};

#endif /* WORLD_H_ */

/*
 * Cell.h
 *
 *  Created on: Feb 14, 2015
 *      Author: rmin
 */

#ifndef CELL_H_
#define CELL_H_

#include "GameEvent.h"
#include "DynamicData.h"
#include "Position.h"
#include "EventHandler.h"
#include <string>
#include "Direction.h"

class Cell {
private:
	EventHandler* eventHandler;
	std::string id;
	Position pos;
	int teamId;
	int energy;

	int depthOfField;
	int jump;
	int gainRate;
	int attackValue;

public:
	Cell(EventHandler* eventHandler, Json::Value &msg);
	void setChange(Json::Value &msg);

	void move(Direction direction);
	void gainResource();
	void mitosis();
	void attack(Direction direction);

	std::string getId();
	Position& getPos();
	int getTeamId();
	int getEnergy();
	int getAttackValue();
	int getGainRate();
	int getJump();
	int getDepthOfField();

	virtual ~Cell();
};

#endif /* CELL_H_ */

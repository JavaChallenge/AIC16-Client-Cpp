/*
 * Block.h
 *
 *  Created on: Feb 14, 2015
 *      Author: rmin
 */

#ifndef BLOCK_H_
#define BLOCK_H_

#include "Position.h"
#include "StaticData.h"
#include "Message.h"
#include <string>

class Block {
	Position pos;
	int height, resource, turn, minHeight;
	std::string type, id;
	int gainImprovementAmount, depthOfFieldImprovementAmount,
			jumpImprovementAmount, attackImprovementAmount;
public:
	Block(Json::Value &msg);
	virtual ~Block();

	void setChange(Json::Value &msg);

	Position getPos();
	int getHeight();
	int getMinHeight();
	int getResource();
	std::string getType();
	std::string getId();
	int getTurn();
	int getGainImprovementAmount();
	int getDepthOfFieldImprovementAmount();
	int getJumpImprovementAmount();
	int getAttackImprovementAmount();
};

#endif /* BLOCK_H_ */

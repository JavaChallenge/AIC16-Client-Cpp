/*
 * Block.cpp
 *
 *  Created on: Feb 14, 2015
 *      Author: rmin
 */

#include "Block.h"

Block::Block(Json::Value &msg) {
	this->id = msg[Constants::GAME_OBJECT_KEY_ID].asString();
	setChange(msg);
}

Block::~Block() {
	// TODO Auto-generated destructor stub
}

void Block::setChange(Json::Value &msg) {
	if (msg[Constants::GAME_OBJECT_KEY_TYPE] != Json::Value::null)
		type = msg[Constants::GAME_OBJECT_KEY_TYPE].asString();

	if (msg[Constants::GAME_OBJECT_KEY_ID] != Json::Value::null)
		this->id = msg[Constants::GAME_OBJECT_KEY_ID].asString();

	if (msg[Constants::GAME_OBJECT_KEY_POSITION] != Json::Value::null)
		this->pos =
				Position(
						msg[Constants::GAME_OBJECT_KEY_POSITION][Constants::POSITION_KEY_X].asInt(),
						msg[Constants::GAME_OBJECT_KEY_POSITION][Constants::POSITION_KEY_Y].asInt());

	if (msg[Constants::BLOCK_KEY_HEIGHT] != Json::Value::null)
		this->height = msg[Constants::BLOCK_KEY_HEIGHT].asInt();

	if (msg[Constants::BLOCK_KEY_MIN_HEIGHT] != Json::Value::null)
		this->minHeight = msg[Constants::BLOCK_KEY_MIN_HEIGHT].asInt();

	if (msg[Constants::BLOCK_KEY_RESOURCE] != Json::Value::null)
		this->resource = msg[Constants::BLOCK_KEY_RESOURCE].asInt();
	else
		this->resource = 0;

	if (msg[Constants::BLOCK_KEY_TURN] != Json::Value::null)
		this->turn = msg[Constants::BLOCK_KEY_TURN].asInt();

	if (msg[Constants::BLOCK_KEY_TYPE] != Json::Value::null)
		this->type = msg[Constants::BLOCK_KEY_TYPE].asString();

	if (msg[Constants::BLOCK_KEY_JUMP_IMP] != Json::Value::null)
		this->jumpImprovementAmount =
				msg[Constants::BLOCK_KEY_JUMP_IMP].asInt();
	else
		this->jumpImprovementAmount = 0;

	if (msg[Constants::BLOCK_KEY_ATTACK_IMP] != Json::Value::null)
		this->attackImprovementAmount =
				msg[Constants::BLOCK_KEY_ATTACK_IMP].asInt();
	else
		this->attackImprovementAmount = 0;

	if (msg[Constants::BLOCK_KEY_DEPTH_OF_FIELD_IMP] != Json::Value::null)
		this->depthOfFieldImprovementAmount =
				msg[Constants::BLOCK_KEY_DEPTH_OF_FIELD_IMP].asInt();
	else
		this->depthOfFieldImprovementAmount = 0;

	if (msg[Constants::BLOCK_KEY_GAIN_RATE_IMP] != Json::Value::null)
		this->gainImprovementAmount =
				msg[Constants::BLOCK_KEY_GAIN_RATE_IMP].asInt();
	else
		this->gainImprovementAmount = 0;
}

Position Block::getPos() {
	return pos;
}

int Block::getHeight() {
	return std::min(
			getMinHeight()
					+ getResource() / Constants::BLOCK_HEIGHT_COEFFICIENT,
			Constants::BLOCK_MAX_HEIGHT);
}

int Block::getMinHeight() {
	return minHeight;
}

int Block::getResource() {
	return resource;
}

std::string Block::getType() {
	return type;
}

std::string Block::getId() {
	return id;
}

int Block::getTurn() {
	return turn;
}

int Block::getGainImprovementAmount() {
	if (type == Constants::BLOCK_TYPE_MITOSIS) {
		return gainImprovementAmount;
	}
	return 0;
}

int Block::getDepthOfFieldImprovementAmount() {
	if (type == Constants::BLOCK_TYPE_MITOSIS) {
		return depthOfFieldImprovementAmount;
	}
	return 0;
}

int Block::getJumpImprovementAmount() {
	if (type == Constants::BLOCK_TYPE_MITOSIS) {
		return jumpImprovementAmount;
	}
	return 0;
}

int Block::getAttackImprovementAmount() {
	if (type == Constants::BLOCK_TYPE_MITOSIS) {
		return attackImprovementAmount;
	}
	return 0;
}

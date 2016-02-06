/*
 * Cell.cpp
 *
 *  Created on: Feb 14, 2015
 *      Author: rmin
 */

#include "Cell.h"
#include <chrono>

Cell::Cell(EventHandler* eventHandler, Json::Value &msg) {
	this->eventHandler = eventHandler;
	this->id = msg[Constants::GAME_OBJECT_KEY_ID].asString();
	this->teamId = msg[Constants::GAME_OBJECT_KEY_TEAM_ID].asInt();
	setChange(msg);
}

void Cell::setChange(Json::Value &msg) {
	if (msg[Constants::GAME_OBJECT_KEY_ID] != Json::Value::null)
		this->id = msg[Constants::GAME_OBJECT_KEY_ID].asString();

	if (msg[Constants::GAME_OBJECT_KEY_TEAM_ID] != Json::Value::null)
		this->teamId = msg[Constants::GAME_OBJECT_KEY_TEAM_ID].asInt();

	if (msg[Constants::GAME_OBJECT_KEY_POSITION] != Json::Value::null)
		this->pos =
				Position(
						msg[Constants::GAME_OBJECT_KEY_POSITION][Constants::POSITION_KEY_X].asInt(),
						msg[Constants::GAME_OBJECT_KEY_POSITION][Constants::POSITION_KEY_Y].asInt());

	if (msg[Constants::CELL_KEY_ENERGY] != Json::Value::null)
		this->energy = msg[Constants::CELL_KEY_ENERGY].asInt();

	if (msg[Constants::CELL_KEY_DEPTH_OF_FIELD] != Json::Value::null)
		this->depthOfField = msg[Constants::CELL_KEY_DEPTH_OF_FIELD].asInt();

	if (msg[Constants::CELL_KEY_JUMP] != Json::Value::null)
		this->jump = msg[Constants::CELL_KEY_JUMP].asInt();

	if (msg[Constants::CELL_KEY_GAIN_RATE] != Json::Value::null)
		this->gainRate = msg[Constants::CELL_KEY_GAIN_RATE].asInt();

	if (msg[Constants::CELL_KEY_ATTACK] != Json::Value::null)
		this->attackValue = msg[Constants::CELL_KEY_ATTACK].asInt();
}

void Cell::move(Direction direction) {
	GameEvent* event = new GameEvent(Constants::TYPE_MOVE);
	event->setObjectId(id);
	event->addArg(Constants::DirectionStr[direction]);

	eventHandler->addEvent(event);
}

void Cell::gainResource() {
	GameEvent *event = new GameEvent(Constants::TYPE_GAIN_RESOURCE);
	event->setObjectId(id);

	eventHandler->addEvent(event);
}

void Cell::mitosis() {
	GameEvent *event = new GameEvent(Constants::TYPE_MITOSIS);
	event->setObjectId(id);

	eventHandler->addEvent(event);
}

void Cell::attack(Direction direction) {
	GameEvent* event = new GameEvent(Constants::TYPE_ATTACK);
	event->setObjectId(id);
	event->addArg(Constants::DirectionStr[direction]);

	eventHandler->addEvent(event);
}

std::string Cell::getId() {
	return id;
}

Position& Cell::getPos() {
	return pos;
}

int Cell::getTeamId() {
	return teamId;
}

int Cell::getEnergy() {
	return energy;
}

int Cell::getAttackValue() {
	return attackValue;
}

int Cell::getGainRate() {
	return gainRate;
}

int Cell::getJump() {
	return jump;
}

int Cell::getDepthOfField() {
	return depthOfField;
}

Cell::~Cell() {
	// TODO Auto-generated destructor stub
}


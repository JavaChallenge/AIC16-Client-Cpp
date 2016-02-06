/*
 * GameEvent.cpp
 *
 *  Created on: Feb 14, 2015
 *      Author: rmin
 */

#include "GameEvent.h"

GameEvent::GameEvent(Event event) :
		Event(event) {
	// TODO Auto-generated constructor stub
	teamId = 0;
}

GameEvent::GameEvent(std::string type) {
	this->type = type;
	int argsLen = 0;
	if (type == Constants::TYPE_MOVE)
		argsLen = Constants::ARGS_NUMBER_MOVE;
	else if (type == Constants::TYPE_GAIN_RESOURCE) {

	} else if (type == Constants::TYPE_MITOSIS) {

	} else if (type == Constants::TYPE_ATTACK) {
		argsLen = Constants::ARGS_NUMBER_ATTACK;
	} else {
		throw "UNKNOWN EVENT TYPE\n";
	}
	teamId = 0;
}

int GameEvent::getTeamId() {
	return teamId;
}

void GameEvent::setTeamId(int teamId) {
	this->teamId = teamId;
}

void GameEvent::setObjectId(std::string objectId) {
	this->objectId = objectId;
}

void GameEvent::addArg(std::string value) {
	args.push_back(value);
}

void GameEvent::setArg(std::string value, int index) {
	if (index < (int) args.size() && index >= 0)
		args[index] = value;
}

GameEvent::~GameEvent() {
	// TODO Auto-generated destructor stub
}


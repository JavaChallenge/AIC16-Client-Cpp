/*
 * StaticData.cpp
 *
 *  Created on: Feb 14, 2015
 *      Author: rmin
 */

#include "StaticData.h"

StaticData::StaticData(const StaticData &source) :
		StaticData(source.getId(), source.getTurn(), source.getPosition(), source.getType(),
				source.getOther()) {
	// TODO Auto-generated constructor stub
}

StaticData::StaticData()
{
	turn = 0;
	other = NULL;
}

StaticData::StaticData(std::string id, int turn, Position position,
		std::string type, Json::Value& other) {
	this->id = id;
	this->turn = turn;
	this->position = position;
	this->type = type;
	this->other = &other;
}

StaticData::~StaticData() {
	// TODO Auto-generated destructor stub
}

void StaticData::setId(std::string id)
{
	this->id = id;
}

void StaticData::setType(std::string type)
{
	this->type = type;
}

void StaticData::setTurn(int turn) {
	this->turn = turn;
}

void StaticData::setPosition(Position position) {
	this->position = position;
}

void StaticData::setOther(Json::Value& other) {
	this->other = &other;
}

std::string StaticData::getType() const {
	return type;
}

std::string StaticData::getId() const {
	return id;
}

int StaticData::getTurn() const {
	return turn;
}

Position StaticData::getPosition() const {
	return position;
}

Json::Value& StaticData::getOther() const {
	return *other;
}

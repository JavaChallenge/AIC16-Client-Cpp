/*
 * DynamicData.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: rmin
 */

#include "DynamicData.h"

DynamicData::DynamicData(std::string id, Position position, std::string type,
		Json::Value other) {
	this->id = id;
	this->position = position;
	this->type= type;
	this->other = &other;
}

DynamicData::DynamicData(const DynamicData &source){
	id = source.getId();
	position = source.getPosition();
	type = source.getType();
	other = &source.getOther();
}


DynamicData::~DynamicData() {
}

void DynamicData::setPosition(Position position) {
	this->position = position;
}

void DynamicData::setId(std::string id) {
	this->id = id;
}

void DynamicData::setType(std::string type) {
	this->type = type;
}

void DynamicData::setOther(Json::Value& other) {
	this->other = &other;
}

std::string DynamicData::getId() const {
	return id;
}

Position DynamicData::getPosition() const {
	return position;
}

std::string DynamicData::getType() const {
	return type;
}

Json::Value& DynamicData::getOther() const {
	return *other;
}

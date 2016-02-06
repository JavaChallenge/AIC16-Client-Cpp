/*
 * TeamInfo.cpp
 *
 *  Created on: Feb 15, 2015
 *      Author: rmin
 */

#include "TeamInfo.h"

TeamInfo::TeamInfo(std::string name,int id) {
	// TODO Auto-generated constructor stub
	this->name = name;
	this->id = id;
}

TeamInfo::~TeamInfo() {
	// TODO Auto-generated destructor stub
}

std::string TeamInfo::getName()
{
	return name;
}

int TeamInfo::getId()
{
	return id;
}

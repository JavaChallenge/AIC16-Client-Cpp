/*
 * Event.cpp
 *
 *  Created on: Feb 14, 2015
 *      Author: rmin
 */

#include "Event.h"

Event::Event() {
	// TODO Auto-generated constructor stub

}

Event::Event(const Event& event)
{
	this->objectId = event.objectId;
	this->type = event.type;
	this->args = event.args;
}

Event::~Event() {
	// TODO Auto-generated destructor stub
}

std::string Event::getType()
{
	return type;
}

std::string Event::getObjectId()
{
	return objectId;
}

std::vector<std::string> Event::getArgs()
{
	return args;
}

/*
 * Event.h
 *
 *  Created on: Feb 14, 2015
 *      Author: rmin
 */

#ifndef EVENT_H_
#define EVENT_H_

#include <vector>
#include "Constants.h"
#include <string>

class Event {
protected:
	std::string type;
	std::string objectId;
	std::vector<std::string> args;
public:
	Event();
	Event(const Event& event);
	std::string getType();
	std::string getObjectId();
	std::vector<std::string> getArgs();
	virtual ~Event();
};

#endif /* EVENT_H_ */

/*
 * GameEvent.h
 *
 *  Created on: Feb 14, 2015
 *      Author: rmin
 */

#ifndef GAMEEVENT_H_
#define GAMEEVENT_H_

#include "Event.h"
#include <string>

class GameEvent: public Event {
private:
	int teamId;
public:
	GameEvent(Event event);
	GameEvent(std::string type);
	int getTeamId();
	void setTeamId(int teamId);
	void setObjectId(std::string objectId);
	void setArg(std::string value,int index);
	void addArg(std::string value);
	virtual ~GameEvent();
};
#endif /* GAMEEVENT_H_ */

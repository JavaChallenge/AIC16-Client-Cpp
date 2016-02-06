/*
 * Model.h
 *
 *  Created on: Feb 4, 2015
 *      Author: rmin
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "Message.h"
#include "Parser.h"
#include <ctime>
#include <vector>
#include "EventHandler.h"
#include "Map.h"
#include "ClientInitInfo.h"
#include "GameEvent.h"
#include "World.h"

class Model {
	long long turnTimeout;
	long long turnStartTime;
	World* world;
	EventHandler *eventHandler;
public:
	Model(EventHandler *eventHandler);
	virtual ~Model();
	void handleInitMessage(Message &msg);
	void handleTurnMessage(Message &msg);
	long long getTurnTimeout();
	long long getTurnTimePassed();
	long long getTurnRemainingTime();
	World* getWorld();
};

#endif /* MODEL_H_ */

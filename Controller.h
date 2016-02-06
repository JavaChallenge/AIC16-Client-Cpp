/*
 * Controller.h
 *
 *  Created on: Feb 3, 2015
 *      Author: rmin
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <ctime>

#include "Message.h"
#include "Network.h"
#include "AI.h"
#include "Game.h"
#include <fstream>
#include <string>
#include "EventHandler.h"

const long int MAX_TIME_FOR_DO_TURN = 400;

class Controller {
private:
	std::string token,ip;
	int port;
	EventHandler *eventHandler;
	AI* client;
	Game* game;
	Network* network;
	std::string settingsFile;
	time_t time;
	void handleTurnMessage(Message &msg);
	void handleInitMessage(Message &msg);
	Message getEvents();
	void doTurn();
	void run();
public:
	void handleMessage(Message &msg);
	Controller(std::string settingsFile);
	void start();
	void readClientData();
	bool getIsThreadCall();
	virtual ~Controller();
};

#endif /* CONTROLLER_H_ */

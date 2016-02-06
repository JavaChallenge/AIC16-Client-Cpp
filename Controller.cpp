/*
 * Controller.cpp
 *
 *  Created on: Feb 3, 2015
 *      Author: rmin
 */

#include "Controller.h"
#include <chrono>
#include <unistd.h>

#define TIMEOUT_FOR_TRY_TO_CONNECT 1000

Controller::Controller(std::string settingsFile) :
		settingsFile(settingsFile) {
	// TODO Auto-generated constructor stub
	time = 0;
	port = 0;
	eventHandler = NULL;
	model = NULL;
	network = NULL;
	client = NULL;
}

Controller::~Controller() {
	if (eventHandler != NULL)
		delete eventHandler;
	if (model != NULL)
		delete model;
	if (network != NULL)
		delete network;
	if (client != NULL)
		delete client;
	// TODO Auto-generated destructor stub
}

void Controller::start() {
	try {
		readClientData();
		network = new Network(this);
		network->setConnectionData(ip, port, token);
		eventHandler = new EventHandler(network);
		model = new Model(eventHandler);
		client = new AI();
		int counter = 0;
		while (counter < 10 && network != NULL && !network->getIsConnected()) {
			counter++;
			network->connect();
			if (network->getIsTerminated() == true)
				break;
			usleep(TIMEOUT_FOR_TRY_TO_CONNECT * 1000);
//			boost::this_thread::sleep_for(
//					boost::chrono::milliseconds(TIMEOUT_FOR_TRY_TO_CONNECT));
		}
		/*
		 * Connection Terminated
		 */

		delete eventHandler;
		delete model;
		delete client;
		delete network;
	} catch (const char* str) {
		std::cerr << str << std::endl;
	}
}

void Controller::readClientData() {
	std::ifstream fin(settingsFile.c_str());
	if (!fin.is_open()) {
		throw "Connection.conf doesn't exist";
	}
	std::string str;
	char tmp[1000];
	while (fin.getline(tmp, 1000)) {
		str.append(tmp);
	}
	Json::Value msg;
	Json::Reader reader;
	reader.parse(str, msg);
	token = msg["token"].asString();
	ip = msg["ip"].asString();
	port = msg["port"].asInt();
}

void Controller::handleMessage(Message &msg) {
	if (msg.getName() == Constants::MESSAGE_KEY_TURN) {
		handleTurnMessage(msg);
	} else if (msg.getName() == Constants::MESSAGE_KEY_INIT)
		handleInitMessage(msg);
	else if (msg.getName() == Constants::MESSAGE_KEY_SHUTDOWN
			|| msg.getName() == Constants::MESSAGE_KEY_WRONG_TOKEN) {
		network->terminate();
	}
}

void Controller::handleTurnMessage(Message &msg) {
	model->handleTurnMessage(msg);
	doTurn();
}

void Controller::handleInitMessage(Message &msg) {
	model->handleInitMessage(msg);
}

void Controller::run() {
	client->doTurn(model->getWorld());
}

void Controller::doTurn() {
	try {
		std::thread thr(&Controller::run);
		usleep(MAX_TIME_FOR_DO_TURN*1000);

//		boost::thread thr(boost::bind(&Controller::run, this));
//		boost::this_thread::sleep_for(
//				boost::chrono::milliseconds(MAX_TIME_FOR_DO_TURN));
		if (eventHandler->getIsThreadCall())
			eventHandler->getThr()->join();

	} catch (...) {
		std::cerr << "!!!\n";
	}
}

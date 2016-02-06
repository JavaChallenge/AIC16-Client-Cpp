/*
 * Model.cpp
 *
 *  Created on: Feb 4, 2015
 *      Author: rmin
 */

#include "Model.h"
#include <chrono>

Model::Model(EventHandler *eventHandler) {
	// TODO Auto-generated constructor stub
	this->eventHandler = eventHandler;
	turnStartTime = 0;
	turnTimeout = 400;
	world = NULL;
}

Model::~Model() {
	// TODO Auto-generated destructor stub
}

void Model::handleInitMessage(Message &msg) {
	Parser parser;

	Json::Value &argsArray = msg.getArray("args");

	Json::UInt I = 0;
	ClientInitInfo* initInfo = new ClientInitInfo();
	parser.parsClientInitInfo(argsArray[I], *initInfo);

	I = 1;
	std::vector<Json::Value> jsonValueArray;
	Json::Value& staticDataMessageArray = argsArray[I];
	for (int i = 0; i < (int) staticDataMessageArray.size(); i++) {
		jsonValueArray.push_back(staticDataMessageArray[i]);
	}

	Map *map = new Map(initInfo->getMapSize(), jsonValueArray);

	// TODO STATIC DIFF

	world = new World(eventHandler, initInfo, map);

	delete initInfo;
}

void Model::handleTurnMessage(Message &msg) {
	turnStartTime = time(0);

	Parser parser;

	Json::Value &argsArray = msg.getArray("args", true);

	Json::UInt I = 0;
	this->world->setTurn(argsArray[I].asInt());

	I = 1;
	Json::Value& staticsArray = argsArray[I]["statics"];
	Json::Value& dynamicsArray = argsArray[I]["dynamics"];
//	Json::Value& transientsArray = argsArray[I]["transients"];

	for (int i = 0; i < (int) staticsArray.size(); i++) {
		this->getWorld()->setStaticChange(staticsArray[i]);
	}

	for (int i = 0; i < (int) dynamicsArray.size(); i++) {
		world->setDynamicChange(dynamicsArray[i]);
	}

	//TODO Transients

}

long long Model::getTurnTimeout() {
	return turnTimeout;
}

long long Model::getTurnTimePassed() {
	return time(0) - turnStartTime;
}

long long Model::getTurnRemainingTime() {
	return turnTimeout - getTurnTimePassed();
}

World* Model::getWorld() {
	return world;
}

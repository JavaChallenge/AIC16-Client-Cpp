/*
 * Parser.h
 *
 *  Created on: Feb 15, 2015
 *      Author: rmin
 */

#ifndef PARSER_H_
#define PARSER_H_

#include "Message.h"
#include <vector>
#include "StaticData.h"
#include "Block.h"
#include "DynamicData.h"
#include "ClientInitInfo.h"
#include "GameEvent.h"

class Parser {
public:
	Parser();
	virtual ~Parser();
	void parsStaticData(Json::Value &msg,StaticData &staticData);
	void parsDynamicData(Json::Value &msg,DynamicData &dynamicData);
	void parsClientInitInfo(Json::Value &msg,ClientInitInfo &clientInitInfo);
	void generateEvent(Message &msg, GameEvent &event);
};

#endif /* PARSER_H_ */

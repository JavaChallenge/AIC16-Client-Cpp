/*
 * Parser.cpp
 *
 *  Created on: Feb 15, 2015
 *      Author: rmin
 */

#include "Parser.h"

Parser::Parser() {
	// TODO Auto-generated constructor stub

}

Parser::~Parser() {
	// TODO Auto-generated destructor stub
}

void Parser::parsStaticData(Json::Value &msg, StaticData &staticData) {
	staticData.setId(msg[Constants::GAME_OBJECT_KEY_ID].asString());

	staticData.setType(msg[Constants::GAME_OBJECT_KEY_TYPE].asString());

	staticData.setTurn(msg[Constants::GAME_OBJECT_KEY_TURN].asInt());

	staticData.setPosition(
			Position(
					msg[Constants::GAME_OBJECT_KEY_POSITION][Constants::POSITION_KEY_X].asInt(),
					msg[Constants::GAME_OBJECT_KEY_POSITION][Constants::POSITION_KEY_Y].asInt()));

	staticData.setOther(msg[Constants::GAME_OBJECT_KEY_OTHER]);
}

void Parser::parsDynamicData(Json::Value &msg, DynamicData &dynamicData) {
	dynamicData.setId(msg[Constants::GAME_OBJECT_KEY_ID].asString());

	dynamicData.setType(msg[Constants::GAME_OBJECT_KEY_TYPE].asString());

	dynamicData.setPosition(
			Position(
					msg[Constants::GAME_OBJECT_KEY_POSITION][Constants::POSITION_KEY_X].asInt(),
					msg[Constants::GAME_OBJECT_KEY_POSITION][Constants::POSITION_KEY_Y].asInt()));

	dynamicData.setOther(msg["other"]);
}

void Parser::parsClientInitInfo(Json::Value &msg,
		ClientInitInfo &clientInitInfo) {
	clientInitInfo.setTurn(msg[Constants::INFO_KEY_TURN].asInt());

	clientInitInfo.setBlockCoefficient(
			msg[Constants::INFO_KEY_HEIGHT_COEFFICIENT].asInt());

	Json::Value tmp = msg[Constants::INFO_KEY_TEAMS];

	for (int i = 0; i < (int) tmp.size(); i++) {
		clientInitInfo.addTeam(tmp[i].asString());
	}

	clientInitInfo.setYourInfo(
			TeamInfo(
					msg[Constants::INFO_KEY_YOUR_INFO][Constants::YOUR_INFO_KEY_NAME].asString(),
					msg[Constants::INFO_KEY_YOUR_INFO][Constants::YOUR_INFO_KEY_ID].asInt()));

	clientInitInfo.setMapSize(
			MapSize(
					msg[Constants::INFO_KEY_MAPSIZE][Constants::MAP_SIZE_KEY_WIDTH].asInt(),
					msg[Constants::INFO_KEY_MAPSIZE][Constants::MAP_SIZE_KEY_HEIGHT].asInt()));

}

void Parser::generateEvent(Message &msg, GameEvent &event) {
	msg.addNode(Constants::EVENT_KEY_TYPE, event.getType());
	msg.addNode(Constants::EVENT_KEY_OBJECT_ID, event.getObjectId());
	std::vector<std::string> args;
	for (int i = 0; i < (int) event.getArgs().size(); i++) {
		args.push_back(event.getArgs()[i]);
	}
	msg.addArray(Constants::MESSAGE_KEY_ARGS, args);
}

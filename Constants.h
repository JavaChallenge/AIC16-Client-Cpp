/*
 * Constants.h
 *
 *  Created on: Feb 16, 2015
 *      Author: rmin
 */

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#include <string>

class Constants {
public:
	static const std::string BLOCK_TYPE_NONE;
	static const std::string BLOCK_TYPE_NORMAL;
	static const std::string BLOCK_TYPE_MITOSIS;
	static const std::string BLOCK_TYPE_RESOURCE;
	static const std::string BLOCK_TYPE_IMPASSABLE;

	static const std::string BLOCK_KEY_TURN;
	static const std::string BLOCK_KEY_TYPE;
	static const std::string BLOCK_KEY_JUMP_IMP;
	static const std::string BLOCK_KEY_HEIGHT;
	static const std::string BLOCK_KEY_ATTACK_IMP;
	static const std::string BLOCK_KEY_RESOURCE;
	static const std::string BLOCK_KEY_MIN_HEIGHT;
	static const std::string BLOCK_KEY_DEPTH_OF_FIELD_IMP;
	static const std::string BLOCK_KEY_GAIN_RATE_IMP;

	static const int BLOCK_MAX_HEIGHT;
	static int BLOCK_HEIGHT_COEFFICIENT;

	static const std::string CELL_KEY_ENERGY;
	static const std::string CELL_KEY_JUMP;
	static const std::string CELL_KEY_ATTACK;
	static const std::string CELL_KEY_VISIBLE;
	static const std::string CELL_KEY_DEPTH_OF_FIELD;
	static const std::string CELL_KEY_GAIN_RATE;

	static const std::string GAME_OBJECT_TYPE_CELL;
	static const std::string GAME_OBJECT_TYPE_DESTROYED;

	static const std::string GAME_OBJECT_KEY_ID;
	static const std::string GAME_OBJECT_KEY_TURN;
	static const std::string GAME_OBJECT_KEY_TYPE;
	static const std::string GAME_OBJECT_KEY_OTHER;
	static const std::string GAME_OBJECT_KEY_TEAM_ID;
	static const std::string GAME_OBJECT_KEY_DURATION;
	static const std::string GAME_OBJECT_KEY_POSITION;

	static const std::string VIEW_GLOBAL;
	static const std::string VIEW;

	static const std::string YOUR_INFO_KEY_NAME;
	static const std::string YOUR_INFO_KEY_ID;

	static const std::string POSITION_KEY_X;
	static const std::string POSITION_KEY_Y;

	static const std::string MAP_SIZE_KEY_WIDTH;
	static const std::string MAP_SIZE_KEY_HEIGHT;

	static const std::string EVENT_KEY_TYPE;
	static const std::string EVENT_KEY_OBJECT_ID;

	static const std::string MESSAGE_KEY_NAME;
	static const std::string MESSAGE_KEY_ARGS;
	static const std::string MESSAGE_KEY_TURN;
	static const std::string MESSAGE_KEY_INIT;
	static const std::string MESSAGE_KEY_TOKEN;
	static const std::string MESSAGE_KEY_EVENT;
	static const std::string MESSAGE_KEY_SHUTDOWN;
	static const std::string MESSAGE_KEY_WRONG_TOKEN;

	static const std::string INFO_KEY_TURN;
	static const std::string INFO_KEY_INIT;
	static const std::string INFO_KEY_TEAMS;
	static const std::string INFO_KEY_VIEWS;
	static const std::string INFO_KEY_YOUR_INFO;
	static const std::string INFO_KEY_MAPSIZE;
	static const std::string INFO_KEY_HEIGHT_COEFFICIENT;

	static const int TURN_TEAM_VIEW_HISTORY_DEFAULT;
	static const int TURN_WORLD_CREATION;
	static const int TURN_MAKE_MAP;
	static const int TURN_INIT;

	static const int TEAM_ID_TERMINAL_ALTERNATIVE;
	static const int TEAM_ID_ENVIRONMENT_ALTERNATIVE;

	static const int CELL_MIN_ENERGY_FOR_MITOSIS;
	static const int CELL_MAX_ENERGY;

	static const int CELL_MAX_JUMP;
	static const int CELL_MAX_ATTACK;
	static const int CELL_MAX_GAIN_RATE;
	static const int CELL_MAX_DEPTH_OF_FIELD;

	static const std::string TYPE_MITOSIS;
	static const std::string TYPE_GAIN_RESOURCE;
	static const std::string TYPE_MOVE;
	static const std::string TYPE_ATTACK;

	static const int ARG_INDEX_MOVE_DIRECTION;
	static const int ARGS_NUMBER_MOVE;

	static const int ARG_INDEX_ATTACK_DIRECTION;
	static const int ARGS_NUMBER_ATTACK;

	static const std::string DirectionStr[6];

};

#endif /* CONSTANTS_H_ */

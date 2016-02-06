/*
 * Constants.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: rmin
 */

#include "Constants.h"

const std::string Constants::BLOCK_TYPE_NONE = "n";
const std::string Constants::BLOCK_TYPE_NORMAL = "o";
const std::string Constants::BLOCK_TYPE_MITOSIS = "m";
const std::string Constants::BLOCK_TYPE_RESOURCE = "r";
const std::string Constants::BLOCK_TYPE_IMPASSABLE = "i";

const std::string Constants::BLOCK_KEY_TURN = "t";
const std::string Constants::BLOCK_KEY_TYPE = "y";
const std::string Constants::BLOCK_KEY_JUMP_IMP = "j";
const std::string Constants::BLOCK_KEY_HEIGHT = "h";
const std::string Constants::BLOCK_KEY_ATTACK_IMP = "a";
const std::string Constants::BLOCK_KEY_RESOURCE = "r";
const std::string Constants::BLOCK_KEY_MIN_HEIGHT = "m";
const std::string Constants::BLOCK_KEY_DEPTH_OF_FIELD_IMP = "d";
const std::string Constants::BLOCK_KEY_GAIN_RATE_IMP = "g";

const int Constants::BLOCK_MAX_HEIGHT = 9;
int Constants::BLOCK_HEIGHT_COEFFICIENT = 50;

const std::string Constants::CELL_KEY_ENERGY = "e";
const std::string Constants::CELL_KEY_JUMP = "j";
const std::string Constants::CELL_KEY_ATTACK = "a";
const std::string Constants::CELL_KEY_VISIBLE = "v";
const std::string Constants::CELL_KEY_DEPTH_OF_FIELD = "d";
const std::string Constants::CELL_KEY_GAIN_RATE = "g";

const std::string Constants::GAME_OBJECT_TYPE_CELL = "c";
const std::string Constants::GAME_OBJECT_TYPE_DESTROYED = "d";

const std::string Constants::GAME_OBJECT_KEY_ID = "i";
const std::string Constants::GAME_OBJECT_KEY_TURN = "t";
const std::string Constants::GAME_OBJECT_KEY_TYPE = "y";
const std::string Constants::GAME_OBJECT_KEY_OTHER = "o";
const std::string Constants::GAME_OBJECT_KEY_TEAM_ID = "ti";
const std::string Constants::GAME_OBJECT_KEY_DURATION = "d";
const std::string Constants::GAME_OBJECT_KEY_POSITION = "p";

const std::string Constants::VIEW_GLOBAL = "global";
const std::string Constants::VIEW = "view";

const std::string Constants::YOUR_INFO_KEY_NAME = "name";
const std::string Constants::YOUR_INFO_KEY_ID = "id";

const std::string Constants::POSITION_KEY_X = "x";
const std::string Constants::POSITION_KEY_Y = "y";

const std::string Constants::MAP_SIZE_KEY_WIDTH = "width";
const std::string Constants::MAP_SIZE_KEY_HEIGHT = "height";

const std::string Constants::EVENT_KEY_TYPE = "type";
const std::string Constants::EVENT_KEY_OBJECT_ID = "objectId";

const std::string Constants::MESSAGE_KEY_NAME = "name";
const std::string Constants::MESSAGE_KEY_ARGS = "args";
const std::string Constants::MESSAGE_KEY_TURN = "turn";
const std::string Constants::MESSAGE_KEY_INIT = "init";
const std::string Constants::MESSAGE_KEY_TOKEN = "token";
const std::string Constants::MESSAGE_KEY_EVENT = "event";
const std::string Constants::MESSAGE_KEY_SHUTDOWN = "wrong token";
const std::string Constants::MESSAGE_KEY_WRONG_TOKEN = "shutdown";

const std::string Constants::INFO_KEY_TURN = "turn";
const std::string Constants::INFO_KEY_INIT = "init";
const std::string Constants::INFO_KEY_TEAMS = "teams";
const std::string Constants::INFO_KEY_VIEWS = "views";
const std::string Constants::INFO_KEY_YOUR_INFO = "yourInfo";
const std::string Constants::INFO_KEY_MAPSIZE = "mapSize";
const std::string Constants::INFO_KEY_HEIGHT_COEFFICIENT = "blockCoefficient";

const int Constants::TURN_TEAM_VIEW_HISTORY_DEFAULT = -10;
const int Constants::TURN_WORLD_CREATION = -3;
const int Constants::TURN_MAKE_MAP = -2;
const int Constants::TURN_INIT = -1;

const int Constants::TEAM_ID_TERMINAL_ALTERNATIVE = -2;
const int Constants::TEAM_ID_ENVIRONMENT_ALTERNATIVE = -1;

const int Constants::CELL_MIN_ENERGY_FOR_MITOSIS = 80;
const int Constants::CELL_MAX_ENERGY = 100;

const int Constants::CELL_MAX_JUMP = 5;
const int Constants::CELL_MAX_ATTACK = 35;
const int Constants::CELL_MAX_GAIN_RATE = 45;
const int Constants::CELL_MAX_DEPTH_OF_FIELD = 5;

const std::string Constants::TYPE_MITOSIS = "mitosis";
const std::string Constants::TYPE_GAIN_RESOURCE = "gainResource";
const std::string Constants::TYPE_MOVE = "move";
const std::string Constants::TYPE_ATTACK = "attack";

const int Constants::ARG_INDEX_MOVE_DIRECTION = 0;
const int Constants::ARGS_NUMBER_MOVE = 1;

const int Constants::ARG_INDEX_ATTACK_DIRECTION = 0;
const int Constants::ARGS_NUMBER_ATTACK = 1;

const std::string Constants::DirectionStr[6] = { "NORTH", "SOUTH", "NORTH_EAST",
		"NORTH_WEST", "SOUTH_EAST", "SOUTH_WEST" };

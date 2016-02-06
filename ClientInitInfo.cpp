/*
 * ClientInitInfo.cpp
 *
 *  Created on: Feb 15, 2015
 *      Author: rmin
 */

#include "ClientInitInfo.h"

ClientInitInfo::ClientInitInfo() {
	// TODO Auto-generated constructor stub
	turn = 0;
	blockCoefficient = 0;
}

ClientInitInfo::~ClientInitInfo() {
	// TODO Auto-generated destructor stub
}

void ClientInitInfo::setBlockCoefficient(int blockCoefficient) {
	this->blockCoefficient = blockCoefficient;
}

void ClientInitInfo::setTurn(int turn) {
	this->turn = turn;
}

void ClientInitInfo::addTeam(std::string team)
{
	teams.push_back(team);
}

void ClientInitInfo::setTeams(std::vector<std::string>& teams) {
	this->teams = teams;
}

void ClientInitInfo::setYourInfo(TeamInfo yourInfo) {
	this->yourInfo = yourInfo;
}

void ClientInitInfo::setMapSize(MapSize mapSize) {
	this->mapSize = mapSize;
}

int ClientInitInfo::getTurn() {
	return turn;
}

std::vector<std::string>& ClientInitInfo::getTeams() {
	return teams;
}

TeamInfo& ClientInitInfo::getYourInfo() {
	return yourInfo;
}

MapSize& ClientInitInfo::getMapSize() {
	return mapSize;
}

int ClientInitInfo::getBlockCoefficient() {
	return blockCoefficient;
}

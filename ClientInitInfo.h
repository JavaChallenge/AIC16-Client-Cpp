/*
 * ClientInitInfo.h
 *
 *  Created on: Feb 15, 2015
 *      Author: rmin
 */

#ifndef CLIENTINITINFO_H_
#define CLIENTINITINFO_H_

#include <vector>
#include "MapSize.h"
#include "TeamInfo.h"
#include <string>

class ClientInitInfo {
private:
	int turn;
	int blockCoefficient;
	std::vector<std::string> teams;
	TeamInfo yourInfo;
	MapSize mapSize;
public:
	ClientInitInfo();
	virtual ~ClientInitInfo();
	void setTurn(int turn);
	void setTeams(std::vector<std::string>& teams);
	void setYourInfo(TeamInfo yourInfo);
	void setMapSize(MapSize mapSize);
	void setBlockCoefficient(int blockCoefficient);
	void addTeam(std::string team);
	int getTurn();
	std::vector<std::string>& getTeams();
	TeamInfo& getYourInfo();
	MapSize& getMapSize();
	int getBlockCoefficient();
};

#endif /* CLIENTINITINFO_H_ */

/*
 * TeamInfo.h
 *
 *  Created on: Feb 15, 2015
 *      Author: rmin
 */

#ifndef TEAMINFO_H_
#define TEAMINFO_H_

#include <string>

class TeamInfo {
private:
	std::string name;
	int id;
public:
	TeamInfo(std::string name = "0",int id = 0);
	virtual ~TeamInfo();
	std::string getName();
	int getId();
};

#endif /* TEAMINFO_H_ */

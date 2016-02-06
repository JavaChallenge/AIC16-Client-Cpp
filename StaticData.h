/*
 * StaticData.h
 *
 *  Created on: Feb 14, 2015
 *      Author: rmin
 */

#ifndef STATICDATA_H_
#define STATICDATA_H_

#include "Position.h"
#include "Constants.h"
#include "Message.h"
#include <string>

class StaticData {
protected:
	std::string id, type;
	int turn;
	Position position;
	Json::Value *other;
public:
	StaticData();
	StaticData(const StaticData &source);
	StaticData(std::string id, int turn,
			Position position, std::string type,
			Json::Value &other);
	virtual ~StaticData();
	void setId(std::string id);
	void setType(std::string type);
	void setTurn(int turn);
	void setPosition(Position position);
	void setOther(Json::Value& other);
	std::string getType() const;
	std::string getId() const;
	int getTurn() const;
	Position getPosition() const;
	Json::Value& getOther() const;
};

#endif /* STATICDATA_H_ */

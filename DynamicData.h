/*
 * DynamicData.h
 *
 *  Created on: Feb 16, 2015
 *      Author: rmin
 */

#ifndef DYNAMICDATA_H_
#define DYNAMICDATA_H_

#include "Position.h"
#include "Message.h"

class DynamicData {
protected:
	std::string id;
	Position position;
	std::string type;
	Json::Value *other;
public:
	DynamicData(const DynamicData &source);
	DynamicData(std::string id = "", Position position = Position(0, 0),
			std::string type = "", Json::Value other = Json::Value(0));
	virtual ~DynamicData();
	void setPosition(Position position);
	void setOther(Json::Value& other);
	void setId(std::string id);
	void setType(std::string type);
	std::string getId() const;
	Position getPosition() const;
	std::string getType() const;
	Json::Value& getOther() const;
};

#endif /* DYNAMICDATA_H_ */

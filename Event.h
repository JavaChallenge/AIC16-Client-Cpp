#ifndef _EVENT_H
#define _EVENT_H

#include <vector>
#include <string>

/**
 * Event class.
 */

class Event
{
public:
	static const std::string EVENT = "event";

	Event(std::string type, std::vector<std::string> args);

    std::string getType();
    const std::vector<std::string>& getArgs();

protected:
	/** The type of the Event **/
    std::string type;			
    /** Arguments of the Event **/
    std::vector<std::string> args;
};

#endif _EVENT_H

#include "Event.h"

Event::Event(std::string type, std::vector<std::string> args)
{
	this->type = type;
	this->args = args;
}

std::string Event::getType()
{
	return type;
}

const std::vector<std::string>& Event::getArgs()
{
    return args;
}

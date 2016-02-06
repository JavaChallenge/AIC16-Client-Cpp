#include "Event.h"

Event::Event(std::string type, std::vector<Object*> args)
{
	this->type = type;
	this->args = args;
}

std::string Event::getType()
{
	return type;
}

std::vector<Object*> Event::getArgs()
{
    return args;
}
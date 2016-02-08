/*
 * EventHandler.cpp
 *
 *  Created on: Feb 16, 2015
 *      Author: rmin
 */

#include "EventHandler.h"
#include "Parser.h"
#include <chrono>
#include <future>

EventHandler::EventHandler(Network *network)
{
	this->network = network;
	isThreadCall = false;
	thr = NULL;
}

bool EventHandler::getIsThreadCall()
{
	return isThreadCall;
}

std::thread * EventHandler::getThr()
{
	return thr;
}

EventHandler::~EventHandler()
{
}

void EventHandler::handling()
{
	std::cerr << "handling function called\n";
	while (events.getSize() != 0)
	{
		handleEvent(events.pop());
	}
	std::cerr << "trying to delete thr\n";
	std::cerr << "EEEEEEEEEEE :            " << (int*)(thr) << std::endl;
	if(thr != NULL) {
//		thr->join();
		std::cerr << "thr joined\n";
//		delete thr;
	}
	std::cerr << "delete thr correctly\n";
	isThreadCall = false;
	std::cerr << "handling function end\n";
}

void EventHandler::addEvent(GameEvent* event) {
	std::cerr << "Event::addEvent Called" << std::endl;
	events.push(event);
	if (!isThreadCall) {
		isThreadCall = true;
		thr = new std::thread(&EventHandler::handling,this);
		std::cerr << "TTTTTTTTTT :            " << (int*)(thr) << std::endl;
	}
	std::cerr << "Event::addEvent End" << std::endl;
}

void EventHandler::handleEvent(GameEvent *eve)
{
	std::cerr << "EventHandler::handleEvent Called" << std::endl;
	Message result, event;
	result.addNode(Constants::MESSAGE_KEY_NAME, Constants::MESSAGE_KEY_EVENT);
	parser.generateEvent(event, *eve);
	std::vector<Message> eventsJson;
	eventsJson.push_back(event);
	result.addArray(Constants::MESSAGE_KEY_ARGS, eventsJson);
	network->sendMessage(result);
	delete eve;
	std::cerr << "EventHandler::handleEvent End" << std::endl;
}

EventHandler* eventHandler;

#include "Game.h"
#include <ctime>
#include "util.h"

Game::Game()
{
	turnStartTime = -1;
	map = NULL;
}

Game::~Game()
{
	if(map != NULL)
		delete map;
}

void Game::handleInitMessage(Message msg)
{
	Json::Value &argsArray = msg.getArray("args");

	Json::UInt I=0;
	this->turnTimeout = argsArray[I++].asInt();

	this->myID = argsArray[I++].asInt();

	// graph deserialization
	Json::Value &adjListInt = argsArray[I++];

	std::vector<Node*> nodes;
	for (int i = 0; i < (int)adjListInt.size(); i++)
	{
		nodes.push_back(new Node(i));
	}

	for (int i = 0; i < (int)adjListInt.size(); i++)
	{
		Json::Value &neighboursInt = adjListInt[i];
		std::vector<Node*> neighbours;
		for (int j = 0; j < (int)neighboursInt.size(); j++)
		{
			neighbours.push_back(nodes[neighboursInt[j].asInt()]);
		}
		nodes[i]->setNeighbours(neighbours);
	}

	Json::Value &graphDiff = argsArray[I++];
	for (int i = 0; i < (int)graphDiff.size(); i++)
	{
		Json::Value &nodeDiff = graphDiff[i];
		int node = nodeDiff[(Json::UInt)0].asInt();
		int owner = nodeDiff[1].asInt();
		int armyCount = nodeDiff[2].asInt();
		nodes[node]->setOwner(owner);
		nodes[node]->setArmyCount(armyCount);
	}

	map = new Graph(nodes);

	updateNodesList();
}

void Game::handleTurnMessage(Message msg)
{
	turnStartTime = time(0);

	Json::Value &argsArray = msg.getArray("args");
	Json::UInt I=0;
	turn = argsArray[I++].asInt(); /** EDITED BY MEHRAN : USED TO BE ++I **/

	Json::Value &graphDiff = argsArray[I++];
	for (int i = 0; i < (int)graphDiff.size(); i++)
	{
		Json::Value &nodeDiff = graphDiff[i];
		Json::UInt J=0;
		int nodeIndex = nodeDiff[J++].asInt(); /** EDITED BY MEHRAN : USED TO BE ++J **/
		map->getNode(nodeIndex)->setOwner(nodeDiff[J++].asInt());
		map->getNode(nodeIndex)->setArmyCount(nodeDiff[J++].asInt());
	}

	updateNodesList();
}

void Game::updateNodesList()
{
	for(int i = 0; i < 3; i++)
		this->nodes[i].clear();
	for (Node* n : this->map->getNodes())
	{
		nodes[n->getOwner() + 1].push_back(n);
	}
}

long long Game::getTurnTimePassed() {
	return time(0) - turnStartTime;
}

long long Game::getTurnRemainingTime() {
	return turnTimeout - getTurnTimePassed();
}

int Game::getMyId() {
	return myID;
}

Graph* Game::getMap() {
	return map;
}

std::vector<Node*>& Game::getMyNodes() {
	return this->nodes[this->myID + 1];
}

std::vector<Node*>& Game::getOpponentNodes() {
	return this->nodes[2 - this->myID];
}

std::vector<Node*>& Game::getFreeNodes() {
	return this->nodes[0];
}

int Game::getTurnNumber() {
	return this->turn;
}

long long Game::getTotalTurnTime() {
	return this->turnTimeout;
}

void Game::moveArmy(Node* src, Node* dst, int count)
{
	this->moveArmy(src->getIndex(), dst->getIndex(), count);
}

void Game::moveArmy(int src, int dst, int count)
{
	GameEvent* gameEvent = new GameEvent(Constants::TYPE_MOVE);
	gameEvent->addArg(src);
	gameEvent->addArg(dst);
	gameEvent->addArg(count);
	eventHandler->addEvent(gameEvent);
}

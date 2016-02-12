#include "AI.h"

#include <vector>
#include <cstdlib>
#include <iostream>

#define MAXN 100

void escape(World *world, Node* node) {
}

bool hasBadNeighbour(Node* source, int owner) {
	for(auto &neighbour : source->getNeighbours()) {
		if(neighbour->getArmyCount() > 0 && owner != neighbour->getOwner())
			return true;
	}
	return false;
}

void AI::doTurn(World *world)
{
	/** Fill this method. We've presented a stupid AI as an example! **/
	srand(time(NULL));
	std::vector<Node*>& myNodes = world->getMyNodes();
	std::vector<Node*> myBadNodes, myGoodNodes;
	std::vector<Node*> escapeEnemyNeighbours[MAXN], goodEnemyNeighbours[MAXN];
	for(auto& source : world->getMap()->getNodes())
	{
//		source->setHasBadNeighbour(false);
		/** Get neighbours **/
		for(auto &neighbour : source->getNeighbours()) {
			if(neighbour->getOwner() != -1  && neighbour->getOwner() != world->getMyId()) { // enemy node
				if(neighbour->getArmyCount() == 2 && world->getMediumArmyBound() > source->getArmyCount()) { // heavy neighbour
					escapeEnemyNeighbours[source->getIndex()].push_back(neighbour);
					myBadNodes.push_back(source);
//					source->setHasBadNeighbour(true);
				}
				else if(neighbour->getArmyCount() == 1 && world->getLowArmyBound() > source->getArmyCount()) {
					escapeEnemyNeighbours[source->getIndex()].push_back(neighbour);
					myBadNodes.push_back(source);
//					source->setHasBadNeighbour(true);
				}
				else {
					goodEnemyNeighbours[source->getIndex()].push_back(neighbour);
					myGoodNodes.push_back(source);
				}
			}
		}
	}
	for(auto &source : myNodes) {
		if(!escapeEnemyNeighbours[source->getIndex()].empty()) { // has bad enemy
			for(auto &neighbour : source->getNeighbours()) {
				if((neighbour->getOwner() == 0 && !hasBadNeighbour(neighbour,neighbour->getOwner())) ||
						(neighbour->getOwner() == source->getOwner() && !hasBadNeighbour(neighbour, neighbour->getOwner())))
				world->moveArmy(source,neighbour,source->getArmyCount());
				break;
			}
		}
		else {
			if(!goodEnemyNeighbours[source->getIndex()].empty()) { // have good enemy
				world->moveArmy(source, goodEnemyNeighbours[source->getIndex()][rand()%goodEnemyNeighbours[source->getIndex()].size()], source->getArmyCount()/2);
			}
			else {
				world->moveArmy(source,source->getNeighbours()[rand()%source->getNeighbours().size()],source->getArmyCount()/2);
			}
		}
	}
}

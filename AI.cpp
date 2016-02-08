#include "AI.h"

#include <vector>
#include <cstdlib>
#include <iostream>

void AI::doTurn(World *world)
{
	/** Fill this method. We've presented a stupid AI as an example! **/

	std::cerr << "AI::doTurn called\n";
	std::vector<Node*>& myNodes = world->getMyNodes();
	std::cerr << myNodes.size() << std::endl;
	for(auto& source : myNodes)
	{
		std::cerr << source->getIndex() << std::endl;
		/** Get neighbours **/
		const std::vector<Node*>& neighbours = source->getNeighbours();
		std::cerr << "!!!! " << neighbours.size() << std::endl;
		if (neighbours.size() > 0)
		{
			/** Select a random neighbour **/
			Node *destination = neighbours[(int)(rand() % neighbours.size())];
			/** Move half of the nodes army to the neighbour node **/
			world->moveArmy(source, destination, source->getArmyCount() / 2);
		}
	}
	std::cerr << "AI:doTurn function end correctly\n";
}

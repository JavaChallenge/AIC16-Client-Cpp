#include "AI.h"

#include <vector>

void AI::doTurn(World *world)
{
	/** Fill this method. We've presented a stupid AI as an example! **/

	std::vector<Node*> myNodes = world->getMyNodes();
	for(auto & source : myNodes)
	{
		/** Get neighbours **/
		std::vector<Node*> neighbours = source->getNeighbours();
		if (neighbours.size() > 0)
		{
			/** Select a random neighbour **/
			Node *destination = neighbours[(int)(neighbours.size() * rand())];
			/** Move half of the nodes army to the neighbour node **/
			world->moveArmy(source, destination, source->getArmyCount() / 2);
		}
	}
}

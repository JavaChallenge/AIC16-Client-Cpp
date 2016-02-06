/*
 * AI.cpp
 *
 *  Created on: Feb 4, 2015
 *      Author: rmin
 */

#include "AI.h"
#include <cstdlib>
#include <ctime>

AI::AI() {
	// TODO Auto-generated constructor stub
}

void AI::doTurn(World *world) {
	srand(time(NULL));
	for (int i = 0; i < (int) world->getMyCells().size(); i++) {
		Cell *c = world->getMyCells()[i];
		bool attack = false;
		for (int dir = 0; dir < 6; dir++) {
			Position nextPos = c->getPos().getNextPos(
					static_cast<Direction>(dir));
			for (int j = 0; j < (int) world->getEnemyCells().size(); j++) {
				if (world->getEnemyCells()[j]->getPos() == nextPos) {
					c->attack(static_cast<Direction>(dir));
					attack = true;
					break;
				}
			}
			if (attack)
				break;
		}

		if (attack)
			continue;

		Block *block = world->getMap()->at(c->getPos());
		if (c->getEnergy() >= Constants::CELL_MIN_ENERGY_FOR_MITOSIS
				&& block->getType() == Constants::BLOCK_TYPE_MITOSIS)
		{
			c->mitosis();
		}
		else if (c->getEnergy() < Constants::CELL_MAX_ENERGY
				&& block->getResource() > 0)
			c->gainResource();
		else {
			Direction direction = static_cast<Direction>(rand() % 6);
			c->move(direction);
		}
	}
	// you should fill this method
}

AI::~AI() {
	// TODO Auto-generated destructor stub
}


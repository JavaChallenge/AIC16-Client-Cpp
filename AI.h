/*
 * AI.h
 *
 *  Created on: Feb 4, 2015
 *      Author: rmin
 */

#ifndef AI_H_
#define AI_H_

#include "World.h"
#include "Constants.h"

class AI {
public:
	AI();
	virtual ~AI();
	void doTurn(World *world);
};

#endif /* AI_H_ */

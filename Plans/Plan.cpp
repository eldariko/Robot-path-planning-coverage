/*
 * Plan.cpp
 *
 *  Created on: Dec 21, 2014
 *      Author: user
 */

#include "Plan.h"
#include "../Behaviors/Behavior.h"

Plan::Plan(Robot* robot) {
	 _robot = robot;
}

Plan::~Plan() {
	// TODO Auto-generated destructor stub
}

Behavior* Plan::getStartPoint(){
	return _start;
}

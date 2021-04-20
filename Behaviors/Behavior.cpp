/*
 * Behavior.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: user
 */

#include "Behavior.h"

Behavior::Behavior(Robot* robot) {

	_robot = robot;
	_nextBehavior = NULL;
	_behaviorsCount = 0;
}

Behavior* Behavior::addNextBehavior(Behavior* behavior){

	Behavior** tempBeh = new Behavior*[_behaviorsCount + 1];

	if (!tempBeh) {
		return NULL;
	}

	int i;
	for (i = 0; i < _behaviorsCount; ++i) {
		tempBeh[i] = _nextBehavior[i];
	}

	tempBeh[i] = behavior;
	delete [] _nextBehavior;
	_behaviorsCount++;

	_nextBehavior = tempBeh;
	return this;
}

Behavior* Behavior::selectNextBehavior(){

	int i;
	for(i=0; i<_behaviorsCount; i++)
		if(_nextBehavior[i]->startCond())
			return _nextBehavior[i];

	return NULL;
}

Behavior::~Behavior() {

	delete [] _nextBehavior;
	delete _robot;
}

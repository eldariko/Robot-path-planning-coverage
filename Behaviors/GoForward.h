/*
 * GoForward.h
 *
 *  Created on: Jun 14, 2015
 *      Author: user
 */

#ifndef GOFORWARD_H_
#define GOFORWARD_H_

#include "Behavior.h"
#include "../Robot/Robot.h"
#include "../Managers/WaypointsManager.h"

class GoForward: public Behavior {

public:

	GoForward(Robot* robot,  WaypointsManager* Wpm);
	bool startCond();
	bool stopCond();
	void action();
	void print();
	virtual ~GoForward();

private:
	WaypointsManager* _wpm;

};

#endif /* GOFORWARD_H_ */

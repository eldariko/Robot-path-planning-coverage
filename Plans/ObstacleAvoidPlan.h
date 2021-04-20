/*
 * ObstacleAvoidPlan.h
 *
 *  Created on: Jun 21, 2015
 *      Author: user
 */

#ifndef OBSTACLEAVOIDPLAN_H_
#define OBSTACLEAVOIDPLAN_H_

#include "Plan.h"
#include "../Managers/WaypointsManager.h"

class ObstacleAvoidPlan: public Plan {

public:
	ObstacleAvoidPlan(Robot* robot,WaypointsManager* wpm);
	Behavior* getStartPoint();
	virtual ~ObstacleAvoidPlan();
};

#endif /* OBSTACLEAVOIDPLAN_H_ */



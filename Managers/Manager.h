/*
 * Manager.h
 *
 *  Created on: Jun 21, 2015
 *      Author: user
 */

#ifndef MANAGER_H_
#define MANAGER_H_
#include "../Plans/ObstacleAvoidPlan.h"
#include "../Robot/Robot.h"
#include "LocalizationManager.h"
#include "WaypointsManager.h"

class Manager {
	Behavior* _curr;
	Robot* _robot;
	LocalizationManager* _localization_manager;
	ConfigurationManager* _cm;
	WaypointsManager* _wayPointsManager;
public:
	Manager(Robot* robot, Plan* pln, LocalizationManager* manager,
			ConfigurationManager* cm, WaypointsManager* wayPointsManager);
	void run();
	virtual ~Manager();
};

#endif /* MANAGER_H_ */

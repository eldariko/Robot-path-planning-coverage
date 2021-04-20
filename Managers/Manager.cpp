/*
 * Manager.cpp
 *
 *  Created on: Jun 21, 2015
 *      Author: user
 */

#include "Manager.h"

Manager::Manager(Robot* robot, Plan* pln, LocalizationManager* l_manager, ConfigurationManager* cm, WaypointsManager* wayPointsManager) {
	_robot = robot;
	_wayPointsManager = wayPointsManager;
	_localization_manager = NULL;
	_cm = cm;

	_curr = pln->getStartPoint();
}
void Manager::run()
{
	wayPoint wp;
	vector<wayPoint*>::iterator it;

	// Reading data from robot
	_robot->Read();

	// Got through all waypoints
	for (it = (_wayPointsManager->wayPoints).begin(); it != (_wayPointsManager->wayPoints).end(); ++it) {
		wp = **it;
		cout<<"-----------------------------"<<endl;
		cout <<"RUN (row)"<< wp.x_Coordinate << " (col)" << wp.y_Coordinate << " " << wp.yaw << endl;
		_robot->Read();



		_wayPointsManager->setNextWayPoint(wp);
		if(_curr != NULL){
			_curr->startCond();
		}
		else {
			cout<<"Nullll"<<endl;
		    break;
		}

		// While we haven't got to the needed way point keep moving there
		while (true){

			// If the current behavior can't run, execute the next behavior
			if(_curr->stopCond())
			{
				// Perform the next behavior according to the plan
				_curr = _curr->selectNextBehavior();
				_robot->Read();
				// if we hit the way point break, and go on to the next way point
				if (_wayPointsManager->isInWayPoint(_robot->getYpos(),_robot->getXpos()) ||
						(dynamic_cast<GoForward*>(_curr) != NULL && _wayPointsManager->inWayPoint)) {
					//_robot->setSpeed(0.1,0);
					cout << "in way point !!!!" << endl;
					break;
				}
				if (!_curr){
              	//_robot->setSpeed(0,0);
              	break;
				}
//				  if(dynamic_cast<GoForward*>(_curr) != NULL && _wayPointsManager->inWayPoint)
//		        {
//					  _robot->setSpeed(0.0,0);
//					 // cout<<"in way point !!!!"<<endl;
//	    	    }
//				  _robot->Read();

			}
			     // Do the current behavior's action
			    _curr->action();
			    _robot->Read();
		}

	}
}

Manager::~Manager() {
	// TODO Auto-generated destructor stub
}

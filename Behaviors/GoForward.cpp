/*
 * GoForward.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: user
 */

#include "GoForward.h"
#include <iostream>
#include <math.h>
#include "../Defines.h"

GoForward::GoForward(Robot* robot, WaypointsManager* wpm):Behavior(robot) {
	_wpm = wpm;
}

bool GoForward::startCond()
{
//    bool result=(_robot->checkRange(_robot->getLaserSpec() / 2 - LASER_SPEC, _robot->getLaserSpec() / 2 + LASER_SPEC));
    bool result=(_robot->isForwardFree());
    if(result){
		cout<<"start go forward"<<endl;
		return result;
	}else {cout<<"Laser too close !"<<endl;return result;}
	}

bool GoForward::stopCond()
{

	_robot->Read();
//	bool result=(!startCond() || (_wpm->isInWayPoint(_robot->getYpos(), _robot->getXpos())));
	bool result=((_wpm->isInWayPoint(_robot->getYpos(), _robot->getXpos())));

	if (result){
		cout<<"stop go forward(from stop cond)"<<endl;
		return result;
    }else return result;
}
void GoForward::action()
{
	cout<<"action go forward"<<endl;
	_robot->setSpeed(0.5, 0.0);
//	MOVE_SPEED
}

GoForward::~GoForward() {
	// TODO Auto-generated destructor stub
}

void GoForward::print()
{

}

/*
 * GoToWayPoint.cpp
 *
 *  Created on: Jun 20, 2015
 *      Author: colman
 */

#include "GoToWayPoint.h"

GoToWayPoint::GoToWayPoint(Robot* robot, WaypointsManager* wpm):Behavior(robot) {
	isRight=0;
	diffrence=0;
	_wpm = wpm;
}

GoToWayPoint::~GoToWayPoint() {
	// TODO Auto-generated destructor stub
}

// here we set if the robot should move right or left towards the nearest waypoint
bool GoToWayPoint::startCond()
{

//		int yaw = _robot->getYaw();
//		diffrence = _wpm->currWayPoint.yaw - yaw;
//
//		if(diffrence == 0)
//		{
//			return false;
//		}
//		else if(diffrence >= 180)
//			{
//				isRight =  1;
//				diffrence = 360 - diffrence;
//			}
	double yaw = _robot->getYaw();
	diffrence = _wpm->currWayPoint.yaw - yaw;

	if(diffrence == 0)
	{
		isRight=0;
		return false;
	}
	else if(diffrence >= 180)
	{
		isRight =  1;
		diffrence = 360 - diffrence;
	}
	else if (diffrence < -180)
	{
		isRight = 0;
		diffrence = 360 + diffrence;
	}
	else if (diffrence > 0)
	{
		isRight = 0;
	}
	else
	{
		isRight = 1;
		diffrence = abs(diffrence);
	}

	bool result;
	if(isRight)
	{
//		result=(_robot->checkRange(0, diffrence * ONE_DEGREE_INDEXES));
		result=_robot->isRightFree();
		if(result){
			cout<<"start go to way point"<<endl;
			return result;
		}else {cout<<"right not free"<<endl;return result;}
	}
	else
	{
//		result=(_robot->checkRange( _robot->getLaserSpec() - (diffrence * ONE_DEGREE_INDEXES),_robot->getLaserSpec()));
		result=_robot->isLeftFree();
		if(result){
		cout<<"start go to way point"<<endl;
		return result;
		}else {cout<<"left not free"<<endl;return result;}
	}
}
bool GoToWayPoint::stopCond()
{
	double yaw=_robot->getYaw();
	cout<<yaw<<","<<_wpm->currWayPoint.yaw<<endl;
	double d=((yaw) - (_wpm->currWayPoint.yaw));
	//bool result=(!(_robot->checkRange(0, diffrence * ONE_DEGREE_INDEXES)) || (abs(d)<= MAX_YAW_DIFF));
	bool result;
	if(isRight)
	{

		if((result=(!(_robot->isRightFree())))){
//		if((result=!(_robot->checkRange(0, diffrence * ONE_DEGREE_INDEXES)))){
			cout<<"stop go to way point"<<endl;
			cout<<"range to close"<<endl;
		return result;
		}
		if((result=(abs(d)<= MAX_YAW_DIFF)))
		{
		   cout<<"stop go to way point"<<endl;
           cout<<"yaw match(Right)"<<endl;
           return result;
		}
		return result;
//		bool result=(!(_robot->isRightFree()) || (abs(d)<= MAX_YAW_DIFF));
//		if(result){
//			cout<<"stop go to way point"<<endl;
//			return result;
//		}else return result;
//		return ((abs(d)<= MAX_YAW_DIFF));

	}
	else
	{

		//bool result=(!(_robot->isLeftFree()) || (abs(d)<= MAX_YAW_DIFF));
		//bool result=(!(_robot->checkRange(0, diffrence * ONE_DEGREE_INDEXES)) || (abs(d)<= MAX_YAW_DIFF));
		if((result=(!(_robot->isLeftFree())))){
//        if((result=!(_robot->checkRange( _robot->getLaserSpec()-(diffrence * ONE_DEGREE_INDEXES),_robot->getLaserSpec())))){
			cout<<"stop go to way point"<<endl;
			cout<<"range to close"<<endl;
		return result;
		}
		if((result=(abs(d)<= MAX_YAW_DIFF)))
		{
			cout<<"stop go to way point"<<endl;
	        cout<<"yaw match(Left)"<<endl;
	        return result;
		}
		return result;
//		if(result){
//			cout<<"stop go to way point"<<endl;
//			return result;
//		}else return result;
//		return(abs(d)<= MAX_YAW_DIFF);

	}

}
void GoToWayPoint::action()
{
	//cout<<"action go to way point"<<endl;
	cout<<"Turning .."<<endl;
	float angSpeed;
	if(abs((_robot->getYaw()) - (_wpm->currWayPoint.yaw))<=15)
	 angSpeed=0.04;
	else angSpeed=0.5;
	if(isRight)
	{
		_robot->setSpeed(0.0, -angSpeed);
	}
	else
	{
		_robot->setSpeed(0.0, angSpeed);
	}
}

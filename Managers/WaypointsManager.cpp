/*
 * WaypointsManager.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: colman
 */

#include "WaypointsManager.h"
#include <math.h>
#include <stdlib.h>

using namespace std;

WaypointsManager::WaypointsManager(vector<Node*> path, double gridResolution, double mapResolution)
{
	this->wayPointArrayIndex = 0;
	is_verticle=false;
	stc_path = path;
	_gridResolution = gridResolution;
	_mapResolution = mapResolution;
	this->endOfArray=false;
	inWayPoint=false;
	nextWayPoint.x_Coordinate=25;
	nextWayPoint.y_Coordinate=30;
 	nextWayPoint.yaw=90;

}

void WaypointsManager::buildWayPointVector(vector<Node *> path)
{
	int fineColCurrent=0;
		int fineRowCurrent=0;
		int fineColNext=0;
		int fineRowNext=0;

		int coarseColCurrent = 0;
		int coarseRowCurrent = 0;
		int coarseColNext = 0;
		int coarseRowNext = 0;

		char direction;
		int count=0;

		for (unsigned int i = 0; i < path.size()-1; ++i) {

			coarseColCurrent = path[i]->col;
			coarseRowCurrent = path[i]->row;

			coarseColNext = path[i+1]->col;
			coarseRowNext = path[i+1]->row;



			//If there is no neighbors , create a U turn based on the last move
			count =0;
			for(int j=0; j < 4; j++){
				if(path[i]->neighborsInSpanningTree[j] != NULL){
					++count;
					break;
				}
			}

			if(count == 0){

				if(direction == 'U'){
					//cout<<"up "<<coarseRowCurrent*2<< coarseColCurrent*2<<" "<<coarseRowCurrent*2<< coarseColCurrent*2+1 <<endl;

					wayPoints.push_back(new wayPoint(coarseRowCurrent*2, coarseColCurrent*2));
					wayPoints.push_back(new wayPoint(coarseRowCurrent*2, coarseColCurrent*2+1));

				}

				if(direction == 'D'){
					//cout<<"Down "<< coarseRowCurrent*2+1<< coarseColCurrent*2+1<<" "<<coarseRowCurrent*2+1<< coarseColCurrent*2<<endl;

					wayPoints.push_back(new wayPoint(coarseRowCurrent*2+1, coarseColCurrent*2+1));
					wayPoints.push_back(new wayPoint(coarseRowCurrent*2+1, coarseColCurrent*2));

				}

				if(direction == 'L'){
					//cout<<"Left "<<coarseRowCurrent*2+1<< coarseColCurrent*2<<" "<<coarseRowCurrent*2<<coarseColCurrent*2<<endl;

					wayPoints.push_back(new wayPoint(coarseRowCurrent*2+1, coarseColCurrent*2));
					wayPoints.push_back(new wayPoint(coarseRowCurrent*2, coarseColCurrent*2));

				}

				if(direction == 'R'){
					//cout<<"Right "<<coarseRowCurrent*2<< coarseColCurrent*2+1<<" "<<coarseRowCurrent*2+1<< coarseColCurrent*2+1<<endl;


					wayPoints.push_back(new wayPoint(coarseRowCurrent*2, coarseColCurrent*2+1));
					wayPoints.push_back(new wayPoint(coarseRowCurrent*2+1, coarseColCurrent*2+1));

				}
			}
			//TL->(i*2, i*2)
			//TR->(i*2, i*2+1)
			//BL->(i*2+1, i*2)
			//BR->(i*2+1, i*2+1)

			//Up: Top Left ->Bottom Left
			if(coarseRowCurrent > coarseRowNext){

				fineRowCurrent=coarseRowCurrent*2;
				fineColCurrent=coarseColCurrent*2;
				fineRowNext=coarseRowNext*2+1;
				fineColNext=coarseColNext*2;



				if(direction == 'R')
					wayPoints.push_back(new wayPoint(fineRowNext, fineColNext));
				else if(direction != 'L'){
					wayPoints.push_back(new wayPoint(coarseRowCurrent*2+1, coarseColCurrent*2));
					wayPoints.push_back(new wayPoint(fineRowCurrent, fineColCurrent));
					wayPoints.push_back(new wayPoint(fineRowNext, fineColNext));
				}
				else{
					wayPoints.push_back(new wayPoint(fineRowCurrent, fineColCurrent));
					wayPoints.push_back(new wayPoint(fineRowNext, fineColNext));
				}
				direction = 'U';
			}

			//Down: Bottom Right ->Top Right
			if(coarseRowCurrent < coarseRowNext){

				fineRowCurrent=coarseRowCurrent*2+1;
				fineColCurrent=coarseColCurrent*2+1;
				fineRowNext=coarseRowNext*2;
				fineColNext=coarseColNext*2+1;

				if(direction == 'L'){
					wayPoints.push_back(new wayPoint(fineRowNext, fineColNext));
				}
				else if(direction == 'R'){
					wayPoints.push_back(new wayPoint(coarseRowCurrent*2, coarseColCurrent*2+1));
					wayPoints.push_back(new wayPoint(fineRowCurrent, fineColCurrent));
					wayPoints.push_back(new wayPoint(fineRowNext, fineColNext));

				}
				else{
					wayPoints.push_back(new wayPoint(fineRowCurrent, fineColCurrent));
					wayPoints.push_back(new wayPoint(fineRowNext, fineColNext));
				}
				direction = 'D';
			}

			//Right: Top Right -> Top Left
			if(coarseColCurrent < coarseColNext){

				fineRowCurrent=coarseRowCurrent*2;
				fineColCurrent=coarseColCurrent*2+1;
				fineRowNext=coarseRowNext*2;
				fineColNext=coarseColNext*2;
				if(direction == 'D'){
					wayPoints.push_back(new wayPoint(fineRowNext, fineColNext));
				}
				else if(direction == 'U'){
					wayPoints.push_back(new wayPoint(coarseRowCurrent*2, coarseColCurrent*2));
					wayPoints.push_back(new wayPoint(fineRowCurrent, fineColCurrent));
					wayPoints.push_back(new wayPoint(fineRowNext, fineColNext));
				}
				else{
					wayPoints.push_back(new wayPoint(fineRowCurrent, fineColCurrent));
					wayPoints.push_back(new wayPoint(fineRowNext, fineColNext));
				}
				direction = 'R';
			}
			//Left: Bottom Left -> Bottom Right
			if(coarseColCurrent > coarseColNext){

				fineRowCurrent=coarseRowCurrent*2+1;
				fineColCurrent=coarseColCurrent*2;
				fineRowNext=coarseRowNext*2+1;
				fineColNext=coarseColNext*2+1;


				if(direction == 'D'){
					wayPoints.push_back(new wayPoint(coarseRowCurrent*2+1, coarseColCurrent*2+1));
					wayPoints.push_back(new wayPoint(fineRowCurrent, fineColCurrent));
					wayPoints.push_back(new wayPoint(fineRowNext, fineColNext));
				}
				else if(direction == 'U'){
					wayPoints.push_back(new wayPoint(fineRowNext, fineColNext));
				}
				else{
					wayPoints.push_back(new wayPoint(fineRowCurrent, fineColCurrent));
					wayPoints.push_back(new wayPoint(fineRowNext, fineColNext));
				}
				direction = 'L';
			}
		}
		setYawToAllWayPoints();

}

double WaypointsManager::calc_yaw(double m, wayPoint* from, wayPoint * to)
{
	double angle;

	if(!is_verticle)
	{
		angle = 180 * atan(m) / M_PI;
	}

	if (is_verticle)
	{
		if (to->x_Coordinate > from->x_Coordinate)
		{
			return (270);
		}
		else
		{
			return (90);
		}
	}
	else if ( m == 0)
	{
		if (to->y_Coordinate > from->y_Coordinate)
		{
			return (angle);
		}
		else
		{
			return (180 + angle);
		}
	}
	else if (m > 0)
	{
		if (to->x_Coordinate > from->x_Coordinate)
		{
			return (360 - angle);
		}
		else
		{
			return (180 - angle);
		}
	}
	else
	{
		if (to->x_Coordinate > from->x_Coordinate)
		{
			return (180 + angle);
		}
		else
		{
			return (angle);
		}
	}
}

void WaypointsManager::setYawToAllWayPoints(){

	int currentIndex;
	int nextIndex;
	double m;

	for (unsigned int i= 0; i < wayPoints.size()-1; ++i) {

		currentIndex = i;
		nextIndex = i+1;
		m = calc_incline(wayPoints[currentIndex], wayPoints[nextIndex]);
		wayPoints[currentIndex]->yaw=(calc_yaw(m, wayPoints[currentIndex], wayPoints[nextIndex]));
	}
}

double WaypointsManager::calc_incline(wayPoint* from, wayPoint* to)
{
	is_verticle = 0;
	if(from->y_Coordinate == to->y_Coordinate)
	{
		is_verticle = 1;
		return(9999);
	}
	else
	{
		return((to->x_Coordinate - from->x_Coordinate) / (to->y_Coordinate - from->y_Coordinate));
	}
}

void WaypointsManager::setNextWayPoint(wayPoint Next)
{
	currWayPoint.x_Coordinate = nextWayPoint.x_Coordinate;
	currWayPoint.y_Coordinate = nextWayPoint.y_Coordinate;
	currWayPoint.yaw = nextWayPoint.yaw;

	nextWayPoint.x_Coordinate = Next.x_Coordinate;
	nextWayPoint.y_Coordinate = Next.y_Coordinate;
	nextWayPoint.yaw = Next.yaw;
}


bool WaypointsManager::isInWayPoint(double x,double y)
{
//	double dx = wayPoints[wayPointArrayIndex]->x_Coordinate - x;
//	double dy = wayPoints[wayPointArrayIndex]->y_Coordinate - y;
//	double distance = sqrt(pow(dx, 2) + pow(dy, 2));
//
//	cout << "Next way point x: "<< wayPoints[wayPointArrayIndex]->x_Coordinate << " ---> current x: " << x << endl;
//	cout << "Next way point y: "<< wayPoints[wayPointArrayIndex]->y_Coordinate << " ---> current y: " << y << endl;
//	cout << "Yaw is: "<< wayPoints[wayPointArrayIndex]->yaw<<endl;
//	cout << "Distance to next way point: " << (distance) << endl;
//	cout << endl;
//
//	// Checking if the robot hit the way point, considering tolerance
//	if (distance*_gridResolution <= TOLERANCE)
//	{
//		return true;
//	}
//	return false;
	double dx = nextWayPoint.x_Coordinate - x;
	double dy = nextWayPoint.y_Coordinate - y;
	double distance = sqrt(pow(dx, 2) + pow(dy, 2));

	cout << "Next way point x: "<< nextWayPoint.x_Coordinate << " ---> current x: " << x << endl;
	cout << "Next way point y: "<< nextWayPoint.y_Coordinate << " ---> current y: " << y << endl;
	cout << "Next way point yaw" << nextWayPoint.yaw <<  endl;
	cout << "Distance to next way point: " << (distance) << endl;
	cout << endl;

	// Checking if the robot hit the way point, considering tolerance
//	if (distance  <= 1 && abs(dx)<=0.5 && abs(dy)<=0.5)
//	&& distance<=previoueDistance
	if (distance  <= 1)
	{
		inWayPoint=true;
		//previoueDistance=distance;
		return true;
	}
	//previoueDistance=distance;
	inWayPoint=false;
	return false;
}
void WaypointsManager::next_WayPoint(){

	if(this->wayPointArrayIndex+1 < wayPoints.size())
		this->wayPointArrayIndex++;

	else
		this->endOfArray = true;
}
void WaypointsManager::saveWayPointsInFile(char* fileName,vector<unsigned char> image){
 	vector<wayPoint*>::iterator it;
     wayPoint wp;
	for (it = (wayPoints).begin(); it != (wayPoints).end(); ++it) {
	 			wp = **it;
	 			int row =wp.x_Coordinate;
                int column= wp.y_Coordinate;
                //convert the row to the original map row that was read from the image
                row  = ((row+0.5) * 12 * 2);
                //convert the column to the original map column that was read from the image
                column = ((column+0.5) * 12 * 2);

                int c = (row * 550 + column) * 4;
               image[c] = 0;
               image[c + 1] = 255;
               image[c + 2] = 0;
	 		}

	lodepng::encode("wayPoints.png",image,550,380);

}
WaypointsManager::~WaypointsManager() {
	// TODO Auto-generated destructor stub
}

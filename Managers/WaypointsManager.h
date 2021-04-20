/*
 * WaypointsManager.h
 *
 *  Created on: Jun 14, 2015
 *      Author: colman
 */

#ifndef WAYPOINTSMANAGER_H_
#define WAYPOINTSMANAGER_H_

#include <iostream>
#include <vector>
#include "../WayPoint/wayPoint.h"
#include "../STC/Node.h"
#include<set>
#include "../Defines.h"
#include "../Map/lodepng.h"


using namespace std;

class WaypointsManager {
public:
    unsigned int wayPointArrayIndex;
    bool endOfArray;

	//set<wayPoint> wayPoints;
	vector<wayPoint *> wayPoints;
	wayPoint currWayPoint;
	wayPoint nextWayPoint;
    //double previoueDistance;
    bool inWayPoint;
	WaypointsManager(vector<Node*> path, double gridResolution, double mapResolution);
	void buildWayPointVector(vector<Node *> path);
	//void build_way_point_vector(int num_of_cells);
	void setNextWayPoint(wayPoint Next);
	bool isInWayPoint(double x,double y);
	void next_WayPoint();
	void saveWayPointsInFile(char* fileName,vector<unsigned char> image);
	virtual ~WaypointsManager();

private:
	vector<Node*> stc_path;
	bool is_verticle;
	double _gridResolution;
	double _mapResolution;
    void setYawToAllWayPoints();
	double calc_yaw(double m, wayPoint* from, wayPoint * to);
	double calc_incline(wayPoint* from, wayPoint* to);

};

#endif /* WAYPOINTSMANAGER_H_ */

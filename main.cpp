/*
 * main.cpp
 *
 *  Created on: Dec 14, 2016
 *      Author: user
 */
#include "STC/Node.h"
#include <iostream>
#include "Robot/Robot.h"
#include "Managers/Manager.h"
#include "Plans/ObstacleAvoidPlan.h"
#include "Map/Map.h"
#include "Managers/ConfigurationManager.h"
#include "Managers/WaypointsManager.h"
#include "STC/STC.h"

using namespace std;
int main()
{
	//load the file data into the ConfigurationManager data members
	ConfigurationManager ConfigMgr(CONFIGURATION_PATH);
	//defines a new Map
	Map map(ConfigMgr.map_resolution, ConfigMgr.robot_length);
	//loads the map from the ConfigurationManager

	map.loadMapFromFile(ConfigMgr.map_path);
	map.inflateObstacles();
	map.buildFineGrid();
	map.buildCoarseGrid();

    //create new image file after inflatetion
	map.writeinflateObstacles();

	//map.printInflateMap();
//	cout<<"-------------------------------"<<endl;
	//map.printGrid(map.getMap());
	//cout<<"-------------------------------"<<endl;
//	map.printGrid(map.getFineGrid());
//	cout<<"-------------------------------"<<endl;
//	map.printGrid(map.getCoarseGrid());

	Position startPos;

	//initialized the startPos with data from ConfigMgr
	startPos.first = ConfigMgr.start_y/24;
	startPos.second = ConfigMgr.start_x/24;

	cout<<"startPos.first(coarse): " << startPos.first<< ",startPos.second(coarse): " << startPos.second << endl;

	STC stc(map, startPos);

	//draw spanning tree on image
	map.addPathToFile((char*)"newroboticLabMap.png", stc.getGraph(), stc.getGraphWidth(),stc.getGraphHeight());

	vector <Node *>  path = stc.getPath();
	WaypointsManager wpm(path,ConfigMgr.grid_resolution,ConfigMgr.map_resolution);

	wpm.buildWayPointVector(path);
    //wpm.saveWayPointsInFile("s",map.GetImage());

 	wayPoint wp;
 	vector<wayPoint*>::iterator it;


 	// Printing the way points
 	cout<<"way points :"<<endl;
 	for (it = (wpm.wayPoints).begin(); it != (wpm.wayPoints).end(); ++it) {
 			wp = **it;
 			cout << wp.x_Coordinate << " " << wp.y_Coordinate << " " << wp.yaw << endl;

 		}

//10.10.245.64
 		Robot robot("localhost",6665, &ConfigMgr,map.getFineGrid().size() );

 	    ObstacleAvoidPlan plnOA(&robot, &wpm);
 	   	//LocalizationManager lm;

 	   	// Start moving in the path
 	   	Manager manager(&robot, &plnOA, NULL, &ConfigMgr, &wpm);
 	   	manager.run();
 	    cout<<"running complete !"<<endl;

    return 0;
}



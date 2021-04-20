/*
 * wayPoint.cpp
 *
 *  Created on: Jun 14, 2015
 *      Author: colman
 */

#include "wayPoint.h"

wayPoint::wayPoint(double x, double y, double yaw_angle)
{
	x_Coordinate = x;
	y_Coordinate = y;
	yaw = yaw_angle;
}//

wayPoint::wayPoint(double x, double y){
	x_Coordinate= x;
	y_Coordinate = y;
}
wayPoint::wayPoint() {
	// TODO Auto-generated constructor stub

}

wayPoint::~wayPoint() {
	// TODO Auto-generated destructor stub
}


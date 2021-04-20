/*
 * wayPoint.h
 *
 *  Created on: Jun 14, 2015
 *      Author: colman
 */

#ifndef WAYPOINT_H_
#define WAYPOINT_H_

#include "limits.h"

class wayPoint {
public:
	double x_Coordinate;
	double y_Coordinate;
	double yaw;

	wayPoint();
	wayPoint(double x, double y);
	wayPoint(double x, double y, double yaw_angle);
	virtual ~wayPoint();
	bool operator<(const wayPoint& wp) const
	{
		return (y_Coordinate*INT_MAX + x_Coordinate + yaw > wp.y_Coordinate*INT_MAX + wp.x_Coordinate + yaw);
	}
};

#endif /* WAYPOINT_H_ */

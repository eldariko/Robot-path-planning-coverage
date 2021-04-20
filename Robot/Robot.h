
#ifndef ROBOT_H_
#define ROBOT_H_

#include <libplayerc++/playerc++.h>
#include "../Defines.h"
#include "../Managers/ConfigurationManager.h"

using namespace PlayerCc;

class Robot {

	PlayerClient* _pc;
	Position2dProxy* _pp;
	LaserProxy* _lp;
	ConfigurationManager* _cm;

public:

	double _x;
	double _y;
	double _yaw;
	int _grid_rows;

	Robot(const char* ip, int port, ConfigurationManager* cm,int grid_rows);
	void Read();
	void setSpeed(float xSpeed, float angularSpeed);
	bool isRightFree();
	bool isLeftFree();
	bool isForwardFree();
	LaserProxy* getLaser();
	double getXpos();
	double getYpos();
	double getYaw();
	void setX(double x);
	void setY(double y);
	void setYaw(double yaw);
	float getLaserDistance(int index);
	bool checkRange(int nStart, int nEnd);
	double getLaserSpec();
	void drive(int cmToMove);

	virtual ~Robot();
};

#endif /* ROBOT_H_ */

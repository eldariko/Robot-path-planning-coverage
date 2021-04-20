
#include "Robot.h"
#include <math.h>

Robot::Robot(const char* ip, int port, ConfigurationManager* cm, int grid_rows) {

	int c=2;
	_pc = new PlayerClient(ip, port);
	_pp = new Position2dProxy(_pc);
	_lp = new LaserProxy(_pc);
	_cm = cm;
	_grid_rows = grid_rows;


	//For fixing Player's reading BUG
	for(int i=0;i<15;i++)
		Read();


	for(int i=0;i<5;i++)
		_pp->SetOdometry((_cm->start_x*_cm->map_resolution)-(6.875),((4.75)-(_cm->start_y*_cm->map_resolution)),cm->yaw* M_PI/180);


	//double resolution_relation = _cm->grid_resolution / _cm->map_resolution;

	//_pp->SetOdometry((_cm->start_x*_cm->map_resolution)-(6.875),(_cm->start_y*_cm->map_resolution)-(4.75),cm->yaw* M_PI/180);
	cout << " x1 " << getXpos() << " y1 " << getYpos() << "yaw" <<cm->yaw*M_PI/180 << endl;
	cout << " x2 " << _pp->GetXPos() << " y2 " << _pp->GetYPos() << "yaw(" <<_pp->GetYaw()<<")" << endl;
	cout << " x3 " << (_cm->start_x*_cm->map_resolution)-((double)(6.875)) << " y3 " << (_cm->start_y*_cm->map_resolution)-(4.75) << "yaw(" <<_pp->GetYaw()<<")" << endl;

//	_pp->SetOdometry((_cm->start_x*_cm->map_resolution)-(13.75/2),(_cm->start_y*_cm->map_resolution)-(9.5/2),M_PI);
//	cout << " x1 " << getXpos() << " y1 " << getYpos() << "yaw" <<cm->yaw*M_PI/180 << endl;
//	cout << " x2 " << _pp->GetXPos() << " y2 " << _pp->GetYPos() << "yaw(" <<_pp->GetYaw()<<")" << endl;
//	cout << " x3 " << (_cm->start_x*_cm->map_resolution)-((double)(13.75/2)) << " y3 " << (_cm->start_y*_cm->map_resolution)-(9.5/2) << "yaw(" <<_pp->GetYaw()<<")" << endl;

	_pp->SetMotorEnable(true);

//		_pp->SetOdometry(((double)cm->start_x / (resolution_relation)/ (_cm->grid_resolution)), ((_grid_rows / _cm->grid_resolution) - (((double)cm->start_y) / (_cm->grid_resolution / _cm->map_resolution)/ (_cm->grid_resolution))) ,cm->yaw*M_PI/180);
//				cout << " x " << ((double)cm->start_x / (resolution_relation)/ (_cm->grid_resolution)) << " y " << getYpos() << "yaw" << getYaw() << endl;
//				cout << " x " << getXpos() << " y " << ((_grid_rows / _cm->grid_resolution) - (((double)cm->start_y) / (_cm->grid_resolution / _cm->map_resolution)/ (_cm->grid_resolution))) << "yaw" <<cm->yaw*M_PI/180 << endl;

				//	_pp->SetOdometry(((double)cm->start_x / (_cm->grid_resolution / _cm->map_resolution)/ (_cm->grid_resolution)), ((_grid_rows / _cm->grid_resolution) - (((double)cm->start_y) / (_cm->grid_resolution / _cm->map_resolution)/ (_cm->grid_resolution))) ,cm->yaw*M_PI/180);
//	cout << " x " << getXpos() << " y " << getYpos() << "yaw" << getYaw() << endl;
}

void Robot::Read()
{
	_pc->Read();
}

void Robot::setSpeed(float xSpeed, float angularSpeed) {
	_pp->SetSpeed(xSpeed, angularSpeed);
}

bool Robot::isRightFree() {
	if ((*_lp)[RIGHT_LASER_PROXY_VALUE] > 0.1)
		return true;
	else
		return false;
}

bool Robot::isLeftFree() {
	if ((*_lp)[LEFT_LASER_PROXY_VALUE] > 0.1)
		return true;
	else
		return false;
}

bool Robot::isForwardFree() {
	if ((*_lp)[FORWARD_LASER_PROXY_VALUE] > 0.1)
		return true;
	else
		return false;
}

// Getting the X position of the robot calculated with the right resolution
double Robot::getXpos()
{
//	return _pp->GetXPos();
//	return ((_pp->GetXPos()) * _cm->grid_resolution);
	double xPosInPixeles=(((_pp->GetXPos() + (6.875))/_cm->map_resolution));
    //cout<<"x pos"<<xPosInPixeles<<endl;
	return (xPosInPixeles/12.0);//fine grid pos
}

// Getting the Y position of the robot calculated with the right resolution
double Robot::getYpos()
{
//	return _pp->GetYPos();
//	return (((_grid_rows / _cm->grid_resolution) - _pp->GetYPos()) * _cm->grid_resolution);

	double yPosInPixeles=((9.5-(_pp->GetYPos() + (4.75)))/_cm->map_resolution);
	//cout<<"y pos"<<yPosInPixeles<<endl;
	return  (yPosInPixeles/12.0);//fine grid pos;

}

double Robot::getYaw()
{
	_yaw = (180*(_pp->GetYaw()))/M_PI;
	if(_yaw >= 0)
	{
		return (_yaw);
	}
	else
	{
		return (360+_yaw);
	}
}

LaserProxy* Robot::getLaser()
{
	return (_lp);
}

float Robot::getLaserDistance(int index)
{
	return _lp->GetRange(index);
}

bool Robot::checkRange(int nStart, int nEnd)
{
	bool is_Good = true;

	for (int index = nStart; (index <= nEnd) && (is_Good); index++)
	{
		is_Good = (this->getLaserDistance(index) > DISTANCE_TOLERANCE);
	}

	return (is_Good);
}


double Robot::getLaserSpec()
{
	double laserSpec=(((_lp->GetMaxAngle() * 180 / M_PI) + 120 ) / 0.36);
	return laserSpec;
}

// Driving "cmToMove" centimeters forward
void Robot::drive(int cmToMove)
{
	_pc->Read();

	double radYaw = _pp->GetYaw();
	double locationX = _pp->GetXPos();
	double locationY = _pp->GetYPos();

	locationX += (cos(radYaw) * cmToMove);
	locationY += (sin(radYaw) * cmToMove);

	double currX = getXpos();
	double currY = getYpos();

	while(currX < locationX)
	{
		_pc->Read();
		_pp->SetSpeed(0.2, 0.0);
		currX = getXpos();
		currY = getYpos();
		cout << currX << endl;
	}

	_pp->SetSpeed(0.0,0.0);

}

Robot::~Robot() {
	delete _pc;
	delete _pp;
	delete _lp;
}

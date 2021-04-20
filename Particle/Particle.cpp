/*
 * Particle.cpp
 *
 *  Created on: Jun 17, 2015
 *      Author: colman
 */

#include "Particle.h"

Particle::Particle(Node node, double dYaw){
    this->_node.col = node.col;
    this->_node.row = node.row;
    this->_Teta = dYaw;
    this->_Belief = 1;
}

// This function update the particle according to the deltas and the laser
double Particle::update(double deltaX, double deltaY, double deltaTeta , LaserProxy* laser)
{
    // Update the particle position
    _node.col += deltaX;
    _node.row += deltaY;
    _Teta += deltaTeta;

    // Guess the probability
    double byMov = probMov(deltaX, deltaY, deltaTeta);
    _Belief = _Belief * byMov * NORMALIZE_FACTOR;

    if (_Belief > 1)
    {
    	_Belief = 1;
    }

    return _Belief;
}

// Probability by move
double Particle::probMov(double deltaX, double deltaY, double deltaTeta)
{
    double dist = sqrt(pow(deltaX, 2) + pow(deltaY, 2));
    double pro = 0;

	if(deltaTeta < 0)
		deltaTeta *= -1;
	if(dist > TRH_DIS && deltaTeta > TRH_YAW)
		pro = 0.2;
	if((dist < TRH_DIS && deltaTeta > TRH_YAW)||(dist > TRH_DIS && deltaTeta < TRH_YAW))
		pro = 0.4;
	if(dist < TRH_DIS && deltaTeta < TRH_YAW)
		pro = 0.8;
	if(dist < TRH_DIS && deltaTeta == 0)
		pro = 1;
	return pro;
}



double Particle::getBelief()
{
    return (this->_Belief);
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}


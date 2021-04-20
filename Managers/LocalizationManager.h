/*
 * LocalizationManager.h
 *
 *  Created on: Jun 17, 2015
 *      Author: colman
 */

#ifndef LOCALIZATIONMANAGER_H_
#define LOCALIZATIONMANAGER_H_
#include <list>
#include "../Particle/Particle.h"

using namespace std;

#define THRESHOLD 0.25
#define STANDARD 0.7
#define MAX_PARTICLES_NUM 100
#define MIN_PARTICLES_NUM 1
#define PARTICLE_RANGE 0.3
#define PARTICLE_NUM_TO_CREATE 5

class LocalizationManager {
public:

	LocalizationManager();
    void update(double dX, double dY, double dTeta, double deltaX, double deltaY, double deltaTeta, LaserProxy* pLaserProxy);
    Particle* getHighestProbParticle();
    virtual ~LocalizationManager();

private:
    list<Particle> arrParticles;

    void createChildren(double dX, double dY, double dRange, int nParticlesNum);
};

#endif /* LOCALIZATIONMANAGER_H_ */

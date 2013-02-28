#ifndef INTERPARTICLEFORCE_H
#define INTERPARTICLEFORCE_H

#include "particle.h"
#include <armadillo>

using namespace arma;

class InterParticleForce
{
public:
    InterParticleForce();
    /**
     * @brief calculate
     * @param p1 Particle 1
     * @param p2 Particle 2
     * @return Force on particle 1 from particle 2
     */
    virtual vec3 calculate(Particle* p1, Particle* p2, vec3 &correction) = 0;
    virtual double energy(Particle* p1, Particle* p2, vec3 &correction) = 0;
    vec3 r;
};

#endif // INTERPARTICLEFORCE_H

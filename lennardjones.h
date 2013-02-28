#ifndef LENNARDJONES_H
#define LENNARDJONES_H

#include "interparticleforce.h"
#include "particle.h"
#include <armadillo>

using namespace arma;

class LennardJones : public InterParticleForce
{
public:
    LennardJones();
    virtual vec3 calculate(Particle* p1, Particle* p2, vec3 &correction);
    virtual double energy(Particle* p1, Particle* p2, vec3 &correction);
};

#endif // LENNARDJONES_H

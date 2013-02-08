#ifndef PARTICLE_H
#define PARTICLE_H

#include <armadillo>
using namespace arma;

class Particle
{
public:
    Particle();

    void setR(double, double, double);

    vec3 r;
    vec3 v;
    vec3 F;

    double m;
};

#endif // PARTICLE_H

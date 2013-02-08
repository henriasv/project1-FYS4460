#include "particle.h"

Particle::Particle()
{
}

void Particle::setR(double x, double y, double z)
{
    r(0) = x; r(1) = y; r(2) = z;
}

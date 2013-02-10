#include "particle.h"

Particle::Particle()
{
    r.zeros();
    v.zeros();
    F.zeros();
    type = "Ar";
}

string Particle::VMDString()
{
    ostringstream tmp;
    tmp << type << " " << r(0) << " " << r(1) <<" " << r(2) << "\n";
    return tmp.str();
}

void Particle::setR(double x, double y, double z)
{
    r(0) = x; r(1) = y; r(2) = z;
}



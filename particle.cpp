#include "particle.h"

Particle::Particle()
{
    r.zeros();
    v.zeros();
    F.zeros();
    m = 1;
    Ep = 0;
    type = "Ar";
}

string Particle::VMDString()
{
    ostringstream tmp;
    tmp << type << " " << r(0) << " " << r(1) <<" " << r(2) << " " << v(0) << " " << v(1) << " " << v(2) << "\n";
    return tmp.str();
}

void Particle::setR(double x, double y, double z)
{
    r(0) = x; r(1) = y; r(2) = z;
}

void Particle::setV(double vx, double vy, double vz)
{
    v(0) = vx; v(1) = vy; v(2) = vz;
}

void Particle::setV(vec3 V)
{
    v = V;
}

void Particle::scaleV(double fac) {
    v = v*fac;
}

double Particle::getEk()
{
    return 0.5*m*(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
}

double Particle::getEp()
{
    return Ep;
}

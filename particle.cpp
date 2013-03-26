#include "particle.h"

Particle::Particle()
{
    r.zeros();
    v.zeros();
    F.zeros();
    m = 1;
    Ep = 0;
    p_contribution = 0;
    r_correction.zeros();
    type = "Ar";
}

string Particle::VMDString()
{
    ostringstream tmp;
    tmp << type << " "
        << r(0) << " " << r(1) << " " << r(2) << " "
        << v(0) << " " << v(1) << " " << v(2) << " "
        << F(0) << " " << F(1) << " " << F(2) << " "
        << r(0)+r_correction(0) << " " << r(1)+r_correction(1) << " " << r(2)+r_correction(2) << "\n";
    return tmp.str();
}

void Particle::setR(double x, double y, double z)
{
    r(0) = x; r(1) = y; r(2) = z;
}

void Particle::setR(vec3 R)
{
    r(0) = R(0); r(1) = R(1); r(2) = R(2);
}

void Particle::setV(double vx, double vy, double vz)
{
    v(0) = vx; v(1) = vy; v(2) = vz;
}

void Particle::setV(vec3 V)
{
    v = V;
}

void Particle::setF(vec3 _F)
{
    F(0) = _F(0); F(1) = _F(1); F(2) = _F(2);
}

void Particle::setType(string _type)
{
    type = _type;
}

void Particle::scaleV(double fac) {
    v = v*fac;
}

double Particle::getEk()
{
    return 0.5*m*(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
}

double Particle::getp_contribution()
{
    return p_contribution;
}

double Particle::getEp()
{
    return Ep;
}

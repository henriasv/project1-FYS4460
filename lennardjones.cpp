#include "lennardjones.h"

LennardJones::LennardJones() : InterParticleForce()
{
}

vec3 LennardJones::calculate(Particle *p1, Particle *p2, vec3 &correction)
{
     r = p1->r - p2->r - correction;
     double rsq = r[0]*r[0]+r[1]*r[1]+r[2]*r[2];
     double r6 = rsq*rsq*rsq;
     double r12 = r6*r6;

     vec3 ret =  24*(2.0/r12 - 1.0/r6)*r/rsq;
     //cout << "Force " << ret << endl;
     return ret;//.zeros();
}

double LennardJones::energy(Particle *p1, Particle *p2, vec3 &correction)
{

    r = p1->r - p2->r - correction;
    double rsq = r[0]*r[0]+r[1]*r[1]+r[2]*r[2];
    double r6 = rsq*rsq*rsq;
    double r12 = r6*r6;
    return 4*(1.0/r12 - 1.0/r6);

}

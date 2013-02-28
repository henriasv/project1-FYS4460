#ifndef PARTICLE_H
#define PARTICLE_H

#include <armadillo>
#include <string>
#include <fstream>
using namespace arma;
using namespace std;

class Particle
{
public:
    Particle();
    string VMDString();

    void setR(double, double, double);
    void setV(double, double, double);
    void setV(vec3);

    double getEk();

    vec3 r;
    vec3 v;
    vec3 F;

    string type;

    double m;
};

#endif // PARTICLE_H

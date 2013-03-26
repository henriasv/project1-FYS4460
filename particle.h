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
    void setR(vec3);
    void setV(double, double, double);
    void setV(vec3);
    void setF(vec3);
    void setType(string);

    double getEk();
    double getp_contribution();

    vec3 r_correction; // Adds the displacement due to periodic boundary.
    vec3 r;
    vec3 v;
    vec3 F;

    string type;

    double m;
    double Ep;
    double p_contribution;
    double getEp();
    void scaleV(double fac);
};

#endif // PARTICLE_H

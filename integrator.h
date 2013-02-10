#ifndef INTEGRATOR_H
#define INTEGRATOR_H
#include <vector>
#include "mdsystem.h"
#include "particle.h"

using namespace std;
class Integrator
{
public:
    Integrator(MDSystem* _system, Config &cfg);
    virtual void step() = 0;
    void integrate();

    vector<Particle*> particles;
    MDSystem* system;
    double t;
    double dt;
    double T;
};

#endif // INTEGRATOR_H

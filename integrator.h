#ifndef INTEGRATOR_H
#define INTEGRATOR_H
#include <vector>
#include "mdsystem.h"
#include "particle.h"
#include "measurements.h"
#include <libconfig.h++>
#include "thermostat.h"

using namespace libconfig;
using namespace std;
class Integrator
{
public:
    Integrator(MDSystem* _system, Config* cfg);
    ~Integrator();
    virtual void step() = 0;
    void integrate();
    void thermostatAction(double);

    vector<Particle*> particles;
    MDSystem* system;
    Thermostat* thermostat;
    double t;
    double dt;
    double T;
    double tau;
    double temperature_th;

    Measurements* measure;

    // Choice of thermostat
    enum {NONE, BERENDSEN};
};

#endif // INTEGRATOR_H

#ifndef MEASUREMENTS_H
#define MEASUREMENTS_H
#include "mdsystem.h"
#include "particle.h"
#include <vector>

class Measurements
{
public:
    Measurements(MDSystem*);
    void measureAll(double t, int n_t);
    void measureEk();
    void measureEp();
    void measureEtot();
    void measurep();
    void measureT();

    void outputAll();

    // The last measurements done, and on which time and timestep
    double T;
    double p;
    double Ek;
    double Ep;
    double Etot;
    double t;
    double n_t;

    vector<Particle*> particles;
    string filenameMeasures;
    ofstream outfileMeasures;
    MDSystem* system;

};

#endif // MEASUREMENTS_H

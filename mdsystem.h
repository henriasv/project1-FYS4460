#ifndef MDSYSTEM_H
#define MDSYSTEM_H

#include "cell.h"
#include "particle.h"
#include <libconfig.h++>

using namespace libconfig;

class MDSystem
{
public:
    MDSystem(Config &cfg);
    MDSystem();
    void cell_positions();
    void createParticlesFCC();

    // System properties in units of sigma
    double r_crit;
    double L;

    // Cell properties
    double l; // in units of sigma

    // Number of cells
    int Nx;
    int Ny;
    int Nz;

    // Number of FCC cells
    int NxFCC;
    int NyFCC;
    int NzFCC;

    // FCC cell properties
    double b; // Width of an fcc cell

    // Cells containing atoms
    Cell**** cells;

    // Vector of particle pointers. A neat way to access all particle outside of cell structure
    vector <Particle*> particles;

};

#endif // MDSYSTEM_H

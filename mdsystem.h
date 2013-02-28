#ifndef MDSYSTEM_H
#define MDSYSTEM_H

#include "cell.h"
#include "particle.h"
//#include <libconfig.h++>
#include "outputmd.h"
#include "interparticleforce.h"
#include "lennardjones.h"

class Config;

//using namespace libconfig;

class MDSystem
{
public:
    MDSystem(Config &cfg);
    MDSystem();
    ~MDSystem();
    void cell_positions(); //DEBUG function
    void createParticlesFCC();
    void fillCells(); // If the particles vector is filled, this function puts them into cells
    void fillCellsAlternate();
    void checkNumParticles(); // DEBUG Check if number of particles in cells and vector is the same.
    void calculateForces();
    void setPositionsPeriodic();
    void updateCells();

    // Helping functions
    bool belongToCell(Particle* p, int i, int j, int k);
    void putInCell(Particle* p);

    // Output functions
    void outputVMD();
    void outputAll();

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

    // InterParticleForce object
    InterParticleForce* force;
    // OutputObject
    OutputMD output;
};

#endif // MDSYSTEM_H

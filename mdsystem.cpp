#include "mdsystem.h"

MDSystem::MDSystem(Config &cfg)
{
    // Here, the system is to be initialized with some config file, possibly linking to a file containing particle positions.
}

MDSystem::MDSystem()
{
    NxFCC = 8; NyFCC = 8, NzFCC = 8;
    b = 5.268/3.405; // b'/sigma
    L = NxFCC* b;
    r_crit = 3;
    Nx = (int) (NxFCC*b/r_crit);
    Ny = (int) (NyFCC*b/r_crit);
    Nz = (int) (NzFCC*b/r_crit);
    l = L/Nx;

    cout << "Initializing system with " << Nx <<" x "<<Ny<<" "<<"Nz"<< " neighbor cells" << endl;
    cells = new Cell***[Nx];
    for (int i = 0; i<Nx; i++) {
        cells[i] = new Cell**[Ny];
            for (int j = 0; j<Ny; j++) {
                cells[i][j] = new Cell*[Nz];
                for (int k = 0; k<Nz; k++) {
                    vec3 tmp;
                    tmp(0) = i;
                    tmp(1) = j;
                    tmp(2) = k;
                    cells[i][j][k] = new Cell(l*tmp);
            }
        }
    }
    cell_positions();
}

void MDSystem::cell_positions()
{
    cout << "*DEBUG* couting cell corners" << endl;
    for (int i = 1; i<Nx; i++) {
        for(int j = 0; j<Ny; j++) {
            for (int k = 0; k<Nz; k++) {
                cells[i][j][k]->corner.print(); cout << endl;
            }
        }
    }
}


void MDSystem::createParticlesFCC() {
    for (int i = 0; i<NxFCC; i++) {
        for(int j = 0; j<NyFCC; j++) {
            for (int k = 0; j<NzFCC; k++) {
                Particle* tmpP = new Particle();
                tmpP->setR(b*i, b*j, b*k);
                particles.push_back(tmpP);
            }
        }
    }
}

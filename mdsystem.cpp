#include "mdsystem.h"

MDSystem::MDSystem(Config &cfg)
{
    // Here, the system is to be initialized with some config file, possibly linking to a file containing particle positions.
}

MDSystem::MDSystem()
{
    // This is to come from config file!
    string outPath = "/home/henrik/NumericalData/FYS4460/test/";
    output.open(outPath);

    force = new LennardJones();

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
    //cell_positions();
    createParticlesFCC();
    fillCells();
    checkNumParticles();
}

MDSystem::~MDSystem()
{

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
            for (int k = 0; k<NzFCC; k++) {
                Particle* tmp1 = new Particle();
                Particle* tmp2 = new Particle();
                Particle* tmp3 = new Particle();
                Particle* tmp4 = new Particle();
                tmp1->setR(b*i, b*j, b*k);
                tmp2->setR(b*i+b/2, b*j+b/2, b*k);
                tmp3->setR(b*i, b*j+b/2, b*k+b/2);
                tmp4->setR(b*i+b/2, b*j, b*k+b/2);
                tmp1->v(0) = 5;
                tmp2->v(0) = -5;
                tmp3->v(1) = 5;
                tmp4->v(1) = -5;
                particles.push_back(tmp1);
                particles.push_back(tmp2);
                particles.push_back(tmp3);
                particles.push_back(tmp4);
            }
        }
    }
}

void MDSystem::fillCells()
{
    for (uint m = 0; m<particles.size(); m++) {
        int i = (int) (particles[m]->r(0)/l);
        int j = (int) (particles[m]->r(1)/l);
        int k = (int) (particles[m]->r(2)/l);
        cells[i][j][k]->add(particles[m]);
        cout << "Adding particle to cell " << i << " " << j << " " << k << endl;
    }
}

void MDSystem::fillCellsAlternate()
{
    for (int i = 0; i<Nx; i++) {
        for (int j = 0; j<Ny; j++) {
            for (int k = 0; k<Nz; k++) {
                for (uint m = 0; m<particles.size(); m++) {
                    if  (
                            particles[m]->r(0) >= i*l
                        &&  particles[m]->r(0) < (i+1)*l
                        &&  particles[m]->r(1) >= j*l
                        &&  particles[m]->r(1) <(j+1)*l
                        &&  particles[m]->r(2) >= k*l
                        &&  particles[m]->r(2) <(k+1)*l
                         )
                    {
                        cells[i][j][k]->add(particles[m]);
                        cout << "Adding particle to cell " << i << " " << j << " " << k << endl;
                    }
                }
            }
        }
    }
}

void MDSystem::checkNumParticles()
{
    int cellParticleCount = 0;
    int vectorParticleCount = particles.size();

    for (int i = 0; i<Nx; i++)
        for (int j = 0; j<Ny; j++)
            for (int k = 0; k<Nz; k++)
                cellParticleCount += cells[i][j][k]->size();

    cout << "Particles in vector: " << vectorParticleCount << endl <<
            "Particles in cells:  " << cellParticleCount << endl;
}

void MDSystem::calculateForces()

// Insert modulo operator in looping to include periodic boundary!
{
    cout << "Started calculating forces" << endl;
    setPositionsPeriodic();
    updateCells();
    vec3 correction;
    for (int i = 0; i<Nx; i++) {
        for (int j = 0; j<Ny; j++) {
            for(int k = 0; k<Nz; k++) {
                for (int m = 0; m<cells[i][j][k]->particles.size(); m++) {
                    cells[i][j][k]->particles[m]->F.zeros();
                // Calculate force on each particle from neighbor cell particles
                    for (int ii = -1; ii<=1; ii++) {
                        for (int jj = -1; jj<=1; jj++) {
                            for (int kk = -1; kk<=1; kk++) {
                                int iii = (i+ii+Nx)%Nx;
                                int jjj = (j+jj+Ny)%Ny;
                                int kkk = (k+kk+Nz)%Nz;
                                correction(0) = -L*((i+ii)==-1) + L*(i+ii==Nx);
                                correction(1) = -L*((j+jj)==-1) + L*(j+jj==Ny);
                                correction(2) = -L*((k+kk)==-1) + L*(k+kk==Nz);
                                for (int mm = 0; mm<cells[iii][jjj][kkk]->particles.size(); mm++) {
                                    if (!(ii==0 && jj==0 && kk==0 && mm==m)) {
                                        cells[i][j][k]->particles[m]->F = cells[i][j][k]->particles[m]->F +
                                            force->calculate(cells[i][j][k]->particles[m], cells[iii][jjj][kkk]->particles[mm], correction);

                                    }
                                }
                            }
                        }
                    }
                }
            }
            cout << "j= " << j << endl;
        }
        cout << "i= " << i << endl;
    }
}

void MDSystem::setPositionsPeriodic()
{
    for (int m = 0; m<particles.size(); m++) {
        if (particles[m]->r(0)<0) {
            particles[m]->r(0) = particles[m]->r(0) + L;
        }
        if (particles[m]->r(0)>=L) {
            particles[m]->r(0) = particles[m]->r(0) - L;
        }
        if (particles[m]->r(1)<0) {
            particles[m]->r(1) = particles[m]->r(1) + L;
        }
        if (particles[m]->r(1)>=L) {
            particles[m]->r(1) = particles[m]->r(1) - L;
        }
        if (particles[m]->r(2)<0) {
            particles[m]->r(2) = particles[m]->r(2) + L;
        }
        if (particles[m]->r(2)>=L) {
            particles[m]->r(2) = particles[m]->r(2) - L;
        }

    }
}

void MDSystem::updateCells()
{
    int counter = 0;
    for (int i = 0; i<Nx; i++)  {
        for (int j = 0; j<Ny; j++) {
            for (int k = 0; k<Nz; k++) {
                for (int m = 0; m < cells[i][j][k]->particles.size(); m++) {
                    if (!belongToCell(cells[i][j][k]->particles[m], i, j, k)) {
                        putInCell(cells[i][j][k]->pop(m));
                        counter ++;
                    }
                }
            }
        }
    }
    cout << counter << " particles changed cells" << endl;
}

bool MDSystem::belongToCell(Particle* p, int i, int j, int k)
{
    double lx = i*l; double ly = j*l; double lz = k*l;
    return (p->r(0)>=lx && p->r(0)<lx+l && p->r(1)>=ly && p->r(1)<ly+l && p->r(2)>=lz && p->r(2)<lz+l);
}

void MDSystem::putInCell(Particle *p)
{
    int i = (int) (p->r(0)/l);
    int j = (int) (p->r(1)/l);
    int k = (int) (p->r(2)/l);
    if (i<0 || i>=Nx || j<0 || j>=Ny || k<0 || k>=Nz) {
        cout << "Trying to put particle in cell (" << i << ", " << ", " << j << ", " << k <<")" << endl;
        cout << "This is illegal" << endl;
        exit(1);
    }
    cells[i][j][k]->add(p);
}



void MDSystem::outputVMD()
{
    ostringstream tmp; tmp << particles.size() << "\n" << "comment" << "\n";
    output.VMD(tmp.str());
    for (uint m = 0; m<particles.size(); m++) {
        output.VMD(particles[m]->VMDString());
    }
}

void MDSystem::outputAll()
{
    outputVMD();
}




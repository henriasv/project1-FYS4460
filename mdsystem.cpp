#include "mdsystem.h"
#include <cmath>
#include <fstream>

using namespace libconfig;

MDSystem::MDSystem(Config* cfg)
{
    // Getting information from config
    cfg->lookupValue("settings.output_path", outPath);
    string outName = "out.xyz";
    output.open(outPath+outName);
    cout << outPath << endl;

    T = cfg->lookup("system.temperature");


    int potential = cfg->lookup("system.potential");
    cout << "Potential = " << potential << endl;
    int initialization = cfg->lookup("settings.sim_type");
    r_crit = cfg->lookup("settings.r_crit");
    cout << "r_crit = " << r_crit << endl;

    // creating force object
    switch (potential) {
        case LENNARD_JONES:
            force = new LennardJones();
            break;
        default:
        cout << " Invalid potential " << endl;
            cerr << "invalid potential in config" << LENNARD_JONES << endl;
            exit(1);
    }

    string tmp_input_path;
    state_file_name = "state.xyz";

    switch (initialization) {
        case FCC:
            NxFCC = cfg->lookup("system.initialization.fcc.NxFCC");
            NyFCC = cfg->lookup("system.initialization.fcc.NyFCC");
            NzFCC = cfg->lookup("system.initialization.fcc.NzFCC");
            // ***Hardcoding argon gas here***
            b = cfg->lookup("system.initialization.fcc.argon.b");
            cout << "b = " << b << endl;
            L = NxFCC*b; // HARDCODING cubic system here
            v_dist = cfg->lookup("system.initialization.fcc.v_dist");
            num_particles = NxFCC*NyFCC*NzFCC*4;
            createParticlesFCC();
            setVelocities();
            cout << "Created FCC lattice and set initial velocities" << endl;
            break;

        case STATE:
            cout << "Trying to initialize from state file " << endl;
            num_particles = cfg->lookup("system.initialization.state.num_particles");
            L = cfg->lookup("system.initialization.state.L");
            cfg->lookupValue("settings.input_path", tmp_input_path);
            cout << "loading state from " << tmp_input_path+state_file_name << endl;
            createParticlesStateFile(tmp_input_path+state_file_name);
            break;

        default:
            cerr << "Invalid initialization option.";
            cout << "quitting" << endl;
            exit(1);
    }

    createCells();
    fillCellsAlternate();

    cout << "Filled cells " << endl;
    checkNumParticles(); //*debug*

}

/*
MDSystem::MDSystem()
{
    // This is to come from config file!
    outPath = "/home/henrik/NumericalData/FYS4460/test/";
    output.open(outPath);

    force = new LennardJones();

    NxFCC = 8; NyFCC = 8, NzFCC = 8;
    b = 5.268/3.405; // b'/sigma
    L = NxFCC* b;
    //T0 = 100;
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
*/

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

                particles.push_back(tmp1);
                particles.push_back(tmp2);
                particles.push_back(tmp3);
                particles.push_back(tmp4);
            }
        }
    }


}

void MDSystem::createParticlesStateFile(string inFile)
{
    cout << "in MDSystem::createParticlesStateFile(string inFile)" << endl;
    int tmp_num_particles;
    ifstream input_data_file(inFile.c_str());
    string tmp;
    input_data_file >> tmp_num_particles;
    cout << tmp_num_particles << endl;
    input_data_file >> tmp;
    cout << tmp << endl;

    for (int i = 0; i<tmp_num_particles; i++) {
        Particle* tmp = new Particle();
        vec3 r_tmp;
        vec3 v_tmp;
        vec3 F_tmp;
        string type_tmp;
        input_data_file >> type_tmp; // reading type
        cout << type_tmp << endl;
        double tmp_val;
        input_data_file >> tmp_val;
        r_tmp(0) = tmp_val;
        input_data_file >> tmp_val;
        r_tmp(1) = tmp_val;
        input_data_file >> tmp_val;
        r_tmp(2) = tmp_val;
        input_data_file >> tmp_val;
        v_tmp(0) = tmp_val;
        input_data_file >> tmp_val;
        v_tmp(1) = tmp_val;
        input_data_file >> tmp_val;
        v_tmp(2) = tmp_val;
        input_data_file >> tmp_val;
        F_tmp(0) = tmp_val;
        input_data_file >> tmp_val;
        F_tmp(1) = tmp_val;
        input_data_file >> tmp_val;
        F_tmp(2) = tmp_val;

        // Skip reading correction for self diffusion..
        input_data_file >> tmp_val;
        input_data_file >> tmp_val;
        input_data_file >> tmp_val;

        tmp->setR(r_tmp);
        tmp->setV(v_tmp);
        tmp->setF(F_tmp);
        tmp->setType(type_tmp);

        particles.push_back(tmp);

        /*
        string tmp_val;
        input_data_file >> tmp_val;
        r_tmp(0) = atof(tmp_val.c_str());
        input_data_file >> tmp_val;
        r_tmp(1) = atof(tmp_val.c_str());
        input_data_file >> tmp_val;
        r_tmp(2) = atof(tmp_val.c_str());
        input_data_file >> tmp_val;
        v_tmp(0) = atof(tmp_val.c_str());
        input_data_file >> tmp_val;
        v_tmp(1) = atof(tmp_val.c_str());
        input_data_file >> tmp_val;
        v_tmp(2) = atof(tmp_val.c_str());
        input_data_file >> tmp_val;
        F_tmp(0) = atof(tmp_val.c_str());
        input_data_file >> tmp_val;
        F_tmp(1) = atof(tmp_val.c_str());
        input_data_file >> tmp_val;
        F_tmp(1) = atof(tmp_val.c_str());
        cout << tmp_val << endl;
        cout << r_tmp << v_tmp << F_tmp << endl;
        /*
        double v1; double v2;
        input_data_file >> v1;//r_tmp(0);
        input_data_file >> v2;//r_tmp(1);
        input_data_file >> r_tmp(2);
        input_data_file >> v_tmp(0);
        input_data_file >> v_tmp(1);
        input_data_file >> v_tmp(2);
        input_data_file >> F_tmp(0);
        input_data_file >> F_tmp(1);
        input_data_file >> F_tmp(2);
        cout << type_tmp << endl;
        cout << v1 << " " << v2 << endl;
        cout << r_tmp << endl;
        cout << v_tmp << endl;
        cout << F_tmp << endl;
        */
    }
    //cout << "exiting test MDSystem::createParticlesStateFile()" << endl;
    //exit(1);


}

void MDSystem::fillCells()
{
    for (unsigned int m = 0; m<particles.size(); m++) {
        int i = (int) (particles[m]->r(0)/l);
        int j = (int) (particles[m]->r(1)/l);
        int k = (int) (particles[m]->r(2)/l);
        cells[i][j][k]->add(particles[m]);
        cout << "Adding particle to cell " << i << " " << j << " " << k << endl;
    }
    for (int i = 0; i<Nx; i++) {
        for (int j = 0; j<Ny; j++) {
            for (int k = 0; k<Nz; k++) {
                cout << cells[i][j][k]->size() << endl;
            }
        }
    }
}

void MDSystem::fillCellsAlternate()
{
    for (int i = 0; i<Nx; i++) {
        for (int j = 0; j<Ny; j++) {
            for (int k = 0; k<Nz; k++) {
                for (unsigned int m = 0; m<particles.size(); m++) {
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
                        //cout << "Adding particle to cell " << i << " " << j << " " << k << endl;
                    }
                }
            }
        }
    }
}

void MDSystem::setVelocities()
{
    for (unsigned int i = 0; i<particles.size(); i++) {
        switch(v_dist) {
            case NORMAL:
                particles[i]->setV(sqrt(T)*randn(3));
            case UNIFORM:
                particles[i]->setV(2*sqrt(T)*(randu(3)-ones(3)));
        }
    }
    // Removing system drift.
    double vx_mean; double vy_mean; double vz_mean; int n = particles.size();
    for (unsigned int i = 0; i<particles.size(); i++) {
        vx_mean += particles[i]->v[0]/n;
        vy_mean += particles[i]->v[1]/n;
        vz_mean += particles[i]->v[2]/n;
    }
    for (unsigned int i = 0; i<particles.size(); i++) {
        particles[i]->v[0] -= vx_mean;
        particles[i]->v[1] -= vy_mean;
        particles[i]->v[2] -= vz_mean;
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
    //"Problem here"
    //cout << "Started calculating forces" << endl;
    setPositionsPeriodic();
    updateCells();
    //"/end Problem Here!"
    vec3 correction;
    for (int i = 0; i<Nx; i++) {
        //cout<< " I =  " << i << endl;
        for (int j = 0; j<Ny; j++) {
            for(int k = 0; k<Nz; k++) {
                //cout << cells[i][j][k]->size();
                for (int m = 0; m<cells[i][j][k]->particles.size(); m++) {
                    cells[i][j][k]->particles[m]->F.zeros();
                    cells[i][j][k]->particles[m]->Ep = 0;
                    cells[i][j][k]->particles[m]->p_contribution = 0;

                // Calculate force on each particle from neighbor cell particles
                    for (int ii = -1; ii<=1; ii++) {
                        for (int jj = -1; jj<=1; jj++) {
                            for (int kk = -1; kk<=1; kk++) {
                                int iii = (i+ii+Nx)%Nx;
                                int jjj = (j+jj+Ny)%Ny;
                                int kkk = (k+kk+Nz)%Nz;
                                //cout << iii << jjj << kkk << endl;
                                correction(0) = -L*((i+ii)==-1) + L*(i+ii==Nx);
                                correction(1) = -L*((j+jj)==-1) + L*(j+jj==Ny);
                                correction(2) = -L*((k+kk)==-1) + L*(k+kk==Nz);
                                for (int mm = 0; mm<cells[iii][jjj][kkk]->particles.size(); mm++) {
                                    if (!((ii==0) && (jj==0) && (kk==0) && (mm==m))) {
                                        cells[i][j][k]->particles[m]->F = cells[i][j][k]->particles[m]->F +
                                            force->calculate(cells[i][j][k]->particles[m], cells[iii][jjj][kkk]->particles[mm], correction);
                                        cells[i][j][k]->particles[m]->Ep =cells[i][j][k]->particles[m]->Ep +
                                            0.5*force->energy(cells[i][j][k]->particles[m], cells[iii][jjj][kkk]->particles[mm], correction);
                                        cells[i][j][k]->particles[m]->p_contribution =
                                            cells[i][j][k]->particles[m]->p_contribution +
                                            0.5*force->pressure(cells[i][j][k]->particles[m], cells[iii][jjj][kkk]->particles[mm], correction);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            //cout << "j= " << j << endl;
        }
        //cout << "i= " << i << endl;
    }
   // cout << "Ended calculationg forces" << endl;
}

void MDSystem::setPositionsPeriodic()
// Cubic system is hardcoded here
{
    for (unsigned int m = 0; m<particles.size(); m++) {
        if (particles[m]->r(0)<0) {
            particles[m]->r(0) = particles[m]->r(0) + L;
            particles[m]->r_correction(0) = particles[m]->r_correction(0)-L;
        }
        if (particles[m]->r(0)>=L) {
            particles[m]->r(0) = particles[m]->r(0) - L;
            particles[m]->r_correction(0) = particles[m]->r_correction(0)+L;
        }
        if (particles[m]->r(1)<0) {
            particles[m]->r(1) = particles[m]->r(1) + L;
            particles[m]->r_correction(1) = particles[m]->r_correction(1)-L;
        }
        if (particles[m]->r(1)>=L) {
            particles[m]->r(1) = particles[m]->r(1) - L;
            particles[m]->r_correction(1) = particles[m]->r_correction(1)+L;
        }
        if (particles[m]->r(2)<0) {
            particles[m]->r(2) = particles[m]->r(2) + L;
            particles[m]->r_correction(2) = particles[m]->r_correction(2)-L;
        }
        if (particles[m]->r(2)>=L) {
            particles[m]->r(2) = particles[m]->r(2) - L;
            particles[m]->r_correction(2) = particles[m]->r_correction(2)+L;
        }

    }
}

void MDSystem::updateCells()
{
    int counter = 0;
    for (int i = 0; i<Nx; i++)  {
        //cout << i << endl;
        for (int j = 0; j<Ny; j++) {
            for (int k = 0; k<Nz; k++) {
                unsigned int m = 0;
                //cout << k << endl;
                while (m < cells[i][j][k]->particles.size()) {
                    //cout << cells[i][j][k]->particles.size();
                    //cout << m << endl;
                    //cout << m << endl;
                //(int m = 0; m < cells[i][j][k]->particles.size(); m++) {
                    if (!belongToCell(cells[i][j][k]->particles[m], i, j, k)) {
                        putInCell(cells[i][j][k]->pop(m));
                        m --;
                        counter ++;
                        //cout << m << endl;
                    }
                    m++;
                }
            }
        }
    }
    cout << counter << " particles changed cells" << endl;
}

void MDSystem::createCells()
{
    Nx = (int) L/r_crit;
    Ny = (int) L/r_crit;
    Nz = (int) L/r_crit;
    l = L/Nx;
    cout << "l = " << l << endl;
    cout << "Initializing system with " << Nx <<" x "<<Ny<<" x "<< Nz << " neighbor cells" << endl;
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
}

bool MDSystem::belongToCell(Particle* p, int i, int j, int k)
{
    double lx = i*l; double ly = j*l; double lz = k*l;
    return (p->r(0)>=lx && p->r(0)<lx+l && p->r(1)>=ly && p->r(1)<ly+l && p->r(2)>=lz && p->r(2)<lz+l);
}

void MDSystem::putInCell(Particle* p)
{
    int i = (int) (p->r(0)/l);
    int j = (int) (p->r(1)/l);
    int k = (int) (p->r(2)/l);
    if (i<0 || i>=Nx || j<0 || j>=Ny || k<0 || k>=Nz) {
        cout << "Trying to put particle in cell (" << i << ", " << j << ", " << k <<")" << endl;
        cout << "This is illegal" << endl;
        exit(1);
    }
    cells[i][j][k]->add(p);
}



void MDSystem::outputVMD()
{
    ostringstream tmp; tmp << particles.size() << "\n" << "comment" << "\n";
    output.VMD(tmp.str());
    for (unsigned int m = 0; m<particles.size(); m++) {
        output.VMD(particles[m]->VMDString());
    }
}

void MDSystem::outputAll()
{
    outputVMD();
}

void MDSystem::outputStateVMD()
{
    out_state.open((outPath + state_file_name));
    ostringstream tmp; tmp << particles.size() << "\n" << "comment" << "\n";
    out_state.VMD(tmp.str());
    for (unsigned int m = 0; m<particles.size(); m++) {
        out_state.VMD(particles[m]->VMDString());
    }
    out_state.close();
}




#include "measurements.h"

Measurements::Measurements(MDSystem* _system)
{
    system = _system;
    filenameMeasures = "measures.dat";
    outfileMeasures.open((system->outPath+filenameMeasures).c_str());
    cout << (system->outPath+filenameMeasures).c_str() <<endl;
    outfileMeasures << "% t " << "n_t " << "T " << "Etot " << "Ep " << "Ek " << "p " << endl;
    t = 0;
    T = 0;
    p = 0;
    Ek = 0;
    Ep = 0;
    Etot = 0;
    n_t = 0;

    particles = system->particles;
    L = system->L;
    V = L*L*L;
    num_particles = particles.size();

}

Measurements::~Measurements()
{
    outfileMeasures.close();
}

void Measurements::measureAll(double _t, int _n_t)
{
    measureEk();
    measureEp();
    measureEtot(); // Etot after Ek, Ep
    measureT(); // T after Ek
    measurep(); // p after all others
    t = _t;
    n_t = _n_t;
}

void Measurements::measureEk()
{
    Ek = 0;
    for (unsigned int i = 0; i<particles.size(); i++) {
        Ek += particles[i]->getEk();
    }
}

void Measurements::measureEp()
{
    vec3 offset;
    offset.zeros();
    Ep = 0;
    for (unsigned int i = 0; i<particles.size(); i++) {
        Ep += particles[i]->getEp();
    }
}

void Measurements::measureEtot()
{
    Etot = Ek+Ep;
}

void Measurements::measurep()
{
    double p_contribution = 0;
    for (unsigned int i = 0; i<particles.size(); i++) {
        p_contribution += particles[i]->getp_contribution();
    }
    p = num_particles/V*T + 1.0/(3*V)*p_contribution;
}

void Measurements::measureT()
{
    T = 2.0/3.0*Ek/particles.size();
}

void Measurements::outputAll()
{
    outfileMeasures << t << " " << n_t << " " << T << " " << Etot << " " << Ep << " " << Ek << " " << p << " " << endl;
}





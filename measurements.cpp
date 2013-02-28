#include "measurements.h"

Measurements::Measurements(MDSystem* _system)
{
    filenameMeasures = "/scratch/henriasv/NumericalData/FYS4460/test7/measures.dat";
    outfileMeasures.open(filenameMeasures.c_str());
    outfileMeasures << "% t " << "n_t " << "T " << "Etot " << "Ep " << "Ek " << "p " << endl;
    t = 0;
    T = 0;
    p = 0;
    Ek = 0;
    Ep = 0;
    Etot = 0;
    n_t = 0;
    system = _system;
    particles = system->particles;

}

void Measurements::measureAll(double _t, int _n_t)
{
    measureEk();
    measureEp();
    measureEtot();
    measurep();
    measureT();
    t = _t;
    n_t = _n_t;
}

void Measurements::measureEk()
{
    Ek = 0;
    for (int i = 0; i<particles.size(); i++) {
        Ek += particles[i]->getEk();
    }
}

void Measurements::measureEp()
{
    vec3 offset;
    offset.zeros();
    Ep = 0;
    for (int i = 0; i<particles.size(); i++) {
        for(int j = i+1; j<particles.size(); j++) {
            Ep += system->force->energy(particles[i], particles[j], offset);
        }
    }
}

void Measurements::measureEtot()
{
}

void Measurements::measurep()
{
}

void Measurements::measureT()
{
}

void Measurements::outputAll()
{
    outfileMeasures << t << " " << n_t << " " << T << " " << Etot << " " << Ep << " " << Ek << " " << p << " " << endl;
}





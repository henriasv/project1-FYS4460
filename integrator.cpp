#include "integrator.h"

Integrator::Integrator(MDSystem* _system, Config &cfg)
{

    t = 0;
    dt = 0.05;
    T = 8;
    system = _system;
    measure = new Measurements(system);
    particles = system->particles;
}

void Integrator::integrate()
{
    int counter = 0;
    system->calculateForces();
    for(double t_cnt = t; t_cnt<T; t_cnt+= dt) {
        step();
        measure->measureAll(t_cnt, counter);
        measure->outputAll();
        system->outputAll();
        system->checkNumParticles();
        cout << t_cnt << " / " << T << endl;
        counter += 1;
    }

}

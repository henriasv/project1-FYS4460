#include "integrator.h"

Integrator::Integrator(MDSystem* _system, Config &cfg)
{
    t = 0;
    dt = 0.005;
    T = 2;
    system = _system;
    particles = system->particles;
}

void Integrator::integrate()
{
    system->calculateForces();
    for(double t_cnt = t; t_cnt<T; t_cnt+= dt) {
        step();
        system->outputAll();
        cout << t_cnt << " / " << T << endl;
    }

}

#include "velocityverlet.h"

VelocityVerlet::VelocityVerlet(MDSystem* _system, Config* cfg) : Integrator(_system, cfg)
{
}

void VelocityVerlet::step()
{
    //cout << "In VelocityVerlet::step()" << endl;
    for (unsigned int m = 0; m<particles.size(); m++) {
        particles[m]->v = particles[m]->v + particles[m]->F*dt/2;
        particles[m]->r = particles[m]->r + particles[m]->v*dt;
    }
    system->calculateForces();
    for(unsigned int m = 0; m<particles.size(); m++) {
        particles[m]->v = particles[m]->v + particles[m]->F*dt/2;
    }
}


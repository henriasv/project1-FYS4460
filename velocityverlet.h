#ifndef VELOCITYVERLET_H
#define VELOCITYVERLET_H

#include "integrator.h"
#include "particle.h"
#include "mdsystem.h"

class VelocityVerlet : public Integrator
{
public:
    VelocityVerlet(MDSystem* _system, Config* cfg);
    virtual void step();
};

#endif // VELOCITYVERLET_H

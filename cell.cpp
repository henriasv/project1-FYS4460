#include "cell.h"

Cell::Cell(vec3 c)
{
    corner = c;
}

void Cell::add(Particle* p)
{
    particles.push_back(p);
}

Particle* Cell::pop(int i)
{
    Particle* p = particles[i];
    particles.erase(particles.begin() + i);
    return p;
}


int Cell::size()
{
    return particles.size();
}

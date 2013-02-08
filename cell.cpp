#include "cell.h"

Cell::Cell(vec3 c)
{
    corner = c;
}

void Cell::add(Particle * p)
{
    particles.push_back(p);
}


int Cell::size()
{
    return particles.size();
}

#ifndef CELL_H
#define CELL_H

#include "particle.h"
#include <vector>

using namespace std;

class Cell
{
public:
    Cell(vec3 corner);
    vector <Particle*> particles;
    void add(Particle*);
    Particle* pop();
    int size();

    vec3 corner;
};

#endif // CELL_H

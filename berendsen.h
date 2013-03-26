#ifndef BERENDSEN_H
#define BERENDSEN_H

#include "thermostat.h"

class Berendsen : public Thermostat
{
public:
    Berendsen(double, double);
    virtual double calculate(double T, double dt);
};

#endif // BERENDSEN_H

#include "berendsen.h"
#include <cmath>
#include <iostream>

Berendsen::Berendsen(double T_bath, double tau) : Thermostat(T_bath, tau)
{
}

double Berendsen::calculate(double T, double dt)
{

    return sqrt(1+1.0/tau*(T_bath/T-1.0));

}

#include "dummythermostat.h"

DummyThermostat::DummyThermostat() : Thermostat(0, 0)
{
}

double DummyThermostat::calculate(double, double)
{
    return 1;
}


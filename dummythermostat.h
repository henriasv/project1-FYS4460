#ifndef DUMMYTHERMOSTAT_H
#define DUMMYTHERMOSTAT_H

#include "thermostat.h"

class DummyThermostat : public Thermostat
{
public:
    DummyThermostat();
    virtual double calculate(double, double);
};

#endif // DUMMYTHERMOSTAT_H

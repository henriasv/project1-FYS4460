#ifndef THERMOSTAT_H
#define THERMOSTAT_H

class Thermostat
{
public:
    Thermostat(double T_bath, double tau);
    virtual double calculate(double T, double dt) = 0;

    double T_bath;
    double tau;
};

#endif // THERMOSTAT_H

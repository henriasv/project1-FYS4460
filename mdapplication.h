#ifndef MDAPPLICATION_H
#define MDAPPLICATION_H

#include "mdsystem.h"
#include "integrator.h"
#include <iostream>
//#include <libconfig.h++>
#include "velocityverlet.h"

using namespace std;
class Config;

class MDApplication
{
public:
    MDApplication();
    void run();

    string outFileVMD;

    Config* cfg;
    MDSystem* system;
    Integrator* integrator;
};

#endif // MDAPPLICATION_H

#ifndef MDAPPLICATION_H
#define MDAPPLICATION_H

#include "mdsystem.h"
#include "integrator.h"
#include <iostream>
#include "velocityverlet.h"

using namespace std;

class MDApplication
{
public:
    MDApplication(string config_path);
    void run();

    string outFileVMD;

    Config* cfg;
    MDSystem* system;
    Integrator* integrator;
};

#endif // MDAPPLICATION_H

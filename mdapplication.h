#ifndef MDAPPLICATION_H
#define MDAPPLICATION_H

#include "mdsystem.h"

using namespace std;

class MDApplication
{
public:
    MDApplication();
    void run();

    MDSystem* system;
};

#endif // MDAPPLICATION_H

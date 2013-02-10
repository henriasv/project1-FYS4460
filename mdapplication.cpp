#include "mdapplication.h"


MDApplication::MDApplication()
{
    system = new MDSystem();
    integrator = new VelocityVerlet(system, cfg);
    cout << "Created MDSystem" << endl;
    system->outputAll();
    integrator->integrate();
    delete system;
}

void MDApplication::run()
{
    cout << "Called MDApplication::run()" << endl;
}

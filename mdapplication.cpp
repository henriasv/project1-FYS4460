#include "mdapplication.h"
#include <iostream>


MDApplication::MDApplication()
{
    system = new MDSystem();
    cout << "Created MDSystem" << endl;
}

void MDApplication::run()
{
    cout << "Called MDApplication::run()" << endl;
}

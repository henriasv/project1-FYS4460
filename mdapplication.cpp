#include "mdapplication.h"
#include <libconfig.h++>

using namespace libconfig;

MDApplication::MDApplication(string config_path)
{
    cfg = new Config;
    cout << "Created Config object" << endl;
    cout << "Trying to load config from:" << endl << config_path << endl;
    cfg->readFile(config_path.c_str());

    // Creating output directory
    string path, folder, fullpath;
    cfg->lookupValue("settings.output_path", path);
    string mkdir_cmd = "mkdir -v ";
    std::system((mkdir_cmd+path).c_str());

    system = new MDSystem(cfg);
    cout << "Created MDSystem" << endl;
    integrator = new VelocityVerlet(system, cfg);
    cout << "created integrator" << endl;
}

void MDApplication::run()
{
    cout << "Called MDApplication::run()" << endl;

    system->outputAll();
    cout << "integrator->integrate()" << endl;
    integrator->integrate();
    delete system;
    delete integrator;
}

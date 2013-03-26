#include "integrator.h"
#include "berendsen.h"
#include "dummythermostat.h"


Integrator::Integrator(MDSystem* _system, Config* cfg)
{

    t = cfg->lookup("settings.t");
    dt = cfg->lookup("settings.dt");
    T = cfg->lookup("settings.T");
    temperature_th = cfg->lookup("system.temperature");
    tau = cfg->lookup("system.thermostat.tau");
    system = _system;
    measure = new Measurements(system);
    particles = system->particles;

    int thermostat_choice = cfg->lookup("system.thermostat.thermostat");
    switch (thermostat_choice) {
        case NONE:
            thermostat = new DummyThermostat;
            break;
        case BERENDSEN:
            thermostat = new Berendsen(temperature_th, tau);
    }
}

Integrator::~Integrator()
{
    delete measure;
}

void Integrator::integrate()
{
    cout << "Starting integration loop" << endl;
    int counter = 0;
    system->calculateForces();

    for(double t_cnt = t; t_cnt<T; t_cnt+= dt) {
        step();
        measure->measureAll(t_cnt, counter);
        thermostatAction(dt);
        measure->outputAll();
        system->outputAll();
        system->checkNumParticles();
        cout << t_cnt << " / " << T << endl;
        counter += 1;
    }
    system->outputStateVMD();

}

void Integrator::thermostatAction(double dt_th)
{
    for (unsigned int i = 0; i<particles.size(); i++) {
        particles[i]->v = thermostat->calculate(measure->T, dt_th)*particles[i]->v;
    }
}

from pylibconfig import Config
import numpy as np
import os

class ConfigPusher:
	"""
	Changes the cfg file to match the specified choices for an MD-simulation. The cfg files
	gotten from this class should be run in series, and each new simulation should take the last state
	of the preceding simulation as input.
	"""
	def __init__(self, config, outpath):
		self.path = outpath;
		self.config = config;
		self.counter = 0;
		self.num_particles = 0;

	def initialize(self, T = 1, dt = 0.002, r_crit = 3.0, nfcc = 8, temperature = 1, v_dist = 0 ):
		self.b = self.config.value("system.initialization.fcc.argon.b")[0]
		self.config.setValue("settings.sim_type", 0)
		self.config.setValue("settings.t", 0.0)
		self.config.setValue("settings.T", float(T))
		self.config.setValue("settings.dt", float(dt))
		self.config.setValue("settings.r_crit", float(r_crit))
		self.config.setValue("system.temperature", float(temperature));
		self.config.setValue("system.thermostat.thermostat", 0)
		self.config.setValue("system.initialization.fcc.NxFCC", nfcc)
		self.config.setValue("system.initialization.fcc.NyFCC", nfcc)
		self.config.setValue("system.initialization.fcc.NzFCC", nfcc)
		self.config.setValue("system.initialization.state.L", nfcc*self.b)
		self.config.setValue("system.initialization.fcc.v_dist", v_dist)
		self.num_particles = 4 * nfcc**3
		self.config.setValue("system.initialization.state.num_particles", self.num_particles)

		self.writeFile()

	def thermalize(self, T = 1.0, tau = 10.0, temperature = False, thermostat = False):
		self.config.setValue("settings.sim_type", 1)
		self.config.setValue("system.thermostat.tau", tau)

		if temperature:
			self.config.setValue("system.temperature", float(temperature))
		if thermostat:
			self.config.setValue("system.thermostat.thermostat", thermostat)
		else:
			self.config.setValue("system.thermostat.thermostat", 1)

		self.timeIncrement(T);
		self.writeFile();

	def release(self, T=1):
		self.config.setValue("system.thermostat.thermostat", 0);

		self.timeIncrement(T);
		self.writeFile()

	def timeIncrement(self, T=1):
		t = (self.config.value("settings.T"))[0]
		T_out = t + T;
		self.config.setValue("settings.t", float(t))
		self.config.setValue("settings.T", float(T_out))

	def writeFile(self):
		self.config.setValue("settings.input_path", self.config.value("settings.output_path")[0]);
		self.config.setValue("settings.sim_name", "mdsim%.4d" % self.counter)
		self.config.setValue("settings.output_path", self.path + self.config.value("settings.sim_name")[0] + "/");
		os.makedirs(self.config.value("settings.output_path")[0]);
		self.config.writeFile(self.config.value("settings.output_path")[0] +"mdsim%.4d.cfg" % self.counter)
		self.counter += 1;

	def set_potential(self, p = 'lennard_jones'):
		if p == 'lennard_jones':
			self.config.setValue("system.potential", 0)
		else:
			print "No support for potential different from Lennard jones ('lennard_jones')"

inPath = "/home/henrik/Dropbox/Henrik/Emner/FYS4460/project1/config/"
outPath = "/home/henrik/NumericalData/FYS4460/2048_diffusion_long6/"

config = Config()
config.readFile(inPath+"std_cfg.cfg")

cp = ConfigPusher(config, outPath)

for temp in np.linspace(3.0, 10.0, 4):
	cp.initialize(nfcc=8, T=0.5, temperature = temp*2*3, v_dist = 0)
	cp.thermalize(T = 2, temperature=temp, tau = 10.0)
	cp.release(T=6.0)

"""
cp.initialize(nfcc = 8, T=0.5, temperature = 5.0, v_dist = 0)
for temp in [5.0, 4.5, 4.0, 3.5, 3.0, 3.5, 3.0, 2.5, 2.0, 1.5, 1.0, 0.5, 0.25, 0.125, 0.05, 0.01, 0.0]:
	cp.thermalize(temperature=temp, tau = 10.0)
	cp.release()
	
cp.thermalize(temperature=4.0, tau = 10.0)
cp.release()
cp.thermalize(temperature = 3.5, tau = 10.0)
cp.release()
cp.thermalize(temperature = 3.0, tau = 10.0)
cp.release()
cp.thermalize(temperature = )
"""


# Config file for MD project in FYS4460
"""
version = "0.1";

system:
{
	potential = 0;
	temperature = 0.0;

	initialization:
	{
		
			
			fcc:
			{
			NxFCC = 0;
			NyFCC = 0;
			NzFCC = 0;		
			v_dist = 0;

				argon:
				{
					b = 1.547136563876652;
				
				};
			};

			state:
			{
				num_particles = 0;
			}
		};
	thermostat:
	{
		thermostat = 0;
		tau = 0.0;
	};
};

settings:
{
	sim_type = 0;
    dt = 0.0;
    t = 0.0;
    T = 0;
	r_crit = 0;
	output_path = "";
	sim_name = "";
	output_freq = 1;
};
"""
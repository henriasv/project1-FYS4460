# calculate the g(r)-function

from pylibconfig import Config
import numpy as np
import matplotlib.pyplot as plt
import sys

def minimumDistance(r1, r2, L):
	r_diff = r1-r2;
	for i in xrange(3):
		r_diff[i] = min(abs(r_diff[i]), L-abs(r_diff[i]))
	return np.sqrt(np.dot(r_diff, r_diff))	

path = "/home/henrik/NumericalData/FYS4460/2048_longrun/"
name = "mdsim0007"

infile_vmd = open(path+name +"/" +"out.xyz")
config = Config()
config.readFile(path+name+"/"+name+".cfg")
L = config.value("system.initialization.state.L")[0]
V = L**3;
num_particles = config.value("system.initialization.state.num_particles")[0]
#num_particles = 10

particle_positions = []

n_bins = 1000;
dr = L/(2*n_bins-1);
distance_densities = np.zeros(n_bins)
distances = np.linspace(dr, L/2+dr, n_bins)

cut1 = 2
cut2 = num_particles+2


for line in infile_vmd.readlines()[cut1:cut2]:
	tmp_list = line.split()
	print tmp_list
	particle_positions.append([float(tmp_list[i]) for i in range(1, 4, 1)])
particle_positions = np.asarray(particle_positions)

print particle_positions;

for i in range(0, num_particles, 1):
	print i
	j = i+1
	#print particle_positions[1, :]
	while(j<num_particles):
		#print i, " ",  j, " ", num_particles
		r_tmp = minimumDistance(particle_positions[i, :], particle_positions[j, :], L)
		#print r_diff_sq
		counter = n_bins-1
		r_distance = distances[counter]
		index = int(n_bins*r_tmp*2/L)
		#print index;
		try:
			distance_densities[index] += 1;
		except:
			pass;
		"""
		while r_diff_sq<r_distance*r_distance and counter >= 0:
			if (r_diff_sq+dr>r_distance*r_distance):
				distance_densities[counter] += 1;
				break;
			r_distance = distances[counter]
			counter -= 1
			"""
		j += 1

distance_densities = distance_densities/(4*np.pi*distances**2*dr*0.5*num_particles)*V/num_particles

_fontsize = 20;
in_T = float(raw_input("Provide temperature"))

plt.figure()
plt.plot(distances, distance_densities)

plt.xlabel(r"$\frac{r}{\sigma}$", fontsize = _fontsize)
plt.ylabel(r"$g(r)$", fontsize = _fontsize)
plt.title(r"Radial distribution function for argon at $T = %.1f T_0$" % in_T)
plt.show(block=False)

filename = raw_input("Filename for dataset: ")
fid = open(path+name+"/" + filename, 'w')
distance_densities.tofile(fid);

fid = open(path+name+"/" + "r_corr" + filename, 'w')
distances.tofile(fid)


raw_input("press enter")
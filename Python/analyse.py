# Script to analyse data from MD-simulations
import numpy as np
import matplotlib.pyplot as plt
import os, sys

try:
	path = sys.argv[1];
except IndexError:
	path = "/home/henrik/NumericalData/FYS4460/2048_longrun/"
	print "path not provided, using \n" + path

simname_tmp = [i for i in sorted(os.listdir(path))]
simname = [];

print simname_tmp
for name in simname_tmp:
	print path+name+"/out.xyz"
	if os.path.isfile(path+name+"/out.xyz"):
		simname.append(name)

print simname


fig1 = plt.figure(); fig2 = plt.figure(); fig3 = plt.figure(); fig4 = plt.figure(); fig5 = plt.figure()
fig6 = plt.figure(); fig7 = plt.figure(); fig8 = plt.figure()
for folder in simname:
	# File imports;
	general_file = open(path+folder+"/measures.dat", 'r')
	vmd_file = open(path+folder+"/out.xyz", 'r')

	tmp_str_all = general_file.readlines();
	format = tmp_str_all.pop(0).split();
	print format
	if (format[0] == '%'):
		format.pop(0);

# Defining lists
	for i in range(len(format)):
		exec(format[i] + "= []")

#Importing data to lists
	for line in tmp_str_all:
		tmp_array = line.split()
		for i in range(len(format)):
			exec(format[i]+'.append(float(tmp_array[i]))')

	for i in range(len(format)):
		exec(format[i] + '= np.asarray('+format[i]+')')

# Importing VMD data
	num_particles = int(vmd_file.readline())
	print num_particles
	data = vmd_file.readlines()[-num_particles:-1];
	v = np.zeros(num_particles)
	vx = np.zeros(num_particles)
	vy = np.zeros(num_particles)
	vz = np.zeros(num_particles)
	counter = 0;
	for line in data:
		try:
			tmp_str = line.split();
			v_tmp = np.asarray([float(tmp_str[i]) for i in range(4, 7, 1)])
			vx[counter] = v_tmp[0]; vy[counter] = v_tmp[1]; vz[counter] = v_tmp[2]
			v[counter] = np.sqrt(np.dot(v_tmp, v_tmp));
			counter += 1;
		
		except IndexError:
			break

	# Plot potential energy	
	plt.figure(fig1.number)
	plt.plot(t, Ep)
	plt.xlabel("tid")
	plt.ylabel("$E_p$")
	plt.title("Potential energy")

	# Plot kinetic energy
	plt.figure(fig2.number)
	plt.plot(t, Ek)
	plt.xlabel("tid")
	plt.ylabel("$E_p$")
	plt.title("Kinetic energy")

	# Plot total energy
	plt.figure(fig3.number)
	plt.plot(t, np.add(Ep,Ek))
	plt.xlabel("tid")
	plt.ylabel("$E_{tot}$")
	plt.title("Total energy")

	# plot temperature
	plt.figure(fig4.number)
	plt.plot(t, T)
	plt.xlabel("tid")
	plt.ylabel("$T$")
	plt.title("Temperature")

	# plot pressure
	plt.figure(fig6.number)
	plt.plot(t, p)

	# Plot velocity distribution at the end of each simulation
	plt.figure(fig5.number)
	plt.hist(v, bins=100, histtype="stepfilled");
	plt.xlabel("$|v|$");
	plt.ylabel("$N(v)$");
	plt.title("Speed distribution")

	# plot velocity distribution
	plt.figure(fig7.number)
	plt.hist(vx, bins=100, histtype="stepfilled")
	plt.hist(vy, bins=100, histtype="stepfilled")
	plt.hist(vz, bins=100, histtype="stepfilled")
	plt.xlabel("$v_i$");
	plt.ylabel("$N(v)$");
	plt.title("Velocity distribution")
	plt.legend(["$v_x$", "$v_y$", "$v_z$"])

	# plot PT
	plt.figure(fig8.number)
	plt.plot(T, p, "--");
	plt.xlabel("T");
	plt.ylabel("P");
	plt.title("PT-diagram for argon")

	plt.show(block=False)

raw_input("Press enter");
	
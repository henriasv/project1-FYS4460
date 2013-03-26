# Estimate diffusion constant
import numpy as np
import matplotlib.pyplot as plt
from pylibconfig import Config

# Short diffusion run
"""
path = "/home/henrik/NumericalData/FYS4460/2048_diffusion3/"
names = ["mdsim0002", "mdsim0005"]#, "mdsim0008"]#, "mdsim0011", "mdsim0014", "mdsim0017", "mdsim0020", "mdsim0023"]#, "mdsim0005"]
"""
# Long diffusion run

path = "/home/henrik/NumericalData/FYS4460/2048_diffusion_long6/"
names = ["mdsim0002", "mdsim0005"]


fig1 = plt.figure(); fig1ax = plt.axes(); fig2 = plt.figure(); fig2ax = plt.axes();
legendstring = [];
for name in names:
	infileVMD = open(path+name+"/out.xyz")
	infileData = open(path+name+"/measures.dat")
	config = Config()
	config.readFile(path+name+"/"+name+".cfg")
	temperature = config.value("system.temperature")[0]
	num_particles = int(infileVMD.readline());
	print "Num particles = ", num_particles
	measures = infileData.readlines()
	vmd = infileVMD.readlines();
	vmd = vmd[1:-1]
	n_t = int(len(measures)-1);
	t = np.zeros(n_t)
	for i in range(n_t):
		tmp = measures[i+1].split()
		t[i] = float(tmp[0]);
	print "Num timesteps = ", n_t
	particle_square_displacements = np.zeros((num_particles, n_t))
	particle_initial_positions = np.zeros((num_particles, 3));

	for i in range(num_particles):
		tmp = vmd[i].split();
		for j in range(3):
			particle_initial_positions[i,j] = float(tmp[j+1])+float(tmp[j+10])
			#print particle_initial_positions[i, :];
	#particle_initial_positions = particle_initial_positions.transpose();


	# Read data
	for i in range(n_t):
		if (i%10 == 0):
			print i

		inarray = np.array(vmd[i*(num_particles+2):i*(num_particles+2)+num_particles])
		inarray = np.array(map(np.string_, inarray))
		tmp = np.zeros((num_particles, 12))
		inarray = np.char.strip(inarray, 'A')
		inarray = np.char.strip(inarray, 'r')
		for j in xrange(num_particles):
			tmp[j] = np.fromstring(inarray[j], sep = " ") #tmp.split();
		tmp = np.float64(tmp);

		r_tmp = np.zeros((3, num_particles))
		#print np.shape(tmp[:, 8:11])
		#print np.shape(r_tmp)
		r_tmp = tmp[:, 0:3]+tmp[:, 9:12]
		#print r_tmp
		#print np.shape(r_tmp);
		r_diff = r_tmp-particle_initial_positions
		particle_square_displacement_tmp = r_diff*r_diff;
		particle_square_displacements[:, i] = np.sum(particle_square_displacement_tmp, axis=1)

	exp_square_displacement = np.zeros(n_t);
	for i in range(n_t):
		exp_square_displacement[i] = 1.0/float(num_particles)*np.sum(particle_square_displacements[:, i])

	polyrange = [2000, -1]
	p = np.polyfit(t[polyrange[0]:polyrange[1]], exp_square_displacement[polyrange[0]:polyrange[1]], 1)
	t_p = t[polyrange[0]::];
	y = np.polyval(p, t_p)
	est_D = p[0]/6.0;
	plt.figure(fig1.number)
	plt.plot(t, exp_square_displacement, label = r"$T=%.1f, D_{est} = %.3g$" % (temperature, est_D))
	plt.plot(t_p, y, 'r')
	plt.xlabel(r"$\frac{t}{t_0}$")
	plt.ylabel(r"$\langle r^2(t) \rangle$")
	plt.title("Mean square displacement and linear fits")

	plt.figure(fig2.number)
	for i in [10, 20, 40, 80, 160, 320]:
		try:
			plt.hist(particle_square_displacements[:, i], bins = 100)
		except:
			pass
	plt.show(block=False)

handles, labels = fig1ax.get_legend_handles_labels()
fig1ax.legend(handles, labels, loc=2)
plt.show(block=False)


raw_input("Press enter")
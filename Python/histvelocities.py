# Slider to look at velocities in time:

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button, RadioButtons
import sys

#import data:
path = "/home/henrik/NumericalData/FYS4460/2048_diffusion_long6/"
name = "mdsim0001/"
try:
	path = sys.argv[1]
except:
	pass

vmd_file = open(path+name+"out.xyz")

# Importing VMD data
data = vmd_file.readlines()
num_particles = int(data[0]);
n_t = int(len(data)/(num_particles+2))
v = np.zeros((n_t, num_particles))
vx = np.zeros((n_t, num_particles))
vy = np.zeros((n_t, num_particles))
vz = np.zeros((n_t, num_particles))
counter = 0;
for i in range(n_t):
	print i, "/" , n_t
	for j in range(num_particles):
		try:
			tmp_str = data[i*(num_particles+2) + j + 2].split();
			v_tmp = np.asarray([float(tmp_str[k]) for k in range(4, 7, 1)])
			vx[i, j] = v_tmp[0]; vy[i, j] = v_tmp[1]; vz[i, j] = v_tmp[2]
			v[i, j] = np.dot(v_tmp, v_tmp);
	
		except IndexError:
			print "IndexError"
"""
plt.hist(v[2, :], bins=20)
plt.show(block=False)
raw_input("press enter")
"""
ax = plt.subplot(111)
plt.subplots_adjust(left=0.25, bottom=0.25)
t = np.asarray(range(n_t));
time = 100;
print v[time, :]
hist, abcissa = np.histogram(v[time, :], bins=100)
print len(hist), len(abcissa)
print hist
l = plt.plot(abcissa[1::], hist, lw=2)[0]
axtime = plt.axes([0.25, 0.2, 0.65, 0.03]);
stime = Slider(axtime, 'Time', 0, n_t-1, valinit=0)
axtime.autoscale(enable=True)

def update(val):
	time = int(stime.val)
	hist, abcissa = np.histogram(v[time, :])
	l.set_ydata(hist)
	l.set_xdata(abcissa[1::])
	axtime.set_ylim(hist.min(), hist.max(), emit=True)
	axtime.set_xlim(abcissa.min(), abcissa.max(), emit=True)
	plt.title("Velocity distribution at timestep=%d" %time)
	plt.draw()

stime.on_changed(update)
plt.show();


"""

ax = plt.subplot(111)
plt.subplots_adjust(left=0.25, bottom=0.25)
t = np.arange(0.0, 1.0, 0.001)
a0 = 5
f0 = 3
s = a0*np.sin(2*np.pi*f0*t)
l, = plt.plot(t,s, lw=2, color='red')
plt.axis()

axcolor = 'lightgoldenrodyellow'
axfreq = plt.axes([0.25, 0.1, 0.65, 0.03], axisbg=axcolor)
axamp  = plt.axes([0.25, 0.15, 0.65, 0.03], axisbg=axcolor)

sfreq = Slider(axfreq, 'Freq', 0.1, 30.0, valinit=f0)
samp = Slider(axamp, 'Amp', 0.1, 10.0, valinit=a0)

def update(val):
    amp = samp.val
    freq = sfreq.val
    l.set_ydata(amp*np.sin(2*np.pi*freq*t))
    plt.draw()
sfreq.on_changed(update)
samp.on_changed(update)

resetax = plt.axes([0.8, 0.025, 0.1, 0.04])
button = Button(resetax, 'Reset', color=axcolor, hovercolor='0.975')
def reset(event):
    sfreq.reset()
    samp.reset()
button.on_clicked(reset)

rax = plt.axes([0.025, 0.5, 0.15, 0.15], axisbg=axcolor)
radio = RadioButtons(rax, ('red', 'blue', 'green'), active=0)
def colorfunc(label):
    l.set_color(label)
    plt.draw()
radio.on_clicked(colorfunc)

plt.show()
"""


# plot g(r) from data
import numpy as np
import matplotlib.pyplot as plt

path = "/home/henrik/NumericalData/FYS4460/2048_longrun/"
names = ["mdsim0000/g_r_fcc.bin", "mdsim0002/g_r_T_3.0.bin", "mdsim0007/g_r_T_0.11.bin"] 
abcissas = ["mdsim0000/r_corrg_r_fcc.bin", "mdsim0002/r_corrg_r_T_3.0.bin", "mdsim0007/r_corrg_r_T_0.11.bin"]

fig1 = plt.figure()
plt.title("Radial distribution functions for argon at different temperatures")
_fontsize = 14
for i in range(len(names)):
	g = np.fromfile(path+names[i])
	r = np.fromfile(path+abcissas[i])
	plt.figure(fig1.number)
	plt.plot(r, g/max(g));
	plt.legend(["FCC (T=0)", "T=3.0", "T=0.11"])
	plt.xlabel(r"$\frac{r}{\sigma}$", fontsize = _fontsize*1.5)
	plt.ylabel(r"$g(r)$ (maximum set to 1)", fontsize = _fontsize)
	plt.show(block=False)

raw_input("press enter")
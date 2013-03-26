# Script to run series of MD-simulations from one path
import sys, os, subprocess, time

path_to_exec = "/home/henrik/Dropbox/Henrik/Emner/FYS4460/Code/build-GCC_64bits/project1-FYS4460"

try:
	path = sys.argv[1]
except IndexError:
	path = "/home/henrik/NumericalData/FYS4460/2048_diffusion_long6/"
	print "Path to config tree not provided, trying to use \n" + path
	isContinue = ("y" == raw_input("Continue(y/n)"))
	if not isContinue:
		print "Ok, quitting"
		sys.exit(0)



for name in sorted(os.listdir(path)):
	if (name == "mdsim0005" or name == "mdsim0006" or name == "mdsim0007" or name == "mdsim0008" or name == "mdsim0009" or name == "mdsim0010" or name == "mdsim0011"):
		print path+name+"/"
		subprocess.call([path_to_exec, path+name+"/"+name+".cfg"])
		#time.sleep(2);
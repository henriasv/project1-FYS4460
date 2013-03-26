# Script to run MD-simulation
# If this script is called from a folder containing a config file, and the name of this config file is given as an argument, everything works fine!
import os

cfg_filename = "v01.cfg"; # sys.argv[1]
cwd = os.getcwd();
file_path = cfg_filename + "/" + cwd

print "Starting simulation from \n" + file_path
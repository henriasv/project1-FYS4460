% Script to analyse output from molecular dynmics program (Argon gas/crystal)
path = fullfile('/scratch', 'henriasv', 'NumericalData', 'FYS4460');
folder = 'state';
filename = 'measures.dat';
filenameVMD = 'out.xyz';

filepath = fullfile(path, folder, filename)
filepathVMD = fullfile(path, folder, filenameVMD)

[t, n_t, T, Etot, Ep, Ek, p] = textread(filepath, '%f %d %f %f %f %f %f', -1, 'commentstyle', 'matlab');
figure;
plot(t, Ek, '-*r');
hold on
plot(t, -Ep, '+-b');
plot(t, abs(Ek+Ep), '*-k');

[name, x, y, z, vx, vy, vz] = readVMD(filepathVMD);
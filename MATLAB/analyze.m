% Script to analyse output from molecular dynmics program (Argon gas/crystal)
path = fullfile('/scratch', 'henriasv', 'NumericalData', 'FYS4460')
folder = 'test5';
filename = 'measures.dat';

filepath = fullfile(path, folder, filename);

[t, n_t, T, Etot, Ep, Ek, p] = textread(filepath, '%f %d %f %f %f %f %f', -1, 'commentstyle', 'matlab');
figure;
plot(t, Ek);
hold on
plot(t, Ep);
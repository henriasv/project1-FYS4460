function [ name, x, y, z, vx, vy, vz ] = readVMD( filepath )
% readVMD Reads a VMD state file on the format:
% 'Atom name' x y z vx vy vz
isContinue = true;
fid = fopen(filepath);
name = {''}; x = [0]; y = [0]; z=[0]; vx = [0]; vy = [0]; vz = [0];
while isContinue
    str = textscan(fgets(fid), '%d');
    dummy = fgets(fid)
    for i=1:2048
        C = textscan(fgets(fid), '%s %f %f %f %f %f %f')
        %[name{i} x(i) y(i) z(i) vx(i) vy(i) vz(i)] 
        C = textscan(fgets(fid), '%s %f %f %f %f %f %f');
        name{i} = C{1};
        x(i) = C{2};
        y(i) = C{3};
        z(i) = C{4};
        vx(i) = C{5};
        vy(i) = C{6};
        vz(i) = C{7};
        
    end
    isContinue = false;
end
    


end


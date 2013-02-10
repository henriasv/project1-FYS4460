#ifndef OUTPUTMD_H
#define OUTPUTMD_H

#include <string>
#include <fstream>

using namespace std;

class OutputMD
{
public:
    OutputMD();
    ~OutputMD();
    void open(string);

    void VMD(string);

    // Filenames
    string VMDName;

    // Ofstreams
    ofstream outFileVMD;

};

#endif // OUTPUTMD_H

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
    void close();

    void VMD(string);

    // Ofstreams
    ofstream outFileVMD;

};

#endif // OUTPUTMD_H

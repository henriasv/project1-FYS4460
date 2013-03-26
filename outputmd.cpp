#include "outputmd.h"

OutputMD::OutputMD()
{
}

OutputMD::~OutputMD()
{
    outFileVMD.close();
}

void OutputMD::VMD(string s)
{
    outFileVMD << s;
}

void OutputMD::open(string path)
{
    // Creationg ofstreams
    outFileVMD.open((path).c_str());
}

void OutputMD::close()
{
    outFileVMD.close();
}

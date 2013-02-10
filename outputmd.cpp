#include "outputmd.h"

OutputMD::OutputMD()
{

    // Setting filenames
    VMDName = "/out.xyz";


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
    outFileVMD.open((path + VMDName).c_str());
}

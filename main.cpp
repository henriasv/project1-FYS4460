#include <iostream>
#include "mdapplication.h"

using namespace std;

int main(int argc, char **argv)
{
    string config_path = argv[1];
    MDApplication app(config_path);
    app.run();
    cout << "Hello World!" << endl;
    return 0;
}


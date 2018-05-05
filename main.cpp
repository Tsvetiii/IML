#include <iostream>
#include <cstring>
#include "IML.h"

using namespace std;

int main()
{
    std::string readFileName, writeFileName;
    cout<<"Please, enter filename to read from: ";
    cin>>readFileName;
    cout<<"Please, enter filename to write to: ";
    cin>>writeFileName;
    parser(readFileName, writeFileName);
    return 0;
}

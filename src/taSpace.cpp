#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <algorithm>
#include "TimberAllocation.h"

using namespace std;

namespace ta
{
void cSpace::rotateLWH()
{
    std::vector<int> vLWH { myLength, myWidth, myHeight };
    std::sort( vLWH.begin(), vLWH.end(),
               []( int& a, int& b)
    {
        return a > b;
    });
    myLength = vLWH[0];
    myWidth  = vLWH[1];
    myHeight = vLWH[2];

//    for( int i : vLWH )
//        std::cout << i <<" ";
//    std::cout << "\n";
}
}

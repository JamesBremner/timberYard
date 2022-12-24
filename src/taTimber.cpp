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
 int cTimber::ParseSpaceDelimited(
    const std::string& l )
{
    std::vector< std::string > token;
    std::stringstream sst(l);
    std::string a;
    while( getline( sst, a, ' ' ) )
        token.push_back( a );
    if( token.size() < 6 )
        throw std::runtime_error(" Error reading: " + l );
    myLength = atoi(token[1].c_str());
    myWidth = atoi(token[2].c_str());
    myHeight = atoi(token[3].c_str());
    myCount = atoi(token[4].c_str());
    myUserID = token[5];

    if( token[0] == "i" )
        return 0;
    else  if( token[0] == "d" )
        return 1;
    else
        throw std::runtime_error(" Error reading: " + l );
}

std::string cTimber::text()
{
    std::stringstream ss;
    ss <<  myLength <<" "<< myWidth <<" "<< myHeight <<" "<< myUserID;
    return ss.str();
}

void cTimber::pack( int l, int w, int h, timber_t stock )
{
    std::cout << "packing " << myUserID << " into " << stock->myUserID << "\n";
    myPacked = true;
    myLocL = l;
    myLocW = w;
    myLocH = h;
    myStock = stock;
    stock->used();
}


}

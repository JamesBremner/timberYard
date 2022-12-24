#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>
#include <vector>
#include <algorithm>
#include "TimberAllocation.h"

using namespace std;

int main( int argc, char* argv[] )
{
    cout << "TimberAllocation" << endl;

    if( argc != 2 )
    {
        std::cout << "Usage: TimberAllocation <path to instance file>\n";
        exit(1);
    }

    try
    {
        ta::cInstance I;

        // read problem instance file
        I.read( argv[1] );

        // sort orders into levels of the same height
        Levels( I );

        // allocate levels to stock
        LevelsToStock( I );

        // cut out orders from stock by level
        LevelCuts( I );

        ReturnToInventory( I );

        // display solution
        std::cout << I.textSolution();

        DisplayWastage( I );
    }
    catch( std::runtime_error& e )
    {
        std::cout << "exception: " << e.what() << "\n";
    }
    return 0;
}

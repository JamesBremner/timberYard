#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <wex.h>
#include "cGUI.h"
#include "TimberAllocation.h"

ta::cInstance I;

     void cGUI::draw(wex::shapes &S)
    {
        auto t = I.textSolution();
        S.text(t,{5,5,500,500});
    }

    void cGUI::menus()
    {
        wex::menubar mb(fm);

        myFileMenu = new wex::menu(fm);

        myFileMenu->append(
            "Open",
            [&](const std::string &title)
            {
                // prompt user
                wex::filebox fb(fm);
                fb.open();
                I.read( fb.path() );
                fm.update();
            });

        mb.append("File", *myFileMenu);
    }

main()
{
    cGUI theGUI(
              "Timber Yard",
              {50, 50, 1000, 500});
    return 0;
}

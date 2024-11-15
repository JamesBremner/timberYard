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
    switch( myView )
    {
        case eView::inventory:
            S.text(I.textInventory(),{5, 5, 500, 500});
            break;
        case eView::order:
            S.text(I.textOrder(),{5, 5, 500, 500});
            break;
        case eView::cuts:
            S.text(I.textCuts(),{5, 5, 500, 500});
            break;
    }
    // auto t = I.textSolution();
    // S.text(t, {5, 5, 500, 500});
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
            I.read(fb.path());
            I.solve();
            fm.update();
        });
    mb.append("File", *myFileMenu);

    myViewMenu = new wex::menu(fm);
    myViewMenu->append(
        "Inventory",
        [&](const std::string &title)
        {
            myView = eView::inventory;
            fm.update();
        });
    myViewMenu->append(
        "Order",
        [&](const std::string &title)
        {
            myView = eView::order;
            fm.update();
        });
    myViewMenu->append(
        "Cuts",
        [&](const std::string &title)
        {
            myView = eView::cuts;
            fm.update();
        });
    mb.append("View", *myViewMenu);
}

main()
{
    cGUI theGUI(
        "Timber Yard",
        {50, 50, 1000, 500});
    return 0;
}

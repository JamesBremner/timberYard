class cGUI
{
public:
    /** CTOR
     * @param[in] title will appear in application window title
     * @param[in] vlocation set location and size of appplication window
     *
     */
    cGUI(
        const std::string &title,
        const std::vector<int> &vlocation)
        : fm(wex::maker::make()),
        myView(eView::inventory)
    {
        fm.move(vlocation);
        fm.text(title);

        menus();

        fm.events().draw(
            [&](PAINTSTRUCT &ps)
            {
                wex::shapes S(ps);
                draw(S);
            });

        fm.show();
        fm.run();
    }

private:
    wex::gui &fm;
    wex::menu *myFileMenu;
    wex::menu *myViewMenu;
    enum class eView {
        order,
        inventory,
        cuts,
    };
    eView myView;

    void draw(wex::shapes &S);

    void menus();
};
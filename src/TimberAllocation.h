#pragma once

//#define USE_CS2LNW
#define USE_CS2Pack2

namespace ta
{

class cTimber;
typedef std::shared_ptr< cTimber > timber_t;
typedef std::vector< timber_t > timberv_t;


/// A 3D object with dimension and location
class cSpace
{
public:
    int myLength, myWidth, myHeight;    // dimensions
    int myLocL, myLocW, myLocH;


    cSpace( int L, int W, int H )
        : myLength( L ), myWidth( W ), myHeight{ H }
    {

    }
    bool fit( const cSpace& squeeze ) const
    {
        return ( squeeze.myLength <= myLength &&
                 squeeze.myLength <= myLength &&
                 squeeze.myHeight <= myHeight );
    }

    int size_horiz()
    {
        return myLength * myWidth;
    }
    /// rotate so that L, W, H are in decending size order
    void rotateLWH();
};

class cTimber : public cSpace
{
public:
    cTimber()
        : cSpace( 0, 0, 0 )
        , myCount( 1 )
        , myPacked( false )
        , myUsed( false )
    {

    }
    cTimber( int L, int W, int H )
        : cSpace( L, W, H )
        , myCount( 1 )
        , myPacked( false )
        , myUsed( false )

    {

    }
    int ParseSpaceDelimited(
        const std::string& l );

    /** Cut the order
        @param[in] l length position
        @param[in] w width position
        @param[in] k height position
        @param[in] stock timber from which order is cut
    */
    void pack( int l, int w, int h, timber_t stock );

    std::string text();

    bool isPacked() const
    {
        return myPacked;
    }

    void used( bool f = true )
    {
        myUsed = f;
    }
    bool isUsed() const
    {
        return myUsed;
    }

    // set the location of the top of the highest level cut
    void level( int h )
    {
        myLevel = h;
    }
    int level() const
    {
        return myLevel;
    }

    void usedbyLevel( bool f )
    {
        myUsedbyLevel = f;
    }
    bool isUsedbyLevel()
    {
        return myUsedbyLevel;
    }

    std::string myUserID;
    int myCount;

private:
    bool myPacked;      // true if an order that has been allocated
    timber_t myStock;   // if an allocated order, the stock allocated to
    bool myUsed;        // true if a stock that haveen used to cut orders
    int myLevel;         // the location of the top of the highest level cut
    bool myUsedbyLevel;  // true if stock has been allocated to current level
};

//class cInventory
//{
//public:
//    void clear();
//    //void add( timber_t t );
//    //void expandCount();
//    //std::string text();
//    //std::string textDetails();
//
//    /** Sort inventory into stock, sheets and scraps
//    @param[in] sheetHeight maximum sheet height
//    @param[in] scrapWidth maximum scrap width
//
//    This will allow inentory returns, if present,
//    to be optimised.
//
//    tid7
//    */
//    //void sortInventory( int sheetHeight, int scrapWidth );
//
//public:
//    timberv_t myInventory;      /// inentory ( all timbers labeled 'i' in the instance file )
////    timberv_t myScrap;          /// inventory fpr 1D cutting
////    timberv_t mySheet;          /// inventory for 2D cutting
//    timberv_t myStock;          /// invemtory for 3D cutting
//};
class cCut
{
public:
    timber_t myStock;
    char myDirection;
    int myLocation;
    int myLevelHeight;
    cCut( timber_t stock, char D, int loc, int levelHeight )
        : myStock( stock )
        , myDirection( D )
        , myLocation( loc )
        , myLevelHeight( levelHeight )
    {

    }
    std::string text();
};

/// orders that have the same height
class cLevel
{
public:
    timberv_t myOrder;      // orders
    timber_t  myStock;      // stock allocated to level

    cLevel()
        : myAreaUsed( 0 )
    {

    }

    /** remove orders that have been packed
        @return 0: none packed, 1: some packed, 2: all packed
    */
    int removePacked();

    std::string text() const;
    int height() const
    {
        return myOrder[0]->myHeight;
    }
    int size() const
    {
        return (int) myOrder.size();
    }
    void use( timber_t order )
    {
        myAreaUsed += order->myLength * order->myWidth;
    }
    /** Volume wasted when level cut from stock
        @return volume wasted

        This calculates wastage only for the currently stacked level
        so this needs to be called for each stacked level
    */
    int wastage() const;

private:
    int myAreaUsed;
};

class cInstance
{
public:
    void read(
        const std::string& fname );

    std::string textProblem();
    std::string textSolution();

    /** Expand multiple timbers
        @param[in] tv vector of timbers
    */
    static void expandCount( timberv_t& tv );


    void addStock( timber_t t );
    void addOrder( timber_t t );
    void addUnpacked( timberv_t& unpacked );

    /** Expand multiple timbers
    @param[in] tv vector of timbers
    */
    void expandCount();

    /// Number of orders that could not fit
    int unPackedCount() const
    {
        return (int)myUnpacked.size();
    }

    bool isEveryIDUnique();

    /** Record allocation in solution
        @param[in] order
        @param[in] stock
    */
    void allocate( timber_t order, timber_t stock );

    void add( const cCut& cut )
    {
        myCut.push_back( cut );
    }
    int cutListSize() const
    {
        return (int)myCut.size();
    }
    /** cut position along orthogonal axis
        @param[in] index of cut in cut list
        @return position, -1 on error
    */
    int cutListPosition( int index )
    {
        if( 0 > index || index > (int)myCut.size() - 1 )
            return -1;
        return myCut[ index ].myLocation;
    }

    /// rotate, if neccesary, so L > W > H
    void rotateLWH();

    /// sort by height
    void sortByHeight();

    timberv_t& orders()
    {
        return myOrder;
    }

    std::vector< cLevel >& levels()
    {
        return myLevels;
    }

    timberv_t& stock()
    {
        return myStock;
    }

private:

    timberv_t       myStock;

    timberv_t       myOrder;            /// the timbers that have to be delivered

    std::vector< cLevel > myLevels;

    timberv_t       myUnpacked;         /// orders that could not be met from the inventory

    std::vector<std::pair<timber_t,timber_t>>
                                           myAllocation;         /// stock that order was cut from

    std::vector< cCut > myCut;          /// cuts required

    /// Parse a line in the instance file
    std::vector< int > ParseSpaceDelimited(
        const std::string& l );

};
/** allocate timbers of same height to levels
@param[in] I the problem instance
*/
void Levels( cInstance& I );

/** allocate levels to stock
    @param[out] I the instance
*/
void
LevelsToStock(
    cInstance& I );

/** allocate a level to a stock
    @param[out] I the instance
    @param[in] level
    @param[in] stock inventory
    @return true if allocation successful
*/
bool
LevelToStock(
    cInstance& I,
    cLevel& level,
    timberv_t& stock );

/** cut out the orders
    @param[out] I the instance
*/
void LevelCuts(
    cInstance& I );

/** Cutting stock 2 dimensional no width
    @param[out] I the instance
    @param[in level
    @param[in] h height in stock
    @return true if all timbers in level were packed

    This is an extremely simple 2D cutting stock algorithm
    to be used as a placeholder in the H3CS algorithm.

    This makes no effort to stack in the width dimension!

    The effect is that the orders will be cut from each level
    in one line along the side of the stock timbers.
    The wastage is likely to be enormous!
*/
bool CS2LNW(
    cInstance& I,
    cLevel& level, int h );

/// Use pack2 engine to do 2D level cutting
void CS2Pack2(
    cInstance& I,
    cLevel& level, int h );

/** Allocate an order
    @param[in] I the instance
    @param[in] level
    @param[in] order index in level
    @param[[in] length position
    @param[[in] width position
    @param[[in] height position
*/
void AllocateOrder(
    cInstance& I,
    cLevel& level,
    int order,
    int length, int width, int height );

/** Record the V cut for a level in the instance
    @param[in] I the instance
    @param[in] stock
    @param[in] h height for cut at top of level
*/
void CutLevel(
    cInstance& I,
    timber_t stock,
    int h );

void ReturnToInventory(
    cInstance& I );

void DisplayWastage(
    cInstance& I );

}

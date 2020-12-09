// gas.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get City::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;               // max number of rows in a city
const int MAXCOLS = 30;               // max number of columns in a city
const int MAXFLATULANS = 120;         // max number of Flatulans allowed

const int UP      = 0;
const int DOWN    = 1;
const int LEFT    = 2;
const int RIGHT   = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class City;  // This is needed to let the compiler know that City is a
// type name, since it's mentioned in the Flatulan declaration.

class Flatulan
{
public:
    // Constructor
    Flatulan(City* cp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool possiblyGetConverted();
    
private:
    City* m_city;
    int   m_row;
    int   m_col;
};

class Player
{
public:
    // Constructor
    Player(City *cp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    int  health() const;
    bool isPassedOut() const;
    
    // Mutators
    void  preach();
    void  move(int dir);
    void  getGassed();
    
private:
    City* m_city;
    int   m_row;
    int   m_col;
    int   m_age;
    int   m_health; // added this data memeber
};

class City
{
public:
    // Constructor/destructor
    City(int nRows, int nCols);
    ~City();
    
    // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    bool    isPlayerAt(int r, int c) const;
    int     flatulanCount() const;
    int     nFlatulansAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;
    
    // Mutators
    bool  addFlatulan(int r, int c);
    bool  addPlayer(int r, int c);
    void  preachToFlatulansAroundPlayer();
    void  moveFlatulans();
    
private:
    int       m_rows;
    int       m_cols;
    Player  * m_player;
    Flatulan* m_flatulans[MAXFLATULANS];
    int       m_nFlatulans;
    
    // Helper functions
    bool isInBounds(int r, int c) const;
};

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();
    
    // Mutators
    void play();
    
private:
    City* m_city;
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Flatulan implementation
///////////////////////////////////////////////////////////////////////////

Flatulan::Flatulan(City* cp, int r, int c)
{
    if (cp == nullptr)
    {
        cout << "***** A Flatulan must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > cp->rows()  ||  c < 1  ||  c > cp->cols())
    {
        cout << "***** Flatulan created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_city = cp;
    m_row = r;
    m_col = c;
}

int Flatulan::row() const
{
    return m_row;
}

int Flatulan::col() const
{
    return m_col; // fixed implementation
}

void Flatulan::move()
{
    // Attempt to move in a random direction; if it can't move, don't move.
    // If the player is there, don't move.
    int dir = randInt(0, NUMDIRS-1);  // dir is now UP, DOWN, LEFT, or RIGHT
    switch (dir)
    {
        // for each case, check if the player is not at the destination of the propposed move
        // then utilize m_city->determineNewPosition() to determine if destination is in-bounds
        // since position variables for m_city->determineNewPosition() are pass by reference,
        // determineNewPosition will actually modify the flatulan's position
        case UP:
            if ((m_row - 1) >= 1 && !(m_city->isPlayerAt(m_row - 1, m_col)))
            {
                m_city->determineNewPosition(m_row, m_col, UP);
                break;
            }
            else break;
        case DOWN:
            if ((m_row + 1) <= m_city->rows() && !(m_city->isPlayerAt(m_row + 1, m_col)))
            {
                m_city->determineNewPosition(m_row, m_col, DOWN);
                break;
            }
            else break;
        case LEFT:
            if ((m_col - 1) >= 1 && !(m_city->isPlayerAt(m_row, m_col - 1)))
            {
                m_city->determineNewPosition(m_row, m_col, LEFT);
                break;
            }
            else break;
        case RIGHT:
            if ((m_col + 1) <= m_city->cols() && !(m_city->isPlayerAt(m_row, m_col + 1)))
            {
                m_city->determineNewPosition(m_row, m_col, RIGHT);
                break;
            }
            else break;
    }
    // fixed implementation
}

bool Flatulan::possiblyGetConverted()  // return true if converted
{
    // Be converted with 2/3 probability
    // generate pseudo-random number between 1 and 3, return true if value is 1 or 2
    // the value will be 1 or 2 2/3 of the time
    return (randInt(1, 3) != 3);  // fixed implementation
}

///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(City* cp, int r, int c)
{
    if (cp == nullptr)
    {
        cout << "***** The player must be created in some City!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > cp->rows()  ||  c < 1  ||  c > cp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_city = cp;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_health = 12;
}

int Player::row() const
{
    return m_row; // fixed implementation
}

int Player::col() const
{
    return m_col; // fixed implementation
}

int Player::age() const
{
    return m_age; // fixed implementation
}

int Player::health() const
{
    return m_health; // fixed implementation
}

bool Player::isPassedOut() const
{
    return (m_health <= 0); // fixed implementation
}

void Player::preach()
{
    m_age++;
    m_city->preachToFlatulansAroundPlayer();
}

void Player::move(int dir)
{
    m_age++;
    switch (dir)
    {
        // for each case, check if there are no flatulans at the destination of the propposed move
        // then utilize m_city->determineNewPosition() to determine if destination is in-bounds
        // since position variables for m_city->determineNewPosition() are pass by reference,
        // determineNewPosition will actually modify the player's position
        case UP:
            if (m_city->nFlatulansAt(m_row - 1, m_col) == 0)
            {
                m_city->determineNewPosition(m_row, m_col, UP);
                break;
            }
            else
                break;
        case DOWN:
            if (m_city->nFlatulansAt(m_row + 1, m_col) == 0)
            {
                m_city->determineNewPosition(m_row, m_col, DOWN);
                break;
            }
            else
                break;
        case LEFT:
            if (m_city->nFlatulansAt(m_row, m_col - 1) == 0)
            {
                m_city->determineNewPosition(m_row, m_col, LEFT);
                break;
            }
            else break;
        case RIGHT:
            if (m_city->nFlatulansAt(m_row, m_col + 1) == 0)
            {
                m_city->determineNewPosition(m_row, m_col, RIGHT);
                break;
            }
            else break;
    }
    // fixed implementation
}

void Player::getGassed()
{
    m_health--; // fixed implementation
}

///////////////////////////////////////////////////////////////////////////
//  City implementations
///////////////////////////////////////////////////////////////////////////

City::City(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** City created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nFlatulans = 0;
}

City::~City()
{
    // delete player
    delete m_player;
    // delete any flatulans that had not been deleted through player's preaching
    // (if player loses the game or quits early)
    for (int i = 0; i < m_nFlatulans; i++)
    {
        delete m_flatulans[i];
    }
    // fixed implementation
}

int City::rows() const
{
    return m_rows;
}

int City::cols() const
{
    return m_cols;
}

Player* City::player() const
{
    return m_player;
}

bool City::isPlayerAt(int r, int c) const
{
    return (m_player->row() == r && m_player->col() == c);
}

int City::flatulanCount() const
{
    return m_nFlatulans;
}

int City::nFlatulansAt(int r, int c) const
{
    int flatulansAt = 0;
    for (int i = 0; i < m_nFlatulans; i++)
    {
        if (m_flatulans[i]->row() == r && m_flatulans[i]->col() == c)
        {
            flatulansAt++;
        }
    }
    return flatulansAt;  // fixed implementation
}

bool City::determineNewPosition(int& r, int& c, int dir) const
{
    // If a move from row r, column c, one step in direction dir
    // would go off the edge of the city, leave r and c unchanged and
    // return false.  Otherwise, set r or c so that row r, column c,
    // is now the new position resulting from the proposed move, and
    // return true.
    switch (dir)
    {
        // for each case, check if prospective move in specified direction still results
        // in an in-bounds position, only modify r or c if true
        case UP:
            if (isInBounds(r - 1, c))
            {
                r--;
                return true;
            }
            else
                break;
        case DOWN:
            if (isInBounds(r + 1, c))
            {
                r++;
                return true;
            }
            else
                break;
        case LEFT:
            if (isInBounds(r, c - 1))
            {
                c--;
                return true;
            }
            else break;
        case RIGHT:
            if (isInBounds(r, c + 1))
            {
                c++;
                return true;
            }
            else break;
    }
    // return false if move results in an out-of-bounds position, or if any other error occurs
    return false; // fixed implementation
}

void City::display() const
{
    // Position (row,col) in the city coordinate system is represented in
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
            grid[r][c] = '.';
    
    // Indicate each Flatulan's position
    // If one Flatulan is at some grid point, set the char to 'F'.
    // If it's 2 though 8, set it to '2' through '8'.
    // For 9 or more, set it to '9'.
    for (r = 0; r < rows(); r++)
        for (c = 0; c < cols(); c++)
        {
            // need to add 1 to r and c since top left element in grid is at position (0, 0)
            // in the game itself this position is (1, 1)
            if (nFlatulansAt(r + 1, c + 1) == 1)
                grid[r][c] = 'F';
            else if (nFlatulansAt(r + 1, c + 1) >= 2 && nFlatulansAt(r + 1, c + 1) <= 8)
                grid[r][c] = nFlatulansAt(r + 1, c + 1) + '0';
            else if (nFlatulansAt(r + 1, c + 1) >= 9)
                grid[r][c] = '9';
        } // fixed implementation
        
    
    // Indicate player's position
    if (m_player != nullptr)
    {
        // Set the char to '@', unless there's also a Flatulan there
        // (which should never happen), in which case set it to '*'.
        char& gridChar = grid[m_player->row()-1][m_player->col()-1];
        if (gridChar == '.')
            gridChar = '@';
        else
            gridChar = '*';
    }
    
    // Draw the grid
    clearScreen();
    for (r = 0; r < rows(); r++)
    {
        for (c = 0; c < cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;
    
    // Write message, Flatulan, and player info
    cout << "There are " << m_nFlatulans << " unconverted Flatulans remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isPassedOut())
            cout << "The player has passed out." << endl;
        else
            cout << "The player's health level is " << m_player->health() << endl;
    }
}

bool City::addFlatulan(int r, int c)
{
    if (! isInBounds(r, c))
        return false;
    
    // Don't add a Flatulan on a spot with a player
    if (m_player != nullptr  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;
    
    // If there are MAXFLATULANS unconverted Flatulans, return false.
    // Otherwise, dynamically allocate a new Flatulan at coordinates (r,c).
    // Save the pointer to the newly allocated Flatulan and return true.
    
    // Your function must work as specified in the preceding paragraph even
    // in this scenario (which won't occur in this game):  MAXFLATULANS
    // Flatulans are added, then some are converted, then more are added.
    
    // return false if no more flatulans can be added
    if (flatulanCount() == MAXFLATULANS)
        return false;
    
    // adds a new flatulan at the next available index of n_flatulans through dynamic memory allocation
    m_flatulans[m_nFlatulans] = new Flatulan(this, r, c);
    m_nFlatulans++; // m_nFlatulans also increases by 1 to reflect this change
    return true; // fixed implementation
}

bool City::addPlayer(int r, int c)
{
    if (! isInBounds(r, c))
        return false;
    
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;
    
    // Don't add a player on a spot with a Flatulan
    if (nFlatulansAt(r, c) > 0)
        return false;
    
    // Dynamically allocate a new Player and add it to the city
    m_player = new Player(this, r, c);
    return true;
}

void City::preachToFlatulansAroundPlayer()
{
    // Preach to Flatulans orthogonally or diagonally adjacent to player.
    // If a Flatulan is converted, destroy it and remove it from the city,
    // since we have no further need to display it or have it interact with
    // the player.
    
    int i = 0;
    // while loop for iterating through every non-converted flatulan
    while (i < m_nFlatulans)
    {
        // check flatulan's proxiomity to player
        if (abs(m_flatulans[i]->row() - m_player->row()) <= 1 && abs(m_flatulans[i]->col() - m_player->col()) <= 1)
        {
            // execute statements below if flatulan is converted
            if (m_flatulans[i]->possiblyGetConverted())
            {
                // delete object that m_flatulans pointer points to
                delete m_flatulans[i];
                for (int j = i; j < m_nFlatulans - 1; j++)
                {
                    // move m_flatulans so that it is not a dangling pointer, avoid undefined behavior
                    m_flatulans[j] = m_flatulans[j + 1];
                }
                // subtract 1 from numFlatulans to reflect fact that a flatulan has been deleted
                m_nFlatulans--;
            }
            // move pointer to next flatulan if current flatulan is not converted
            else
                i++;
        }
        // move pointer to next flatulan if current flatulan is not directly orthogonal or diagonal to player
        else
            i++;
    }
} // fixed implementation


void City::moveFlatulans()
{
    for (int k = 0; k < m_nFlatulans; k++)
    {
        // Have the k-th Flatulan in the city make one move.
        // If that move results in that Flatulan being orthogonally
        // adjacent to the player, the player suffers a gas blast.
        
        // move kth flatulan
        m_flatulans[k]->move();
        
        // check flatulan's proximity to player, statement is true only when flatulan is orthogonal to player
        if (((abs(m_flatulans[k]->row() - m_player->row()) == 1) && (m_flatulans[k]->col() == m_player->col())) || ((abs(m_flatulans[k]->col() - m_player-> col()) == 1) && (m_flatulans[k]->row() == m_player->row())))
            // pass gas if flatulan is within proximity
            m_player->getGassed();
    }
}

bool City::isInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nFlatulans)
{
    if (nFlatulans < 0)
    {
        cout << "***** Cannot create Game with negative number of Flatulans!" << endl;
        exit(1);
    }
    if (nFlatulans > MAXFLATULANS)
    {
        cout << "***** Trying to create Game with " << nFlatulans
        << " Flatulans; only " << MAXFLATULANS << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1  &&  cols == 1  &&  nFlatulans > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the Flatulans!" << endl;
        exit(1);
    }
    
    // Create city
    m_city = new City(rows, cols);
    
    // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_city->addPlayer(rPlayer, cPlayer);
    
    // Populate with Flatulans
    while (nFlatulans > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        // Don't put a Flatulan where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_city->addFlatulan(r, c);
        nFlatulans--;
    }
}

Game::~Game()
{
    delete m_city;
}

void Game::play()
{
    m_city->display();
    Player* p = m_city->player();
    if (p == nullptr)
        return;
    
    while ( ! p->isPassedOut()  &&  m_city->flatulanCount() > 0)
    {
        cout << "Move (u/d/l/r//q): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)  // player preaches
            p->preach();
        else
        {
            switch (action[0])
            {
                default:   // if bad move, nobody moves
                    cout << '\a' << endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    p->move(decodeDirection(action[0]));
                    break;
            }
        }
        m_city->moveFlatulans();
        m_city->display();
    }
    if (p->isPassedOut())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
        case 'u':  return UP;
        case 'd':  return DOWN;
        case 'l':  return LEFT;
        case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

// Return a random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rd;
    static default_random_engine generator(rd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

void doBasicTests();

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////

int main()
{
    doBasicTests(); // Remove this line after completing test.
    return 0;       // Remove this line after completing test.

    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 4, 2);
    // Game g(1, 20, 10);
    
    // Play the game
    // g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANY CODE BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif

#include <type_traits>
#include <cassert>

#define CHECKTYPE(c, f, r, a)  \
static_assert(std::is_same<decltype(&c::f), r (c::*)a>::value, \
"FAILED: You changed the type of " #c "::" #f);  \
[[gnu::unused]] auto xxx##c##_##f = static_cast<r(c::*)a>(&c::f)

void thisFunctionWillNeverBeCalled()
{
    // If the student deleted or changed the interfaces to the public
    // functions, this won't compile.  (This uses magic beyond the scope
    // of CS 31.)
    
    Flatulan(static_cast<City*>(0), 1, 1);
    CHECKTYPE(Flatulan, row, int, () const);
    CHECKTYPE(Flatulan, col, int, () const);
    CHECKTYPE(Flatulan, move, void, ());
    CHECKTYPE(Flatulan, possiblyGetConverted, bool, ());
    
    Player(static_cast<City*>(0), 1, 1);
    CHECKTYPE(Player, row, int, () const);
    CHECKTYPE(Player, col, int, () const);
    CHECKTYPE(Player, age, int, () const);
    CHECKTYPE(Player, health, int, () const);
    CHECKTYPE(Player, isPassedOut, bool, () const);
    CHECKTYPE(Player, preach, void, ());
    CHECKTYPE(Player, move, void, (int));
    CHECKTYPE(Player, getGassed, void, ());
    
    City(1, 1);
    CHECKTYPE(City, rows, int, () const);
    CHECKTYPE(City, cols, int, () const);
    CHECKTYPE(City, player, Player*, () const);
    CHECKTYPE(City, isPlayerAt, bool, (int,int) const);
    CHECKTYPE(City, flatulanCount, int, () const);
    CHECKTYPE(City, nFlatulansAt, int, (int,int) const);
    CHECKTYPE(City, determineNewPosition, bool, (int&,int&,int) const);
    CHECKTYPE(City, display, void, () const);
    CHECKTYPE(City, addFlatulan, bool, (int,int));
    CHECKTYPE(City, addPlayer, bool, (int,int));
    CHECKTYPE(City, preachToFlatulansAroundPlayer, void, ());
    CHECKTYPE(City, moveFlatulans, void, ());
    
    Game(1, 1, 1);
    CHECKTYPE(Game, play, void, ());
}

void doBasicTests()
{
    {
        City walk(10, 20);
        assert(walk.addPlayer(2, 6));
        Player* pp = walk.player();
        assert(walk.isPlayerAt(2, 6)  && ! pp->isPassedOut());
        pp->move(UP);
        assert(walk.isPlayerAt(1, 6)  && ! pp->isPassedOut());
        pp->move(UP);
        assert(walk.isPlayerAt(1, 6)  && ! pp->isPassedOut());
        for (int k = 1; k <= 11; k++)
            pp->getGassed();
        assert(! pp->isPassedOut());
        pp->getGassed();
        assert(pp->isPassedOut());
    }
    {
        City ofAngels(2, 2);
        assert(ofAngels.addPlayer(1, 1));
        assert(ofAngels.addFlatulan(2, 2));
        Player* pp = ofAngels.player();
        ofAngels.moveFlatulans();
        assert( ! pp->isPassedOut());
        for (int k = 0; k < 1000  && ! pp->isPassedOut(); k++)
            ofAngels.moveFlatulans();
        assert(pp->isPassedOut());
    }
    {
        City ousDarth(2, 2);
        assert(ousDarth.addPlayer(1, 1));
        for (int k = 0; k < 50; k++)
        {
            assert(ousDarth.addFlatulan(1, 2));
            assert(ousDarth.addFlatulan(2, 2));
        }
        ousDarth.preachToFlatulansAroundPlayer();
        assert(ousDarth.nFlatulansAt(1, 1) == 0);
        assert(ousDarth.nFlatulansAt(2, 1) == 0);
        for (int r = 1; r <= 2; r++)
        {     // .9999 probability that between 5 and 29 out of 50 are unconverted
            int n = ousDarth.nFlatulansAt(r, 2);
            assert(n >= 5  &&  n <= 29);
        }
        int m = ousDarth.nFlatulansAt(1, 2);
        ousDarth.addFlatulan(1, 2);
        assert(ousDarth.nFlatulansAt(1, 2) == m+1);
    }
    {
        City univer(5, 20);
        univer.addPlayer(3, 3);
        int r = 1;
        int c = 1;
        for (int k = 1; k <= 5*5; k++)
        {
            if (r != 3 || c != 3)
                univer.addFlatulan(r, c);
            if (r == 5)
            {
                r = c+1;
                c = 5;
            }
            else if (c == 1)
            {
                c = r + 1;
                r = 1;
            }
            else
            {
                c--;
                r++;
            }
        }
        assert(univer.flatulanCount() == 24);
        for (int k = 0; k < 1000  && univer.flatulanCount() > 16; k++)
            univer.preachToFlatulansAroundPlayer();
        assert(univer.flatulanCount() == 16);
        for (int r = 1; r <= 5; r++)
        {
            for (int c = 1; c <= 5; c++)
            {
                int expected = 1;
                if (r >= 2  &&  r <= 4  &&  c >= 2  &&  c <= 4)
                    expected = 0;
                assert(univer.nFlatulansAt(r, c) == expected);
            }
        }
        univer.addFlatulan(3, 2);
        assert(univer.flatulanCount() == 17);
        // If the program crashes after leaving this compound statement, you
        // are probably messing something up when you delete a Flatulan after
        // it is converted (or you have mis-coded the destructor).
        //
        // Draw a picture of your m_flatulans array before the Flatulans are
        // preached to and also note the values of m_nFlatulans or any other
        // variables you might have that are involved with the number of
        // Flatulans.  Trace through your code step by step as the Flatulans
        // are preached to and removed, updating the picture according to
        // what the code says, not what you want it to do.  If you don't see
        // a problem then, try tracing through the destruction of the city.
        //
        // If you execute the code, use the debugger to check on the values
        // of key variables at various points.  If you didn't try to learn
        // to use the debugger, insert statements that write the values of
        // key variables to cerr so you can trace the execution of your code
        // and see the first place where something has gone amiss.  (Comment
        // out the call to clearScreen in City::display so that your output
        // doesn't disappear.)
    }
    cout << "Passed all basic tests" << endl;
}

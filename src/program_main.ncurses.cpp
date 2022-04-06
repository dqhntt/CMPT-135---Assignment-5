#include "Database.h"
#include "Menu.h"
#include "program_main.h"
#include "util.ncurses.h"

using namespace std;

int program_main_ncurses() {
    
    ///
    /// @todo Implement the program.
    ///

    //
    // Sample program
    // From course webpage.
    //
    // initialize screen in curses mode
    const util::ncurses::Ncurses_RAII nc;
    // print to screen
    printw("Hello World!");
    // move the cursor to row 2, column 20
    move(5, 14);
    printw("Whoosh!");
    // print some numbers in a pattern
    int c = 0;
    for (int r = 0; r < 10; r++) {
        move(r + 2, c);
        // printw takes a C-string (i.e. a const char*),
        // and we can get a C-string from a std::string
        // using the std::string c_str method.
        printw(to_string(r).c_str());
        c += r;
    }
    move(2, 10);
    printw("Press any key to end.");
    // redraw the screen
    refresh();
    // read a character to pause the program
    getch();

    return EXIT_SUCCESS;
}

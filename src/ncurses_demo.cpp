// ncurses_demo.cpp

#include <ncurses.h>
#include <string>

using namespace std;

int main() {
    // initialize the screen
    initscr();

    // print to screen
    printw("Hello World!");

    // move the cursor to row 2, column 20
    move(5, 14);
    printw("Whoosh!");

    // print some numbers in a pattern
    int c = 0;
    for (int r = 0; r < 10; r++) {
        move(r+2, c);
        // printw takes a C-string (i.e. a const char*)
        // as input; if s is a std::string, then
        // s.c_str() is  C-string version of it.
        printw(to_string(r).c_str());
        c += r;
    }

    move(2, 10);
    printw("Press any key to end.");

    // redraw the screen
    refresh();

    // read a character to pause the program
    getch();

    // deallocate memory and ends ncurses
    endwin();
}
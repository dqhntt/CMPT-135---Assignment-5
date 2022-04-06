#ifndef UTIL_NCURSES_H
#define UTIL_NCURSES_H

#include <form.h> // May not actually need all of these.
#include <menu.h>
#include <ncurses.h>
#include <panel.h>

namespace util::ncurses {

///////////////////////////////////////////////////////////////////////////////
// Description:
//    A simple RAII wrapper for ncurses to help prevent memory leak.
// Pre-condition:
//    ncurses is installed on the system.
// Post-condition:
//    Auto invoke `initscr()` upon object creation,
//    and `endwin()` upon object destruction.
// Ref:
//    https://docs.oracle.com/cd/E36784_01/html/E36880/isendwin-3curses.html
//    https://invisible-island.net/ncurses/man/curs_memleaks.3x.html
class Ncurses_RAII {
public:
    // Initialize terminal in curses mode.
    Ncurses_RAII() {
        initscr();
    }
    // End curses mode.
    ~Ncurses_RAII() {
        if (!isendwin()) {
            endwin();
        }
        exit_curses(EXIT_SUCCESS);
    }
}; // class Ncurses_RAII

} // namespace util::ncurses

#endif // UTIL_NCURSES_H
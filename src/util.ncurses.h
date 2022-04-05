#ifndef UTIL_NCURSES_H
#define UTIL_NCURSES_H

#include <form.h> // May not actually need all of these.
#include <menu.h>
#include <ncurses.h>
#include <panel.h>

namespace util::ncurses {

///////////////////////////////////////////////////////////////////////////////
// Description:
//    A simple RAII wrapper for ncurses to prevent memory leak.
// Pre-condition:
//    ncurses is installed on the system.
//    endwin() is not manually called elsewhere.
// Post-condition:
//    Auto invoke `initscr()` upon object creation,
//    and `endwin()` upon object destruction.
class Ncurses_RAII {
public:
    // Initialize terminal in curses mode.
    Ncurses_RAII() { initscr(); }
    // End curses mode.
    // Destructor will not call `endwin()` again.
    void invoke_endwin() {
        endwin();
        _invoked_endwin = true;
    }
    // End curses mode if not already done so.
    ~Ncurses_RAII() {
        if (!_invoked_endwin)
            endwin();
    }
    // Delete copy ctor to prevent copying.
    Ncurses_RAII(const Ncurses_RAII&) = delete;
    // Delete copy assignment operator to prevent copying.
    Ncurses_RAII& operator=(const Ncurses_RAII&) = delete;

private:
    bool _invoked_endwin = false;
}; // class Ncurses_RAII

} // namespace util::ncurses

#endif // UTIL_NCURSES_H
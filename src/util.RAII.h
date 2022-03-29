#ifndef UTIL_RAII_H
#define UTIL_RAII_H

namespace util::RAII {

///////////////////////////////////////////////////////////////////////////////
// Description:
//    A simple RAII wrapper for ncurses to prevent memory leak.
// Pre-condition:
//    ncurses is installed on the system.
// Post-condition:
//    Auto invoke `initscr()` upon object creation,
//    and `endwin()` upon object destruction.
class Ncurses {
public:
    // Initialize terminal in curses mode.
    Ncurses();

    // End curses mode.
    // Destructor will not call `endwin()` again.
    void invoke_endwin();

    // End curses mode if not already done so.
    ~Ncurses();

    // Delete copy ctor to prevent copying.
    Ncurses(const Ncurses&) = delete;

    // Delete copy assignment operator to prevent copying.
    Ncurses& operator=(const Ncurses&) = delete;

private:
    bool _invoked_endwin = false;

}; // class Ncurses

} // namespace util::RAII

#endif // UTIL_RAII_H

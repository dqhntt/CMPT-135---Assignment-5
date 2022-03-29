#include "util.RAII.h"
#include <ncurses.h>

util::RAII::Ncurses::Ncurses()
{
    initscr();
}

void util::RAII::Ncurses::invoke_endwin()
{
    endwin();
    _invoked_endwin = true;
}

util::RAII::Ncurses::~Ncurses()
{
    if (!_invoked_endwin) {
        endwin();
    }
}

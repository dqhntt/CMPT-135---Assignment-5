#include "Menu.h"
#include "cmpt_error.h"
#include "util.ncurses.h"
#include "util.parse.h"
using namespace std;

namespace ncurses {

// Inherit from class Menu in global namespace in Menu.h
class Menu : public ::Menu {
private:
    const util::ncurses::Ncurses_RAII ncurses_wrapper;
};

} // namespace ncurses
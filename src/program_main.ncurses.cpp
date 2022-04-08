#include "program_main.h"
#include "Database.h"
#include "Menu.h"
#include "Menu.ncurses.h"
#include "util.h"
using namespace std;

// FIXME: Just testing sample from: http://www.linuxfocus.org/English/March2002/article233.shtml :)

const int ENTER = 10;
const int ESCAPE = 27;

void init_curses() {
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    init_pair(3, COLOR_RED, COLOR_WHITE);
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
}
void draw_menubar(WINDOW* menubar) {
    wbkgd(menubar, COLOR_PAIR(2));
    waddstr(menubar, "Add");
    wattron(menubar, COLOR_PAIR(3));
    waddstr(menubar, "(F1)");
    wattroff(menubar, COLOR_PAIR(3));
    wmove(menubar, 0, 15);
    waddstr(menubar, "Find");
    wattron(menubar, COLOR_PAIR(3));
    waddstr(menubar, "(F2)");
    wattroff(menubar, COLOR_PAIR(3));
    wmove(menubar, 0, 30);
    waddstr(menubar, "Delete");
    wattron(menubar, COLOR_PAIR(3));
    waddstr(menubar, "(F3)");
    wattroff(menubar, COLOR_PAIR(3));
    wmove(menubar, 0, 45);
    waddstr(menubar, "List");
    wattron(menubar, COLOR_PAIR(3));
    waddstr(menubar, "(F4)");
    wattroff(menubar, COLOR_PAIR(3));
    wmove(menubar, 0, 60);
    waddstr(menubar, "Quit");
    wattron(menubar, COLOR_PAIR(3));
    waddstr(menubar, "(Esc)");
    wattroff(menubar, COLOR_PAIR(3));
}
WINDOW** draw_menu(int start_col) {
    WINDOW** items = new WINDOW*[8];

    items[0] = newwin(10, 19, 1, start_col);
    wbkgd(items[0], COLOR_PAIR(2));
    box(items[0], ACS_VLINE, ACS_HLINE);
    items[1] = subwin(items[0], 1, 17, 2, start_col + 1);
    items[2] = subwin(items[0], 1, 17, 3, start_col + 1);
    items[3] = subwin(items[0], 1, 17, 4, start_col + 1);
    items[4] = subwin(items[0], 1, 17, 5, start_col + 1);
    items[5] = subwin(items[0], 1, 17, 6, start_col + 1);
    items[6] = subwin(items[0], 1, 17, 7, start_col + 1);
    items[7] = subwin(items[0], 1, 17, 8, start_col + 1);
    wprintw(items[1], "By city name");
    wprintw(items[2], "By province");
    wprintw(items[3], "By prov code");
    wprintw(items[4], "By latitude");
    wprintw(items[5], "By longitude");
    wprintw(items[6], "By population");
    wprintw(items[7], "By pop density");
    wbkgd(items[1], COLOR_PAIR(1));
    wrefresh(items[0]);
    return items;
}
void delete_menu(WINDOW* items[], int count) {
    for (int i = 0; i < count; i++)
        delwin(items[i]);
    delete[] items;
}
int scroll_menu(WINDOW* items[], int count, int menu_start_col) {
    int key;
    int selected = 0;
    while (1) {
        key = getch();
        if (key == KEY_DOWN || key == KEY_UP) {
            wbkgd(items[selected + 1], COLOR_PAIR(2));
            wnoutrefresh(items[selected + 1]);
            if (key == KEY_DOWN) {
                selected = (selected + 1) % count;
            } else {
                selected = (selected + count - 1) % count;
            }
            wbkgd(items[selected + 1], COLOR_PAIR(1));
            wnoutrefresh(items[selected + 1]);
            doupdate();
        } else if (key == KEY_LEFT) {
            delete_menu(items, count + 1);
            touchwin(stdscr);
            refresh();
            int new_start_col;
            if (menu_start_col <= 15)
                new_start_col = menu_start_col + 30; // Reset to below menu 4.
            else
                new_start_col = menu_start_col - 15;
            items = draw_menu(new_start_col);
            return scroll_menu(items, 7, new_start_col);
        } else if (key == KEY_RIGHT) {
            delete_menu(items, count + 1);
            touchwin(stdscr);
            refresh();
            int new_start_col;
            if (menu_start_col >= 45)
                new_start_col = menu_start_col - 30; // Reset to below menu 2.
            else
                new_start_col = menu_start_col + 15;
            items = draw_menu(new_start_col);
            return scroll_menu(items, 7, new_start_col);
        } else if (key == ENTER) {
            return selected;
        } else {
            return -1;
        }
    }
}

int program_main_ncurses() {
    // Initialize screen in curses mode
    // This RAII object eliminates the needs to call initscr() and endwin() manually.
    const util::ncurses::Ncurses_RAII nc;

    Menu_ncurses menu;
    // Menu_Option main_menu_option = Menu_Option::invalid_option;

    // open database
    Database db;
    try {
        db.open("database.txt");
    } catch (const exception&) {
        try {
            db.open("../data/database.txt");
        } catch (const exception&) { db.open("../data/test_database.txt"); }
    }

    int key;
    WINDOW *menubar, *messagebar;

    init_curses();
    bkgd(COLOR_PAIR(1));

    menubar = subwin(stdscr, 1, 80, 0, 0);
    messagebar = subwin(stdscr, 1, 79, 23, 1);
    draw_menubar(menubar);
    menu.show_main_menu();
    move(10, 1);
    printw("Press F1, F2, or other options in the toolbar to open the menus. ");
    printw("ESC quits.");
    refresh();

    do {
        int selected_item;
        WINDOW** menu_items;
        key = getch();
        werase(messagebar);
        wrefresh(messagebar);
        if (key == KEY_F(1)) {
            //
            // TODO: Execute menu 1.
            //
            touchwin(stdscr);
            refresh();
        } else if (key == KEY_F(2)) {
            menu_items = draw_menu(15);
            selected_item = scroll_menu(menu_items, 7, 15);
            delete_menu(menu_items, 8);
            if (selected_item < 0)
                wprintw(messagebar, "You haven't selected any item.");
            else // TODO
                wprintw(messagebar, "You have selected menu item %d.", selected_item + 1);
            touchwin(stdscr);
            refresh();
        } else if (key == KEY_F(3)) {
            menu_items = draw_menu(30);
            selected_item = scroll_menu(menu_items, 7, 30);
            delete_menu(menu_items, 8);
            if (selected_item < 0)
                wprintw(messagebar, "You haven't selected any item.");
            else // TODO
                wprintw(messagebar, "You have selected menu item %d.", selected_item + 1);
            touchwin(stdscr);
            refresh();
        } else if (key == KEY_F(4)) {
            menu_items = draw_menu(45);
            selected_item = scroll_menu(menu_items, 7, 45);
            delete_menu(menu_items, 8);
            if (selected_item < 0)
                wprintw(messagebar, "You haven't selected any item.");
            else // TODO
                wprintw(messagebar, "You have selected menu item %d.", selected_item + 1);
            touchwin(stdscr);
            refresh();
        } else if (key != ESCAPE) {
            WINDOW* error_msg = subwin(stdscr, 1, 80, 15, 0);
            wprintw(error_msg, "You entered an invalid option. Please try again: ");
            touchwin(stdscr);
            refresh();
            util::time::pause(600);
            werase(error_msg);
            wrefresh(error_msg);
            delwin(error_msg);
        }
    } while (key != ESCAPE);

    delwin(menubar);
    delwin(messagebar);

    return EXIT_SUCCESS;
}

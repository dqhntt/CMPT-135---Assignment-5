#include "program_main.h"
#include "Database.h"
#include "Menu.h"
#include "Menu.ncurses.h"
#include "util.h"
using namespace std;

// FIXME: Just testing sample from: http://www.linuxfocus.org/English/March2002/article233.shtml :)

const int ENTER = 10;
const int ESCAPE = 27;

// Moved to class Menu constructor.
// void init_curses() {
//     start_color();
//     init_pair(1, COLOR_WHITE, COLOR_BLUE);
//     init_pair(2, COLOR_BLUE, COLOR_WHITE);
//     init_pair(3, COLOR_RED, COLOR_WHITE);
//     curs_set(0);
//     noecho();
//     keypad(stdscr, TRUE);
// }
void draw_menubar(WINDOW* menubar) {
    wbkgd(menubar, COLOR_PAIR(2));
    waddstr(menubar, "Add");
    wattron(menubar, COLOR_PAIR(3));
    waddstr(menubar, "(A)");
    wattroff(menubar, COLOR_PAIR(3));
    wmove(menubar, 0, 15);
    waddstr(menubar, "Find");
    wattron(menubar, COLOR_PAIR(3));
    waddstr(menubar, "(F)");
    wattroff(menubar, COLOR_PAIR(3));
    wmove(menubar, 0, 30);
    waddstr(menubar, "Delete");
    wattron(menubar, COLOR_PAIR(3));
    waddstr(menubar, "(D)");
    wattroff(menubar, COLOR_PAIR(3));
    wmove(menubar, 0, 45);
    waddstr(menubar, "List");
    wattron(menubar, COLOR_PAIR(3));
    waddstr(menubar, "(L)");
    wattroff(menubar, COLOR_PAIR(3));
    wmove(menubar, 0, 60);
    waddstr(menubar, "Quit");
    wattron(menubar, COLOR_PAIR(3));
    waddstr(menubar, "(Q)");
    wattroff(menubar, COLOR_PAIR(3));
}
vector<WINDOW*> draw_menu(int start_col) {
    vector<WINDOW*> items;
    items.push_back(newwin(10, 18, 1, start_col));
    wbkgd(items[0], COLOR_PAIR(2));
    box(items[0], ACS_VLINE, ACS_HLINE);
    for (int i = 0; i < 7; i++) {
        items.push_back(subwin(items.front(), 1, 16, (i + 2), start_col + 1));
    }
    if (items.size() < 8) {
        const string error_msg = "Insufficient memory for 7 City's fields in " + string(__func__)
            + "()\n" + "FILE: " + string(__FILE__);
        cmpt::error(error_msg);
    }
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
void delete_menu(vector<WINDOW*>& items) {
    for (WINDOW*& item : items) {
        delwin(item);
    }
}
int scroll_menu(vector<WINDOW*>& items, int menu_start_col) {
    int key;
    int selected = 0;
    while (1) {
        key = getch();
        if (key == KEY_DOWN || key == KEY_UP) {
            wbkgd(items[selected + 1], COLOR_PAIR(2));
            wnoutrefresh(items[selected + 1]);
            if (key == KEY_DOWN) {
                selected = (selected + 1) % (items.size() - 1);
            } else {
                selected = (selected + (items.size() - 1) - 1) % (items.size() - 1);
            }
            wbkgd(items[selected + 1], COLOR_PAIR(1));
            wnoutrefresh(items[selected + 1]);
            doupdate();
        } else if (key == KEY_LEFT) {
            delete_menu(items);
            touchwin(stdscr);
            refresh();
            int new_start_col;
            if (menu_start_col <= 15)
                new_start_col = 45; // Reset to below menu 4.
            else
                new_start_col = menu_start_col - 15;
            items = draw_menu(new_start_col);
            return scroll_menu(items, new_start_col);
        } else if (key == KEY_RIGHT) {
            delete_menu(items);
            touchwin(stdscr);
            refresh();
            int new_start_col;
            if (menu_start_col >= 45)
                new_start_col = 15; // Reset to below menu 2.
            else
                new_start_col = menu_start_col + 15;
            items = draw_menu(new_start_col);
            return scroll_menu(items, new_start_col);
        } else if (key == ENTER) {
            return selected;
        } else {
            return -1;
        }
    }
}

int program_main_ncurses() {
    Menu_ncurses menu;
    // Menu_Option main_menu_option = Menu_Option::invalid_option;

    // open database
    Database db;
    try {
        db.open("database.txt");
    } catch (const exception&) {
        try {
            db.open("./data/database.txt");
        } catch (const exception&) {
            try {
                db.open("../data/database.txt");
            } catch (const exception&) { db.open("../data/test_database.txt"); }
        }
    }

    int key;
    WINDOW *menubar, *messagebar;

    bkgd(COLOR_PAIR(1));

    menubar = subwin(stdscr, 1, 80, 0, 0);
    messagebar = subwin(stdscr, 1, 79, 23, 1);
    draw_menubar(menubar);
    menu.show_main_menu();
    move(12, 0);
    printw("Enter the letter of your choice.");
    refresh();

    do {
        int selected_item;
        vector<WINDOW*> menu_items;
        key = getch();
        werase(messagebar);
        wrefresh(messagebar);
        if (key == 'a' || key == 'A') {
            //
            // TODO: Execute menu 1.
            //
            touchwin(stdscr);
            refresh();
        } else if (key == 'f' || key == 'F') {
            menu_items = draw_menu(15);
            selected_item = scroll_menu(menu_items, 15);
            delete_menu(menu_items);
            if (selected_item < 0)
                wprintw(messagebar, "You haven't selected any item.");
            else // TODO
                wprintw(messagebar, "You have selected menu item %d.", selected_item + 1);
            touchwin(stdscr);
            refresh();
        } else if (key == 'd' || key == 'D') {
            menu_items = draw_menu(30);
            selected_item = scroll_menu(menu_items, 30);
            delete_menu(menu_items);
            if (selected_item < 0)
                wprintw(messagebar, "You haven't selected any item.");
            else // TODO
                wprintw(messagebar, "You have selected menu item %d.", selected_item + 1);
            touchwin(stdscr);
            refresh();
        } else if (key == 'l' || key == 'L') {
            menu_items = draw_menu(45);
            selected_item = scroll_menu(menu_items, 45);
            delete_menu(menu_items);
            if (selected_item < 0)
                wprintw(messagebar, "You haven't selected any item.");
            else // TODO
                wprintw(messagebar, "You have selected menu item %d.", selected_item + 1);
            touchwin(stdscr);
            refresh();
        } else if (key != ESCAPE && key != 'q' && key != 'Q') {
            WINDOW* error_msg = subwin(stdscr, 1, 80, 15, 0);
            wprintw(error_msg, "You entered an invalid option. Please try again: ");
            touchwin(stdscr);
            refresh();
            util::time::pause(600);
            werase(error_msg);
            wrefresh(error_msg);
            delwin(error_msg);
        }
    } while (key != ESCAPE && key != 'q' && key != 'Q');

    delwin(menubar);
    delwin(messagebar);

    return EXIT_SUCCESS;
}

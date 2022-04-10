#include "program_main.h"
#include "Database.h"
#include "Menu.ncurses.h"
#include "util.h"
using namespace std;

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

void quick_nc_pause() { util::time::pause(100); }
void nc_say_invalid_option();
int nc_get_sub_sub_menu_option();

void nc_do_add_records_menu(const Menu_ncurses& menu, Database& db);
void nc_do_find_records_menu(const Menu_ncurses& menu, Database& db);
void nc_do_delete_records_menu(const Menu_ncurses& menu, Database& db);
void nc_do_list_records_menu(const Menu_ncurses& menu, Database& db);

int program_main_ncurses() { // Ncurses menu controller.
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
    Menu_ncurses menu;
    menu.show_main_menu();
    while (true) {
        quick_nc_pause();
        switch (getch()) {
        case '1':
            nc_do_add_records_menu(menu, db);
            menu.show_main_menu();
            break;
        case '2':
            nc_do_find_records_menu(menu, db);
            menu.show_main_menu();
            break;
        case '3':
            nc_do_delete_records_menu(menu, db);
            menu.show_main_menu();
            break;
        case '4':
            nc_do_list_records_menu(menu, db);
            menu.show_main_menu();
            break;
        case '5':
            return EXIT_SUCCESS;
        default:
            nc_say_invalid_option();
        } // switch
        quick_nc_pause();
    } // while

    return EXIT_SUCCESS;
} // program_main_ncurses

///////////////////////////////////////////////////////////////////////////////////////////////////

void nc_do_add_records_menu(const Menu_ncurses& menu, Database& db) {
    menu.add_records.show_guides();
    do {
        const City city = menu.add_records.get_input();
        quick_nc_pause();
        if (db.exists_record(city)) {
            menu.add_records.say_record_exists(city);
        } else {
            db.add_city(city);
            menu.add_records.say_record_added(city);
        }
        quick_nc_pause();
    } while (menu.ask_if_user_wants_to_try_again());
} // nc_do_add_records_menu

///////////////////////////////////////////////////////////////////////////////////////////////////

void nc_do_find_records_by_strings_sub_menu(
    const Menu_ncurses& menu, Database& db, const Field& field);
void nc_do_find_records_by_numbers_sub_menu(
    const Menu_ncurses& menu, Database& db, const Field& field);

void nc_do_find_records_menu(const Menu_ncurses& menu, Database& db) {
    menu.find_records.show_guides();
    while (true) {
        switch (getch()) {
        case '1':
            nc_do_find_records_by_strings_sub_menu(menu, db, Field::city_name);
            menu.find_records.show_guides();
            break;
        case '2':
            nc_do_find_records_by_strings_sub_menu(menu, db, Field::province);
            menu.find_records.show_guides();
            break;
        case '3':
            nc_do_find_records_by_strings_sub_menu(menu, db, Field::province_id);
            menu.find_records.show_guides();
            break;
        case '4':
            nc_do_find_records_by_numbers_sub_menu(menu, db, Field::latitude);
            menu.find_records.show_guides();
            break;
        case '5':
            nc_do_find_records_by_numbers_sub_menu(menu, db, Field::longitude);
            menu.find_records.show_guides();
            break;
        case '6':
            nc_do_find_records_by_numbers_sub_menu(menu, db, Field::population);
            menu.find_records.show_guides();
            break;
        case '7':
            nc_do_find_records_by_numbers_sub_menu(menu, db, Field::population_density);
            menu.find_records.show_guides();
            break;
        case '8': // Return to main menu.
            return;
        default:
            nc_say_invalid_option();
        } // switch
        quick_nc_pause();
    }
} // nc_do_find_records_menu

void nc_do_find_records_by_strings_sub_menu(
    const Menu_ncurses& menu, Database& db, const Field& field) {
    do {
        menu.find_records.by_string.show_guides();
        const int sub_sub_menu_option = menu.get_input_option(3);
        if (sub_sub_menu_option == 3) {
            return; // To previous menu.
        }
        const bool substring_mode = (sub_sub_menu_option == 2);
        const string input = menu.find_records.by_string.get_input_string(substring_mode);
        db.sort_cities(substring_mode ? field : Field::city_name, 0, substring_mode);
        menu.print_matching_records(db.cities_matching_string(field, substring_mode, input));
        quick_nc_pause();
    } while (menu.ask_if_user_wants_to_try_again());
} // nc_do_find_records_by_strings_sub_menu

void nc_do_find_records_by_numbers_sub_menu(
    const Menu_ncurses& menu, Database& db, const Field& field) {
    do {
        menu.find_records.by_number.show_guides();
        const int sub_sub_menu_option = menu.get_input_option(3);
        if (sub_sub_menu_option == 3) {
            return; // To previous menu.
        }
        const bool range_mode = (sub_sub_menu_option == 2);
        const Range_t inputs = menu.find_records.by_number.get_input_numbers(range_mode);
        db.sort_cities(range_mode ? field : Field::city_name, 0, range_mode);
        menu.print_matching_records(db.cities_in_number_range(field, inputs.first, inputs.second));
        quick_nc_pause();
    } while (menu.ask_if_user_wants_to_try_again());
} // nc_do_find_records_by_numbers_sub_menu

///////////////////////////////////////////////////////////////////////////////////////////////////

void nc_do_delete_records_by_strings_sub_menu(
    const Menu_ncurses& menu, Database& db, const Field& field);
void nc_do_delete_records_by_numbers_sub_menu(
    const Menu_ncurses& menu, Database& db, const Field& field);

void nc_do_delete_records_menu(const Menu_ncurses& menu, Database& db) {
    menu.delete_records.show_guides();
    while (true) {
        switch (getch()) {
        case '1':
            nc_do_delete_records_by_strings_sub_menu(menu, db, Field::city_name);
            menu.delete_records.show_guides();
            break;
        case '2':
            nc_do_delete_records_by_strings_sub_menu(menu, db, Field::province);
            menu.delete_records.show_guides();
            break;
        case '3':
            nc_do_delete_records_by_strings_sub_menu(menu, db, Field::province_id);
            menu.delete_records.show_guides();
            break;
        case '4':
            nc_do_delete_records_by_numbers_sub_menu(menu, db, Field::latitude);
            menu.delete_records.show_guides();
            break;
        case '5':
            nc_do_delete_records_by_numbers_sub_menu(menu, db, Field::longitude);
            menu.delete_records.show_guides();
            break;
        case '6':
            nc_do_delete_records_by_numbers_sub_menu(menu, db, Field::population);
            menu.delete_records.show_guides();
            break;
        case '7':
            nc_do_delete_records_by_numbers_sub_menu(menu, db, Field::population_density);
            menu.delete_records.show_guides();
            break;
        case '8': // Return to main menu.
            break;
        default:
            nc_say_invalid_option();
        } // switch
        quick_nc_pause();
    }
} // nc_do_delete_records_menu

void nc_do_delete_records_by_strings_sub_menu(
    const Menu_ncurses& menu, Database& db, const Field& field) {
    do {
        menu.delete_records.by_string.show_guides();
        const int sub_sub_menu_option = menu.get_input_option(3);
        if (sub_sub_menu_option == 3) {
            return; // To previous menu.
        }
        const bool substring_mode = (sub_sub_menu_option == 2);
        const string input = menu.delete_records.by_string.get_input_string(substring_mode);
        db.sort_cities(substring_mode ? field : Field::city_name, 0, substring_mode);
        const vector<City> matching_records
            = db.cities_matching_string(field, substring_mode, input);
        menu.print_matching_records(matching_records);
        if (!matching_records.empty() && menu.delete_records.confirm_user_wants_to_delete()) {
            db.delete_cities(matching_records);
            menu.delete_records.say_records_deleted(matching_records.size());
        }
        quick_nc_pause();
    } while (menu.ask_if_user_wants_to_try_again());
} // nc_do_delete_records_by_strings_sub_menu

void nc_do_delete_records_by_numbers_sub_menu(
    const Menu_ncurses& menu, Database& db, const Field& field) {
    do {
        menu.delete_records.by_number.show_guides();
        const int sub_sub_menu_option = menu.get_input_option(3);
        if (sub_sub_menu_option == 3) {
            return; // To previous menu.
        }
        const bool range_mode = (sub_sub_menu_option == 2);
        const Range_t inputs = menu.delete_records.by_number.get_input_numbers(range_mode);
        db.sort_cities(range_mode ? field : Field::city_name, 0, range_mode);
        const vector<City> matching_records
            = db.cities_in_number_range(field, inputs.first, inputs.second);
        menu.print_matching_records(matching_records);
        if (!matching_records.empty() && menu.delete_records.confirm_user_wants_to_delete()) {
            db.delete_cities(matching_records);
            menu.delete_records.say_records_deleted(matching_records.size());
        }
        quick_nc_pause();
    } while (menu.ask_if_user_wants_to_try_again());
} // nc_do_delete_records_by_numbers_sub_menu

///////////////////////////////////////////////////////////////////////////////////////////////////

void nc_do_list_records_sub_menu(const Menu_ncurses& menu, Database& db, const Field& field);

void nc_do_list_records_menu(const Menu_ncurses& menu, Database& db) {
    menu.list_records.show_guides();
    while (true) {
        switch (getch()) {
        case '1':
            nc_do_list_records_sub_menu(menu, db, Field::city_name);
            menu.list_records.show_guides();
            break;
        case '2':
            nc_do_list_records_sub_menu(menu, db, Field::province);
            menu.list_records.show_guides();
            break;
        case '3':
            nc_do_list_records_sub_menu(menu, db, Field::province_id);
            menu.list_records.show_guides();
            break;
        case '4':
            nc_do_list_records_sub_menu(menu, db, Field::latitude);
            menu.list_records.show_guides();
            break;
        case '5':
            nc_do_list_records_sub_menu(menu, db, Field::longitude);
            menu.list_records.show_guides();
            break;
        case '6':
            nc_do_list_records_sub_menu(menu, db, Field::population);
            menu.list_records.show_guides();
            break;
        case '7':
            nc_do_list_records_sub_menu(menu, db, Field::population_density);
            menu.list_records.show_guides();
            break;
        case '8': // Return to main menu.
            return;
        default:
            nc_say_invalid_option();
        } // switch
        quick_nc_pause();
    }
} // nc_do_list_records_menu

void nc_do_list_records_sub_menu(const Menu_ncurses& menu, Database& db, const Field& field) {
    do {
        util::parse::is_string_field(field) ? menu.list_records.show_options_for_strings()
                                            : menu.list_records.show_options_for_numbers();
        const int sub_sub_menu_option = menu.get_input_option(3);
        if (sub_sub_menu_option == 3) {
            return; // To previous menu.
        }
        const bool reverse_mode = (sub_sub_menu_option == 2);
        db.sort_cities(field, reverse_mode, 0);
        menu.print_matching_records(db.get_cities());
        quick_nc_pause();
    } while (menu.ask_if_user_wants_to_try_again());
} // nc_do_list_records_sub_menu

///////////////////////////////////////////////////////////////////////////////////////////////////

// int nc_get_sub_sub_menu_option() {
//     int cur_y, cur_x;
//     getyx(stdscr, cur_y, cur_x);
// } // nc_get_sub_sub_menu_option

void nc_say_invalid_option() {
    echo();
    attron(A_BOLD | A_BLINK);
    mvprintw(12, 0, "Invalid option.");
    attroff(A_BOLD | A_BLINK);
    addstr(" ");
    noecho();
} // nc_say_invalid_option

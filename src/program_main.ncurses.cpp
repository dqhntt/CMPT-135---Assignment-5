#include "program_main.h"
#include "Database.h"
#include "Menu.ncurses.h"
#include "util.h"
using namespace std;

void quick_nc_pause() { util::time::pause(100); }

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
    while (true) {
        menu.show_main_menu();
        switch (menu.get_input_option_key('5')) {
        case '1':
            nc_do_add_records_menu(menu, db);
            break;
        case '2':
            nc_do_find_records_menu(menu, db);
            break;
        case '3':
            nc_do_delete_records_menu(menu, db);
            break;
        case '4':
            nc_do_list_records_menu(menu, db);
            break;
        case '5':
            return EXIT_SUCCESS;
        default:;
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
    while (true) {
        menu.find_records.show_guides();
        switch (menu.get_input_option_key('8')) {
        case '1':
            nc_do_find_records_by_strings_sub_menu(menu, db, Field::city_name);
            break;
        case '2':
            nc_do_find_records_by_strings_sub_menu(menu, db, Field::province);
            break;
        case '3':
            nc_do_find_records_by_strings_sub_menu(menu, db, Field::province_id);
            break;
        case '4':
            nc_do_find_records_by_numbers_sub_menu(menu, db, Field::latitude);
            break;
        case '5':
            nc_do_find_records_by_numbers_sub_menu(menu, db, Field::longitude);
            break;
        case '6':
            nc_do_find_records_by_numbers_sub_menu(menu, db, Field::population);
            break;
        case '7':
            nc_do_find_records_by_numbers_sub_menu(menu, db, Field::population_density);
            break;
        case '8': // Return to main menu.
            return;
        default:;
        } // switch
        quick_nc_pause();
    }
} // nc_do_find_records_menu

void nc_do_find_records_by_strings_sub_menu(
    const Menu_ncurses& menu, Database& db, const Field& field) {
    do {
        menu.find_records.by_string.show_guides(field);
        const char sub_sub_menu_option = menu.get_input_option_key('3');
        if (sub_sub_menu_option == '3') {
            return; // To previous menu.
        }
        const bool substring_mode = (sub_sub_menu_option == '2');
        const string input = menu.find_records.by_string.get_input_string(substring_mode);
        db.sort_cities(substring_mode ? field : Field::city_name, 0, substring_mode);
        menu.print_matching_records(db.cities_matching_string(field, substring_mode, input));
        quick_nc_pause();
    } while (menu.ask_if_user_wants_to_try_again());
} // nc_do_find_records_by_strings_sub_menu

void nc_do_find_records_by_numbers_sub_menu(
    const Menu_ncurses& menu, Database& db, const Field& field) {
    do {
        menu.find_records.by_number.show_guides(field);
        const char sub_sub_menu_option = menu.get_input_option_key('3');
        if (sub_sub_menu_option == '3') {
            return; // To previous menu.
        }
        const bool range_mode = (sub_sub_menu_option == '2');
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
    while (true) {
        menu.delete_records.show_guides();
        switch (menu.get_input_option_key('8')) {
        case '1':
            nc_do_delete_records_by_strings_sub_menu(menu, db, Field::city_name);
            break;
        case '2':
            nc_do_delete_records_by_strings_sub_menu(menu, db, Field::province);
            break;
        case '3':
            nc_do_delete_records_by_strings_sub_menu(menu, db, Field::province_id);
            break;
        case '4':
            nc_do_delete_records_by_numbers_sub_menu(menu, db, Field::latitude);
            break;
        case '5':
            nc_do_delete_records_by_numbers_sub_menu(menu, db, Field::longitude);
            break;
        case '6':
            nc_do_delete_records_by_numbers_sub_menu(menu, db, Field::population);
            break;
        case '7':
            nc_do_delete_records_by_numbers_sub_menu(menu, db, Field::population_density);
            break;
        case '8': // Return to main menu.
            return;
        default:;
        } // switch
        quick_nc_pause();
    }
} // nc_do_delete_records_menu

void nc_do_delete_records_by_strings_sub_menu(
    const Menu_ncurses& menu, Database& db, const Field& field) {
    do {
        menu.delete_records.by_string.show_guides(field);
        const char sub_sub_menu_option = menu.get_input_option_key('3');
        if (sub_sub_menu_option == '3') {
            return; // To previous menu.
        }
        const bool substring_mode = (sub_sub_menu_option == '2');
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
        menu.delete_records.by_number.show_guides(field);
        const char sub_sub_menu_option = menu.get_input_option_key('3');
        if (sub_sub_menu_option == '3') {
            return; // To previous menu.
        }
        const bool range_mode = (sub_sub_menu_option == '2');
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
    while (true) {
        menu.list_records.show_guides();
        switch (menu.get_input_option_key('8')) {
        case '1':
            nc_do_list_records_sub_menu(menu, db, Field::city_name);
            break;
        case '2':
            nc_do_list_records_sub_menu(menu, db, Field::province);
            break;
        case '3':
            nc_do_list_records_sub_menu(menu, db, Field::province_id);
            break;
        case '4':
            nc_do_list_records_sub_menu(menu, db, Field::latitude);
            break;
        case '5':
            nc_do_list_records_sub_menu(menu, db, Field::longitude);
            break;
        case '6':
            nc_do_list_records_sub_menu(menu, db, Field::population);
            break;
        case '7':
            nc_do_list_records_sub_menu(menu, db, Field::population_density);
            break;
        case '8': // Return to main menu.
            return;
        default:;
        } // switch
        quick_nc_pause();
    }
} // nc_do_list_records_menu

void nc_do_list_records_sub_menu(const Menu_ncurses& menu, Database& db, const Field& field) {
    do {
        util::parse::is_string_field(field) ? menu.list_records.show_options_for_strings(field)
                                            : menu.list_records.show_options_for_numbers(field);
        const char sub_sub_menu_option = menu.get_input_option_key('3');
        if (sub_sub_menu_option == '3') {
            return; // To previous menu.
        }
        const bool reverse_mode = (sub_sub_menu_option == '2');
        db.sort_cities(field, reverse_mode, 0);
        menu.print_matching_records(db.get_cities());
        quick_nc_pause();
    } while (menu.ask_if_user_wants_to_try_again());
} // nc_do_list_records_sub_menu

///////////////////////////////////////////////////////////////////////////////////////////////////

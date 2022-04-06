#include "program_main.h"
#include "Database.h"
#include "Menu.h"
#include "cmpt_error.h"
#include "util.time.h"

using namespace std;

int program_main() { // Menu controller.

    // TODO: Implement the program without ncurses.

    Database db;
    try {
        db.open("database.txt");
    } catch (const exception&) {
        try {
            db.open("../data/database.txt");
        } catch (const exception&) { db.open("../data/test_database.txt"); }
    }

    const Menu menu;
    Menu_Option main_menu_option = Menu_Option::invalid_option;

    while (main_menu_option != Menu_Option::five) { // 5 = Quit.
        // MAIN MENU.
        menu.show_main_menu();
        main_menu_option = menu.get_input_option(5);
        switch (main_menu_option) {
        // MENU #1 - Add a record.
        case Menu_Option::one: {
            menu.add_records.show_guides();
            City city = menu.add_records.get_input();
            bool record_exists = db.exists_record(city);
            while (record_exists) {
                util::time::pause(100);
                menu.add_records.say_record_exists(city);
                if (menu.ask_if_user_wants_to_try_again()) {
                    city = menu.add_records.get_input();
                    record_exists = db.exists_record(city);
                } else {
                    break;
                }
            } // while
            if (!record_exists) {
                db.add_city(city);
                util::time::pause(100);
                menu.add_records.say_record_added(city);
            }
        } break;
        // MENU #2 - Find a record.
        case Menu_Option::two: {
            Menu_Option sub_menu_option = Menu_Option::invalid_option;
            while (sub_menu_option != Menu_Option::eight) { // 8 = Return to main menu.
                menu.find_records.show_guides();
                sub_menu_option = menu.get_input_option(8);
                switch (sub_menu_option) {
                case Menu_Option::one:   // By city name.
                case Menu_Option::two:   // By province.
                case Menu_Option::three: // By province id.
                    do {
                        menu.find_records.by_string.show_guides();
                        const bool substring_mode = (menu.get_input_option(2) == Menu_Option::two);
                        const string input
                            = menu.find_records.by_string.get_input_string(substring_mode);
                        const Field field
                            = (sub_menu_option == Menu_Option::one) ? Field::city_name
                            : (sub_menu_option == Menu_Option::two) ? Field::province
                                                                    : Field::province_id;
                        db.sort_cities(field);
                        menu.print_records(db.cities_matching_string(field, substring_mode, input));
                    } while (menu.ask_if_user_wants_to_try_again());
                    break;
                case Menu_Option::four:  // By latitude.
                case Menu_Option::five:  // By longitude.
                case Menu_Option::six:   // By population.
                case Menu_Option::seven: // By population density.
                    do {
                        menu.find_records.by_number.show_guides();
                        const bool range_mode = (menu.get_input_option(2) == Menu_Option::two);
                        const Range_t inputs
                            = menu.find_records.by_number.get_input_numbers(range_mode);
                        const Field field
                            = (sub_menu_option == Menu_Option::four) ? Field::latitude
                            : (sub_menu_option == Menu_Option::five) ? Field::longitude
                            : (sub_menu_option == Menu_Option::six)  ? Field::population
                                                                     : Field::population_density;
                        db.sort_cities(field);
                        menu.print_records(
                            db.cities_in_number_range(field, inputs.first, inputs.second));
                    } while (menu.ask_if_user_wants_to_try_again());
                    break;
                case Menu_Option::eight: // Return to main menu.
                    break;
                default:
                    cmpt::error("Invalid / Unimplemented menu option.");
                } // switch
                util::time::pause(150);
            } // while
        } break;
        // MENU #3 - Delete a record.
        case Menu_Option::three: {
            Menu_Option sub_menu_option = Menu_Option::invalid_option;
            while (sub_menu_option != Menu_Option::eight) { // 8 = Return to main menu.
                menu.delete_records.show_guides();
                sub_menu_option = menu.get_input_option(8);
                switch (sub_menu_option) {
                case Menu_Option::one:   // By city name.
                case Menu_Option::two:   // By province.
                case Menu_Option::three: // By province id.
                    do {
                        menu.delete_records.by_string.show_guides();
                        const bool substring_mode = (menu.get_input_option(2) == Menu_Option::two);
                        const string input
                            = menu.delete_records.by_string.get_input_string(substring_mode);
                        const Field field
                            = (sub_menu_option == Menu_Option::one) ? Field::city_name
                            : (sub_menu_option == Menu_Option::two) ? Field::province
                                                                    : Field::province_id;
                        db.sort_cities(field);
                        const vector<City> matching_records
                            = db.cities_matching_string(field, substring_mode, input);
                        menu.print_records(matching_records);
                        if (!matching_records.empty()
                            && menu.delete_records.confirm_user_wants_to_delete()) {
                            db.delete_cities(matching_records);
                            util::time::pause(100);
                            menu.delete_records.say_records_deleted(matching_records.size());
                        }
                    } while (menu.ask_if_user_wants_to_try_again());
                    break;
                case Menu_Option::four:  // By latitude.
                case Menu_Option::five:  // By longitude.
                case Menu_Option::six:   // By population.
                case Menu_Option::seven: // By population density.
                    do {
                        menu.delete_records.by_number.show_guides();
                        const bool range_mode = (menu.get_input_option(2) == Menu_Option::two);
                        const Range_t inputs
                            = menu.delete_records.by_number.get_input_numbers(range_mode);
                        const Field field
                            = (sub_menu_option == Menu_Option::four) ? Field::latitude
                            : (sub_menu_option == Menu_Option::five) ? Field::longitude
                            : (sub_menu_option == Menu_Option::six)  ? Field::population
                                                                     : Field::population_density;
                        db.sort_cities(field);
                        const vector<City> matching_records
                            = db.cities_in_number_range(field, inputs.first, inputs.second);
                        menu.print_records(matching_records);
                        if (!matching_records.empty()
                            && menu.delete_records.confirm_user_wants_to_delete()) {
                            db.delete_cities(matching_records);
                            util::time::pause(100);
                            menu.delete_records.say_records_deleted(matching_records.size());
                        }
                    } while (menu.ask_if_user_wants_to_try_again());
                    break;
                case Menu_Option::eight: // Return to main menu.
                    break;
                default:
                    cmpt::error("Invalid / Unimplemented menu option.");
                } // switch
                util::time::pause(150);
            } // while
        } break;
        // MENU #4 - List records.
        // case Menu_Options::four:
        //     // TODO
        //     break;
        // MENU #5 - Quit.
        case Menu_Option::five:
            break;
        default:
            cmpt::error("Invalid / Unimplemented menu option.");
        } // switch
        util::time::pause(150);
    } // while
    return EXIT_SUCCESS;
}

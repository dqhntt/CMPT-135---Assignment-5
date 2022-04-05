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
        db.open("../data/test_database.txt");
    } catch (const exception&) {
        try {
            db.open("../data/database.txt");
        } catch (const exception&) { db.open("database.txt"); }
    }

    const Menu   menu;
    Menu_Options main_menu_option = Menu_Options::invalid_option;

    while (main_menu_option != Menu_Options::five) { // 5 = Quit.
        menu.show_main_menu();
        main_menu_option = menu.get_input_option(5);
        switch (main_menu_option) {
        case Menu_Options::one: { // Add a record.
            menu.add_records.show_guides();
            City city = menu.add_records.get_input();
            bool record_exists = db.exists_record(city);
            while (record_exists) {
                util::time::pause(100);
                menu.add_records.say_record_exists(city);
                if (menu.add_records.ask_if_user_wants_to_try_again()) {
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
        case Menu_Options::two: { // Find a record.
            Menu_Options sub_menu_option = Menu_Options::invalid_option;
            while (sub_menu_option != Menu_Options::eight) { // 8 = Return to main menu.
                menu.find_records.show_guides();
                sub_menu_option = menu.get_input_option(8);
                switch (sub_menu_option) {
                case Menu_Options::one:     // By city name.
                case Menu_Options::two:     // By province.
                case Menu_Options::three: { // By province id.
                    menu.find_records.by_string.show_guides();
                    const Menu_Options sub_sub_menu_option = menu.get_input_option(2);
                    const string       input
                        = menu.find_records.by_string.get_input_string(sub_sub_menu_option);
                    const Field field
                        = (sub_menu_option == Menu_Options::one) ? Field::city_name
                        : (sub_menu_option == Menu_Options::two) ? Field::province
                                                                 : Field::province_id;
                    menu.print_records(db.cities_matching_string(
                        field, (sub_sub_menu_option == Menu_Options::two), input)); // 2 = substr.
                } break;
                case Menu_Options::four:    // By latitude.
                case Menu_Options::five:    // By longitude.
                case Menu_Options::six:     // By population.
                case Menu_Options::seven: { // By population density.
                    menu.find_records.by_number.show_guides();
                    const Menu_Options sub_sub_menu_option = menu.get_input_option(2);
                    const Num_range_t  input
                        = menu.find_records.by_number.get_input_number(sub_sub_menu_option);
                    const Field field
                        = (sub_menu_option == Menu_Options::four) ? Field::latitude
                        : (sub_menu_option == Menu_Options::five) ? Field::longitude
                        : (sub_menu_option == Menu_Options::six)  ? Field::population
                                                                  : Field::population_density;
                    menu.print_records(db.cities_in_number_range(field, input.low, input.high));
                } break;
                case Menu_Options::eight: // Return to main menu.
                    break;
                default:
                    cmpt::error("Invalid/Unimplemented menu option.");
                } // switch
                util::time::pause(150);
            } // while
        } break;
        // case Menu_Options::three: // Delete a record.
        //     // TODO
        //     break;
        // case Menu_Options::four: // List records.
        //     // TODO
        //     break;
        case Menu_Options::five: // Quit menu.
            break;
        default:
            cmpt::error("Invalid/Unimplemented menu option.");
        } // switch
        util::time::pause(150);
    } // while
    return EXIT_SUCCESS;
}

#include "program_main.h"
#include "Database.h"
#include "Menu.h"
#include "cmpt_error.h"
#include "util.time.h"

using namespace std;

inline void quick_pause() { util::time::pause(100); }

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
            do {
                menu.add_records.show_guides();
                City city = menu.add_records.get_input();
                bool record_exists = db.exists_record(city);
                while (record_exists) {
                    quick_pause();
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
                    quick_pause();
                    menu.add_records.say_record_added(city);
                }
                quick_pause();
            } while (menu.ask_if_user_wants_to_try_again());
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
                        const Menu_Option sub_sub_menu_option = menu.get_input_option(3);
                        if (sub_sub_menu_option == Menu_Option::three) {
                            break; // To previous menu.
                        }
                        const bool substring_mode = (sub_sub_menu_option == Menu_Option::two);
                        const string input
                            = menu.find_records.by_string.get_input_string(substring_mode);
                        const Field field
                            = (sub_menu_option == Menu_Option::one) ? Field::city_name
                            : (sub_menu_option == Menu_Option::two) ? Field::province
                                                                    : Field::province_id;
                        db.sort_cities(field);
                        menu.print_records(db.cities_matching_string(field, substring_mode, input));
                        quick_pause();
                    } while (menu.ask_if_user_wants_to_try_again());
                    break;
                case Menu_Option::four:  // By latitude.
                case Menu_Option::five:  // By longitude.
                case Menu_Option::six:   // By population.
                case Menu_Option::seven: // By population density.
                    do {
                        menu.find_records.by_number.show_guides();
                        const Menu_Option sub_sub_menu_option = menu.get_input_option(3);
                        if (sub_sub_menu_option == Menu_Option::three) {
                            break; // To previous menu.
                        }
                        const bool range_mode = (sub_sub_menu_option == Menu_Option::two);
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
                        quick_pause();
                    } while (menu.ask_if_user_wants_to_try_again());
                    break;
                case Menu_Option::eight: // Return to main menu.
                    break;
                default:
                    cmpt::error("Invalid / Unimplemented menu option.");
                } // switch
                quick_pause();
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
                        const Menu_Option sub_sub_menu_option = menu.get_input_option(3);
                        if (sub_sub_menu_option == Menu_Option::three) {
                            break; // To previous menu.
                        }
                        const bool substring_mode = (sub_sub_menu_option == Menu_Option::two);
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
                            menu.delete_records.say_records_deleted(matching_records.size());
                        }
                        quick_pause();
                    } while (menu.ask_if_user_wants_to_try_again());
                    break;
                case Menu_Option::four:  // By latitude.
                case Menu_Option::five:  // By longitude.
                case Menu_Option::six:   // By population.
                case Menu_Option::seven: // By population density.
                    do {
                        menu.delete_records.by_number.show_guides();
                        const Menu_Option sub_sub_menu_option = menu.get_input_option(3);
                        if (sub_sub_menu_option == Menu_Option::three) {
                            break; // To previous menu.
                        }
                        const bool range_mode = (sub_sub_menu_option == Menu_Option::two);
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
                            menu.delete_records.say_records_deleted(matching_records.size());
                        }
                        quick_pause();
                    } while (menu.ask_if_user_wants_to_try_again());
                    break;
                case Menu_Option::eight: // Return to main menu.
                    break;
                default:
                    cmpt::error("Invalid / Unimplemented menu option.");
                } // switch
                quick_pause();
            } // while
        } break;
        // MENU #4 - List records.
        case Menu_Option::four: {
            Menu_Option sub_menu_option = Menu_Option::invalid_option;
            while (sub_menu_option != Menu_Option::eight) { // 8 = Return to main menu.
                menu.list_records.show_guides();
                sub_menu_option = menu.get_input_option(8);
                Field field;
                bool string_field;
                switch (sub_menu_option) {
                case Menu_Option::one:   // By city name.
                    field = Field::city_name;
                    string_field = true;
                    break;
                case Menu_Option::two:   // By province.
                    field = Field::province;
                    string_field = true;
                    break;
                case Menu_Option::three: // By province id.
                    field = Field::province_id;
                    string_field = true;
                    break;
                case Menu_Option::four:  // By latitude.
                    field = Field::latitude;
                    string_field = false;
                    break;
                case Menu_Option::five:  // By longitude.
                    field = Field::longitude;
                    string_field = false;
                    break;
                case Menu_Option::six:   // By population.
                    field = Field::population;
                    string_field = false;
                    break;
                case Menu_Option::seven: // By population density.
                    field = Field::population_density;
                    string_field = false;
                    break;
                case Menu_Option::eight: // Return to main menu.
                    break;
                default:
                    cmpt::error("Invalid / Unimplemented menu option.");
                }
                if (sub_menu_option == Menu_Option::eight) {
                    break; // Return to main menu.
                }
                do {
                    string_field ? menu.list_records.show_options_for_strings()
                                 : menu.list_records.show_options_for_numbers();
                    const Menu_Option sub_sub_menu_option = menu.get_input_option(3);
                    if (sub_sub_menu_option == Menu_Option::three) {
                        break; // To previous menu.
                    }
                    const bool reverse_mode = (sub_sub_menu_option == Menu_Option::two);
                    db.sort_cities(field, reverse_mode);
                    menu.print_records(db.get_cities());
                    quick_pause();
                } while (menu.ask_if_user_wants_to_try_again());
                quick_pause();
            } // while
        } break;
        // case Menu_Option::four: {
        //     Menu_Option sub_menu_option = Menu_Option::invalid_option;
        //     while (sub_menu_option != Menu_Option::eight) { // 8 = Return to main menu.
        //         menu.list_records.show_guides();
        //         sub_menu_option = menu.get_input_option(8);
        //         switch (sub_menu_option) {
        //         case Menu_Option::one:   // By city name.
        //         case Menu_Option::two:   // By province.
        //         case Menu_Option::three: // By province id.
        //             do {
        //                 menu.list_records.show_options_for_strings();
        //                 const Menu_Option sub_sub_menu_option = menu.get_input_option(3);
        //                 if (sub_sub_menu_option == Menu_Option::three) {
        //                     break; // To previous menu.
        //                 }
        //                 const bool reversed_alpha_mode = (sub_sub_menu_option == Menu_Option::two);
        //                 const Field field
        //                     = (sub_menu_option == Menu_Option::one) ? Field::city_name
        //                     : (sub_menu_option == Menu_Option::two) ? Field::province
        //                                                             : Field::province_id;
        //                 db.sort_cities(field, reversed_alpha_mode);
        //                 menu.print_records(db.get_cities());
        //                 quick_pause();
        //             } while (menu.ask_if_user_wants_to_try_again());
        //             break;
        //         case Menu_Option::four:  // By latitude.
        //         case Menu_Option::five:  // By longitude.
        //         case Menu_Option::six:   // By population.
        //         case Menu_Option::seven: // By population density.
        //             do {
        //                 menu.list_records.show_options_for_numbers();
        //                 const Menu_Option sub_sub_menu_option = menu.get_input_option(3);
        //                 if (sub_sub_menu_option == Menu_Option::three) {
        //                     break; // To previous menu.
        //                 }
        //                 const bool descending_mode = (sub_sub_menu_option == Menu_Option::two);
        //                 const Field field
        //                     = (sub_menu_option == Menu_Option::four) ? Field::latitude
        //                     : (sub_menu_option == Menu_Option::five) ? Field::longitude
        //                     : (sub_menu_option == Menu_Option::six)  ? Field::population
        //                                                              : Field::population_density;
        //                 db.sort_cities(field, descending_mode);
        //                 menu.print_records(db.get_cities());
        //                 quick_pause();
        //             } while (menu.ask_if_user_wants_to_try_again());
        //             break;
        //         case Menu_Option::eight: // Return to main menu.
        //             break;
        //         default:
        //             cmpt::error("Invalid / Unimplemented menu option.");
        //         } // switch
        //         quick_pause();
        //     } // while
        // } break;
        // MENU #5 - Quit.
        case Menu_Option::five:
            break;
        default:
            cmpt::error("Invalid / Unimplemented menu option.");
        } // switch
        quick_pause();
    } // while
    return EXIT_SUCCESS;
}

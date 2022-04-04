#include "program_main.h"
#include "Database.h"
#include "Menu.h"
#include "cmpt_error.h"

#include <iostream>

// #include < ...something... >

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
    Menu_Options menu_option;

    do {
        menu.show_main_menu();
        menu_option = menu.get_input_option();

        switch (menu_option) {
        case Menu_Options::one: {
            menu.add_records.show_guides();
            City city = menu.add_records.get_input();
            bool record_exists = db.exists_record(city);
            while (record_exists) {
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
                menu.add_records.say_record_added(city);
            }
            break;
        }
        // case Menu_Options::two:
        //     // TODO
        //     break;
        // case Menu_Options::three:
        //     // TODO
        //     break;
        // case Menu_Options::four:
        //     // TODO
        //     break;
        case Menu_Options::five:
            return EXIT_SUCCESS;
        case Menu_Options::invalid_option:
            return EXIT_FAILURE;
        default:
            cmpt::error("Unimplemented menu option.");
        } // switch

    } while (menu_option != Menu_Options::invalid_option);

    return EXIT_FAILURE;
}

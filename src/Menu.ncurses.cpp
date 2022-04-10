#include "Menu.ncurses.h"
#include "cmpt_error.h"
#include "util.h"
using namespace std;

Menu_ncurses::Menu_ncurses() {
    refresh();
    getmaxyx(stdscr, _max_y, _max_x);
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(2, COLOR_BLUE, COLOR_WHITE);
    init_pair(3, COLOR_RED, COLOR_WHITE);
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    scrollok(stdscr, TRUE);
}

void show_loading_bar_ncurses(
    int how_many_bars, const string& bar = "-", int total_milliseconds = 250) {
    for (int i = 0; i < how_many_bars; i++) {
        printw(bar.c_str());
        refresh();
        util::time::pause(total_milliseconds / how_many_bars);
    }
    printw("\n");
}

Menu_ncurses::~Menu_ncurses() {
    printw("\nSaving data to file before exiting");
    show_loading_bar_ncurses(5, ".", 2000);
}

int Menu_ncurses::get_input_option(int max_options) const {
    int cur_y, cur_x;
    getyx(stdscr, cur_y, cur_x);
    WINDOW* new_box = subwin(stdscr, 6, 45, cur_y + 2, 1);
    box(new_box, '|', '-');
    touchwin(stdscr);
    mvwprintw(new_box, 2, 1, "Enter the option number of your choice: ");
    echo();
    int key = wgetch(new_box);
    while (key < '1' || key > (max_options + '0')) {
        attron(A_BOLD | A_BLINK);
        mvwprintw(new_box, 4, 1, "Invalid option.");
        attroff(A_BOLD | A_BLINK);
        wmove(new_box, 2, 41);
        touchwin(stdscr);
        key = wgetch(new_box);
    }
    werase(new_box);
    delwin(new_box);
    refresh();
    return key;
}

// print records if the cites exist
void Menu_ncurses::print_matching_records(const vector<City>& records) const {
    printw("Here is a list of matching cities:");
    printw("[Name ; Province ; Province-ID ; Latitude ; Longitude ; Population ; ");
    printw("Population-Density]");
    refresh();
    int count = 1;
    bkgd(COLOR_PAIR(2));
    for (const City& city : records) {
        printw("\n%d) [%s];", count++, city.name.c_str());
        printw("\n%s];[%s];[%.3f];[%.3f];[%d];[%.2f]", city.province.c_str(),
            city.province_id.c_str(), city.latitude, city.longitude, city.population,
            city.population_density);
        //This is to solve the problem that the screen cannot display all the cities together
        if(count % 9 == 0){ // Do it every 9 cities
            printw("\n\nPress \"down\" key to go to the next page,"
                   "\nOR press 's' to skip the displaying process.\n\n");
            noecho();
            int key = getch();
            while(key != KEY_DOWN){
                if(key == 's' || key == 'S'){
                    printw("...\n\n");
                    goto finish; //stop printing
                }
                //If user enters other keys, do nothing and get the next input
                key = getch(); 
            }
        } // if 
        
    }
    finish:
    printw("Total = %d records found.\n\n", records.size());
    
    
}

void Menu_ncurses::show_main_menu() const {
    clear();
    move(2, 0);
    show_loading_bar_ncurses(33);
    printw("\n| Welcome to the City Database! |\n");
    show_loading_bar_ncurses(33);
    printw("\n"
           "\n"
           "(1) Add a city.\n"
           "(2) Find a city.\n"
           "(3) Delete a city.\n"
           "(4) List cities.\n"
           "(5) Quit");
    refresh();
}

void Menu_ncurses::Add_records::show_guides() const {
    clear();
    mvprintw(1, 0, "Add a City\n");
    show_loading_bar_ncurses(10);
    printw("\n"
           "A city has a:\n"
           "- Name\n"
           "- Province it's in\n"
           "- That province's abbreviation\n"
           "- Latitude\n"
           "- Longitude\n"
           "- Population size\n"
           "- Population density\n"
           "\n"
           "e.g. Vancouver is a city in British Columbia (BC)\n"
           "     located at coordinate: 49.25 N, -123.1 W\n"
           "     once with a population of 2,264,823 people and\n"
           "     a population density of 5,492.6 people per km^2\n");
    refresh();
}

// // Request new string as needed until it doesn't contain ";".
// // Works just like std::getline with added feature to request correct input.
string get_string_no_semicolon() {
    char str[80];
    getstr(str);
    string input_str(str);
    while (input_str.find(';') != string::npos) {
        printw("\n"
               "Semicolons are reserved for file formatting.\n"
               "Please try again with no \";\" added: ");
        getstr(str);
        input_str = str;
    }
    return util::parse::trim(input_str);
}

void nc_get_input_for_province_id(City& city) {
    city.province_id = get_string_no_semicolon();
    while (city.province_id.size() > city.province.size()) {
        printw("\n"
               "Hmm... That's actually longer than: %s\n"
               "Try entering a shorter one: ",
            city.province.c_str());
        city.province_id = get_string_no_semicolon();
    }
}

void nc_get_input_for_latitude(City& city) {
    string input = get_string_no_semicolon();
    while (!util::parse::is_valid_DD_latitude(input)) {
        printw("\n"
               "You entered an invalid latitude.\n"
               "Please use only decimal degrees from -90.0 to 90.0.\n"
               "Please try again: ");
        input = get_string_no_semicolon();
    }
    city.latitude = stod(input);
}

void nc_get_input_for_longitude(City& city) {
    string input = get_string_no_semicolon();
    while (!util::parse::is_valid_DD_longitude(input)) {
        printw("\n"
               "You entered an invalid longitude.\n"
               "Please use only decimal degrees from -180.0 to 180.0.\n"
               "Please try again: ");
        input = get_string_no_semicolon();
    }
    city.longitude = stod(input);
}

void nc_get_input_for_population(City& city) {
    string input = get_string_no_semicolon();
    while (!util::parse::is_valid_num<int>(input) || stoi(input) < 0) {
        printw("\n"
               "You entered an invalid population.\n"
               "It should be a non-negative integer. Please try again: ");
        input = get_string_no_semicolon();
    }
    city.population = stoi(input);
}

void nc_get_input_for_population_density(City& city) {
    string input = get_string_no_semicolon();
    while (!util::parse::is_valid_num<double>(input) || stod(input) > city.population
        || stod(input) < 0.0) {
        printw("\n"
               "You entered an invalid population density.\n"
               "It should be non-negative and less than the population. Please try again: ");
        input = get_string_no_semicolon();
    }
    city.population_density = stod(input);
}

// // Only to provide consistent naming.
void nc_get_input_and_add_to(City& city, const Field& field) {
    switch (field) {
    case Field::city_name:
        city.name = get_string_no_semicolon();
        break;
    case Field::province:
        city.province = get_string_no_semicolon();
        break;
    case Field::province_id:
        nc_get_input_for_province_id(city);
        break;
    case Field::latitude:
        nc_get_input_for_latitude(city);
        break;
    case Field::longitude:
        nc_get_input_for_longitude(city);
        break;
    case Field::population:
        nc_get_input_for_population(city);
        break;
    case Field::population_density:
        nc_get_input_for_population_density(city);
        break;
    default:
        cmpt::error("Unknown Field in: " + string(__func__) + "(). File: " + string(__FILE__));
    }
}

City Menu_ncurses::Add_records::get_input() const {
    City city;
    echo();
    addstr("\n"
           "Enter the characteristics of your new city to be added:\n"
           "\n"
           "- City name: ");
    nc_get_input_and_add_to(city, Field::city_name);
    printw("- Its province: ");
    nc_get_input_and_add_to(city, Field::province);
    printw("- That province's shorter name: ");
    nc_get_input_and_add_to(city, Field::province_id);
    printw("- City's latitude: ");
    nc_get_input_and_add_to(city, Field::latitude);
    printw("- Its longitude: ");
    nc_get_input_and_add_to(city, Field::longitude);
    printw("- City's population: ");
    nc_get_input_and_add_to(city, Field::population);
    printw("- Its population density: ");
    nc_get_input_and_add_to(city, Field::population_density);
    noecho();
    return city;
}

bool Menu_ncurses::ask_if_user_wants_to_try_again() const {
    printw("\n"
           "Would you like to try again? (y/n): ");
    echo();
    int yn = getch();
    while(yn != 'y' && yn != 'Y' && yn != 'n' && yn != 'N'){
        printw("\nPlease press either 'y' or 'n': ");
        yn = getch();
    }
    noecho();
    return (yn == 'y' || yn == 'Y');
}

void nc_print_single_record(const City& city) {
    printw("City:\n"
           "+ Name: %s\n"
           "+ Province: %s\n"
           "+ Province Code: %s\n"
           "+ Latitude: %.3f North\n"
           "+ Longitude: %.3f West\n"
           "+ Population: %d people\n"
           "+ Population Density: %.2f people per km^2\n",
        city.name.c_str(), city.province.c_str(), city.province_id.c_str(), city.latitude,
        city.longitude, city.population, city.population_density);
    refresh();
}

void Menu_ncurses::Add_records::say_record_exists(const City& city) const {
    printw("\n"
           "This record already exists in the database!\n");
    nc_print_single_record(city);
}

void Menu_ncurses::Add_records::say_record_added(const City& city) const {
    printw("\n"
           "This record has been successfully added to the database.\n");
    nc_print_single_record(city);
}

void nc_show_menu_options_for_possible_fields() {
    printw("\n"
           "(1) City name\n"
           "(2) Province it's in\n"
           "(3) Province code\n"
           "(4) Latitude\n"
           "(5) Longitude\n"
           "(6) Population size\n"
           "(7) Population density\n"
           "\n"
           "(8) Return to main menu\n"
           "\n");
    refresh();
}

void Menu_ncurses::Find_records::show_guides() const {
    clear();
    printw("\n"
           "Find a City\n");
    show_loading_bar_ncurses(11);
    printw("\n"
           "You can find cities by:\n");
    nc_show_menu_options_for_possible_fields();
}

void Menu_ncurses::By_string::show_guides() const {
    clear();
    printw("\n"
           "Searching by strings\n");
    show_loading_bar_ncurses(20);
    printw("\n"
           "You can search for exact or partial matches to your input.\n"
           "NOTE: queries are case-sensitive, i.e., Van != van\n"
           "\n"
           "(1) Exact matches\n"
           "(2) Partial/substring matches\n"
           "\n"
           "(3) Return to previous menu\n"
           "\n");
    refresh();
}

string nc_get_input_string_trimmed() {
    char str[80];
    getstr(str);
    return util::parse::trim(str);
}

string Menu_ncurses::By_string::get_input_string(bool substr_mode) const {
    printw("Enter a %sstring to search for: ", (substr_mode ? "sub" : ""));
    return nc_get_input_string_trimmed();
}

void Menu_ncurses::By_number::show_guides() const {
    clear();
    printw("\n"
           "Searching by numbers\n");
    show_loading_bar_ncurses(20);
    printw("\n"
           "You can search for exact matches or matches in a range of numbers.\n"
           "\n"
           "(1) Exact number matches\n"
           "(2) Matches in a range of numbers\n"
           "\n"
           "(3) Return to previous menu\n"
           "\n");
    refresh();
}

Range_t Menu_ncurses::By_number::get_input_numbers(bool range_mode) const {
    printw(
        "Enter a %s to search for: ", (!range_mode ? "number" : "range of numbers, one by one,"));
    char str[80];
    // Get first number.
    getstr(str);
    while (!util::parse::is_valid_num(str)) {
        printw("Not a single number. Please try again: ");
        getstr(str);
    }
    const double range_low = stod(str);
    // If only one number is desired.
    if (!range_mode) {
        return make_pair(range_low, range_low);
    }
    // Else get range.
    printw("End range: ");
    getstr(str);
    while (!util::parse::is_valid_num(str)) {
        printw("Not a single number. Please try again: ");
        getstr(str);
    }
    const double range_high = stod(str);
    if (range_low > range_high) {
        return make_pair(range_high, range_low);
    }
    return make_pair(range_low, range_high);
}

void Menu_ncurses::Delete_records::show_guides() const {
    clear();
    printw("\n"
           "Delete a City\n");
    show_loading_bar_ncurses(13);
    printw("\n"
           "You can search and delete cities by:\n");
    nc_show_menu_options_for_possible_fields();
}

bool Menu_ncurses::Delete_records::confirm_user_wants_to_delete() const {
    printw("Are you sure you want to delete the record(s) above? (y/n): ");
    char yn = getch();
    return (yn == 'y' || yn == 'Y');
}

void Menu_ncurses::Delete_records::say_records_deleted(int how_many) const {
    printw("\n");
    if (how_many >= 0) {
        printw("%d", how_many);
    }
    printw("matching records deleted successfully.\n"
           "\n");
    refresh();
}

void Menu_ncurses::List_records::show_guides() const {
    clear();
    printw("\n"
           "List Cities\n");
    show_loading_bar_ncurses(11);
    printw("\n"
           "Cities can be listed in sorted order by:\n");
    nc_show_menu_options_for_possible_fields();
}

void Menu_ncurses::List_records::show_options_for_strings() const {
    clear();
    printw("\n"
           "Listing by strings\n");
    show_loading_bar_ncurses(18);
    printw("\n"
           "Categorical fields in records can be listed in:\n"
           "\n"
           "(1) Alphabetical order\n"
           "(2) Reverse alphabetical order\n"
           "\n"
           "(3) Return to previous menu\n"
           "\n");
    refresh();
}

void Menu_ncurses::List_records::show_options_for_numbers() const {
    clear();
    printw("\n"
           "Listing by numbers\n");
    show_loading_bar_ncurses(18);
    printw("\n"
           "Numerical fields in records can be listed in:\n"
           "\n"
           "(1) Ascending order\n"
           "(2) Descending order\n"
           "\n"
           "(3) Return to previous menu\n"
           "\n");
    refresh();
}

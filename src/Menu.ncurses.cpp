#include "Menu.ncurses.h"
#include "cmpt_error.h"
#include "util.h"
#include <iostream>
using namespace std;


Menu_ncurses::Menu_ncurses()
    : _start_time(time(0))
{ }

void show_loading_bar_ncurses(int how_many_bars, string bar = "-", int total_milliseconds = 250) {
    for (int i = 0; i < how_many_bars; i++) {
        printw(bar.c_str());
        util::time::pause(total_milliseconds / how_many_bars);
    }
}

Menu_ncurses::~Menu_ncurses() {
    cout << "Saving data to file before exiting";
    show_loading_bar_ncurses(5, ".", 1000);
    cout << "Thanks for spending " << (time(0) - _start_time) / 60.0 << " minutes with us!\n";
}

//print records if the cites exist
void Menu_ncurses::print_records(const vector<City>& records, WINDOW* rec) const {
    // Put commas in numbers.
    const util::format::Commas_thousands_sep_RAII formatter(cout);
  
    printw("Here is a list of matching cities:");
    move(1, 0);
    printw("(Name ; Province ; Province-ID ; Latitude ; Longitude ; Population ; ");
    printw("Population-Density)");
    refresh();

    int count = 1;
    wbkgd(rec, COLOR_PAIR(2));
    for (const City& city : records) {
        waddstr(rec, to_string(count++).c_str());
        waddstr(rec, ") [");
        waddstr(rec, city.name.c_str());
        waddstr(rec, "];");
        mvwaddstr(rec,1,0,"[");
        waddstr(rec, city.province.c_str());
        waddstr(rec, "];[");
        waddstr(rec, city.province_id.c_str());
        waddstr(rec, "];[");
        waddstr(rec, to_string(city.latitude).c_str());
        waddstr(rec, "];[");
        waddstr(rec, to_string(city.longitude).c_str());
        waddstr(rec, "];[");
        waddstr(rec, to_string(city.population).c_str());
        waddstr(rec, "];[");
        waddstr(rec, to_string(city.population_density).c_str());
        waddstr(rec, "]");
    }    
    mvwaddstr(rec, 1, 0, "Total = ");
    waddstr(rec, to_string(records.size()).c_str());
    waddstr(rec, " records found.");
}

void Menu_ncurses::show_main_menu() const {
    move(2,0);
    show_loading_bar_ncurses(29);
    mvprintw(3, 0,"Welcome to the City Database!");
    mvprintw(4, 0, "(1) Add a city.");
    mvprintw(5, 0, "(2) Find a city.");
    mvprintw(6, 0, "(3) Delete a city.");
    mvprintw(7, 0, "(4) List cities.");
    mvprintw(8, 0, "(5) Quit");    
}

// Menu_Option Menu_ncurses::get_input_option(int max_options) const {
//     cout << "Enter the option number of your choice: ";
//     string input;
//     getline(cin, input);
//     Menu_Option option = util::parse::convert_to_menu_option(input, max_options);
//     while (option == Menu_Option::invalid_option) {
//         cout << "You entered an invalid option. Please try again: ";
//         getline(cin, input);
//         option = util::parse::convert_to_menu_option(input, max_options);
//     }
//     return option;
// }

// void Menu_ncurses::Add_records::show_guides() const {
//     cout << "\n"
//             "Add a City\n";
//     show_loading_bar(10);
//     cout << "\n"
//             "A city has a:\n"
//             "- Name\n"
//             "- Province it's in\n"
//             "- That province's abbreviation\n"
//             "- Latitude\n"
//             "- Longitude\n"
//             "- Population size\n"
//             "- Population density\n"
//             "\n"
//             "e.g. Vancouver is a city in British Columbia (BC)\n"
//             "     located at coordinate (N, W): 49.25, -123.1 (DD)\n"
//             "     once with a population of 2,264,823 people and\n"
//             "     a population density of 5,492.6 people per km^2\n"
//             "\n";
// }

// // Request new string as needed until it doesn't contain ";".
// // Works just like std::getline with added feature to request correct input.
// istream& getline_no_semicolon_and_trim(istream& is, string& str) {
//     std::getline(is, str);
//     while (str.find(';') != string::npos) {
//         cout << "Semicolons are reserved for file formatting.\n"
//              << "Please try again with no \";\" added: ";
//         std::getline(is, str);
//     }
//     util::parse::trim(str);
//     return is;
// }

// void get_input_for_province_id(City& city) {
//     getline_no_semicolon_and_trim(cin, city.province_id);
//     while (city.province_id.size() > city.province.size()) {
//         cout << "Hmm... That's actually longer than: " << city.province << "\n"
//              << "Try entering a shorter one: ";
//         getline_no_semicolon_and_trim(cin, city.province_id);
//     }
// }

// void get_input_for_latitude(City& city) {
//     string input;
//     getline(cin, input);
//     while (!util::parse::is_valid_DD_latitude(input)) {
//         cout << "You entered an invalid latitude.\n"
//                 "Please use only decimal degrees from -90.0 to 90.0.\n"
//                 "Please try again: ";
//         getline(cin, input);
//     }
//     city.latitude = stod(input);
// }

// void get_input_for_longitude(City& city) {
//     string input;
//     getline(cin, input);
//     while (!util::parse::is_valid_DD_longitude(input)) {
//         cout << "You entered an invalid longitude.\n"
//                 "Please use only decimal degrees from -180.0 to 180.0.\n"
//                 "Please try again: ";
//         getline(cin, input);
//     }
//     city.longitude = stod(input);
// }

// void get_input_for_population(City& city) {
//     string input;
//     getline(cin, input);
//     while (!util::parse::is_valid_num<int>(input) || stoi(input) < 0) {
//         cout << "You entered an invalid population.\n"
//                 "It should be a non-negative integer. Please try again: ";
//         getline(cin, input);
//     }
//     city.population = stoi(input);
// }

// void get_input_for_population_density(City& city) {
//     string input;
//     getline(cin, input);
//     while (!util::parse::is_valid_num<double>(input) || stod(input) > city.population
//         || stod(input) < 0.0) {
//         cout << "You entered an invalid population density.\n"
//                 "It should be non-negative and less than the population. Please try again: ";
//         getline(cin, input);
//     }
//     city.population_density = stod(input);
// }

// // Only to provide consistent naming.
// void get_input_and_add_to(City& city, const Field& field) {
//     switch (field) {
//     case Field::city_name:
//         getline_no_semicolon_and_trim(cin, city.name);
//         break;
//     case Field::province:
//         getline_no_semicolon_and_trim(cin, city.province);
//         break;
//     case Field::province_id:
//         get_input_for_province_id(city);
//         break;
//     case Field::latitude:
//         get_input_for_latitude(city);
//         break;
//     case Field::longitude:
//         get_input_for_longitude(city);
//         break;
//     case Field::population:
//         get_input_for_population(city);
//         break;
//     case Field::population_density:
//         get_input_for_population_density(city);
//         break;
//     default:
//         cmpt::error("Unknown Field in: " + string(__func__) + "(). File: " + string(__FILE__));
//     }
// }

// City Menu::Add_records::get_input() const {
//     City city;
//     cout << "Enter the characteristics of your new city to be added:\n";
//     cout << "- City name: ";
//     get_input_and_add_to(city, Field::city_name);
//     cout << "- Its province: ";
//     get_input_and_add_to(city, Field::province);
//     cout << "- That province's shorter name: ";
//     get_input_and_add_to(city, Field::province_id);
//     cout << "- City's latitude: ";
//     get_input_and_add_to(city, Field::latitude);
//     cout << "- Its longitude: ";
//     get_input_and_add_to(city, Field::longitude);
//     cout << "- City's population: ";
//     get_input_and_add_to(city, Field::population);
//     cout << "- Its population density: ";
//     get_input_and_add_to(city, Field::population_density);
//     return city;
// }

// YesNo_Option get_yesno_option() {
//     cout << "Enter 'y' for Yes, 'n' for No: ";
//     string input;
//     getline(cin, input);
//     YesNo_Option option = util::parse::convert_to_yesno_option(input);
//     while (option == YesNo_Option::invalid_option) {
//         cout << "Interesting choice.. Please try again: ";
//         getline(cin, input);
//         option = util::parse::convert_to_yesno_option(input);
//     }
//     return option;
// }

// bool Menu::ask_if_user_wants_to_try_again() const {
//     cout << "Would you like to try again?\n";
//     return (get_yesno_option() == YesNo_Option::yes);
// }

// void print_single_record(const City& city) {
//     // Put commas in numbers.
//     const util::format::Commas_thousands_sep_RAII formatter(cout);
//     cout << "City:\n"
//          << "+ Name: " << city.name << "\n"
//          << "+ Province: " << city.province << "\n"
//          << "+ Province Code: " << city.province_id << "\n"
//          << "+ Latitude: " << city.latitude << " degrees North\n"
//          << "+ Longitude: " << city.longitude << " degrees West\n"
//          << "+ Population: " << city.population << " people\n"
//          << "+ Population Density: " << city.population_density << " people per km^2\n"
//          << endl;
// }

// void Menu::Add_records::say_record_exists(const City& city) const {
//     cout << "\n"
//          << "This record already exists in the database!\n\a";
//     print_single_record(city);
// }

// void Menu::Add_records::say_record_added(const City& city) const {
//     cout << "\n"
//          << "This record has been successfully added to the database.\n";
//     print_single_record(city);
// }

// void show_menu_options_for_possible_fields() {
//     cout << "\n"
//             "(1) City name\n"
//             "(2) Province it's in\n"
//             "(3) Province code\n"
//             "(4) Latitude\n"
//             "(5) Longitude\n"
//             "(6) Population size\n"
//             "(7) Population density\n"
//             "\n"
//             "(8) Return to main menu\n"
//             "\n";
// }

// void Menu::Find_records::show_guides() const {
//     cout << "\n"
//             "Find a City\n";
//     show_loading_bar(11);
//     cout << "\n"
//             "You can find cities by:\n";
//     show_menu_options_for_possible_fields();
// }

// void Menu::By_string::show_guides() const {
//     cout << "\n"
//             "Searching by strings\n";
//     show_loading_bar(20);
//     cout << "\n"
//             "You can search for exact or partial matches to your input.\n"
//             "Note: queries are case-sensitive, i.e., Van != van\n"
//             "\n"
//             "(1) Exact matches\n"
//             "(2) Partial/substring matches\n"
//             "\n"
//             "(3) Return to previous menu\n"
//             "\n";
// }

// string get_input_string_trimmed() {
//     string input_str;
//     getline(cin, input_str);
//     return util::parse::trim(input_str);
// }

// string Menu::By_string::get_input_string(bool substr_mode) const {
//     cout << "Enter a " << (substr_mode ? "sub" : "") << "string to search for: ";
//     return get_input_string_trimmed();
// }

// void Menu::By_number::show_guides() const {
//     cout << "\n"
//             "Searching by numbers\n";
//     show_loading_bar(20);
//     cout << "\n"
//             "You can search for exact matches or matches in a range of numbers.\n"
//             "\n"
//             "(1) Exact number matches\n"
//             "(2) Matches in a range of numbers\n"
//             "\n"
//             "(3) Return to previous menu\n"
//             "\n";
// }

// Range_t Menu::By_number::get_input_numbers(bool range_mode) const {
//     cout << "Enter a " << (!range_mode ? "number" : "range of numbers, one by one,")
//          << " to search for: ";
//     string input_str;
//     // Get first number.
//     getline(cin, input_str);
//     while (!util::parse::is_valid_num(input_str)) {
//         cout << "Not a single number. Please try again: ";
//         getline(cin, input_str);
//     }
//     const double range_low = stod(input_str);
//     // If only one number is desired.
//     if (!range_mode) {
//         return make_pair(range_low, range_low);
//     }
//     // Else get range.
//     cout << "End range: ";
//     getline(cin, input_str);
//     while (!util::parse::is_valid_num(input_str)) {
//         cout << "Not a single number. Please try again: ";
//         getline(cin, input_str);
//     }
//     const double range_high = stod(input_str);
//     if (range_low > range_high) {
//         return make_pair(range_high, range_low);
//     }
//     return make_pair(range_low, range_high);
// }

// void Menu::Delete_records::show_guides() const {
//     cout << "\n"
//             "Delete a City\n";
//     show_loading_bar(13);
//     cout << "\n"
//             "You can search and delete cities by:\n";
//     show_menu_options_for_possible_fields();
// }

// bool Menu::Delete_records::confirm_user_wants_to_delete() const {
//     cout << "Are you sure you want to delete the record(s) above?\n";
//     return (get_yesno_option() == YesNo_Option::yes);
// }

// void Menu::Delete_records::say_records_deleted(int how_many) const {
//     cout << "\n";
//     if (how_many >= 0) {
//         cout << how_many << " ";
//     }
//     cout << "Matching records deleted successfully.\n"
//             "\n";
// }

// void Menu::List_records::show_guides() const {
//     cout << "\n"
//             "List Cities\n";
//     show_loading_bar(11);
//     cout << "\n"
//             "Cities can be listed in sorted order by:\n";
//     show_menu_options_for_possible_fields();
// }

// void Menu::List_records::show_options_for_strings() const {
//     cout << "\n"
//             "Listing by strings\n";
//     show_loading_bar(18);
//     cout << "\n"
//             "Categorical fields in records can be listed in:\n"
//             "\n"
//             "(1) Alphabetical order\n"
//             "(2) Reverse alphabetical order\n"
//             "\n"
//             "(3) Return to previous menu\n"
//             "\n";
// }

// void Menu::List_records::show_options_for_numbers() const {
//     cout << "\n"
//             "Listing by numbers\n";
//     show_loading_bar(18);
//     cout << "\n"
//             "Numerical fields in records can be listed in:\n"
//             "\n"
//             "(1) Ascending order\n"
//             "(2) Descending order\n"
//             "\n"
//             "(3) Return to previous menu\n"
//             "\n";
// }

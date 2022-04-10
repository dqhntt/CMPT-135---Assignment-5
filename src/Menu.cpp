#include "Menu.h"
#include "cmpt_error.h"
#include "util.format.h"
#include "util.parse.h"
#include "util.time.h"
#include <iostream>
using namespace std;

Menu::Menu()
    : _start_time(time(0))
{ }

void show_loading_bar(int how_many_bars, char bar = '-', int total_milliseconds = 100) {
    for (int i = 0; i < how_many_bars; i++) {
        cout << bar << flush;
        util::time::pause(total_milliseconds / how_many_bars);
    }
    cout << "\n";
}

Menu::~Menu() {
    cout << "Saving data to file before exiting";
    show_loading_bar(5, '.', 1000);
    cout << "Thanks for spending " << (time(0) - _start_time) / 60.0 << " minutes with us!\n";
}

void Menu::print_matching_records(const vector<City>& records) const {
    // Put commas in numbers, e.g., 10,000,000
    const util::format::Commas_thousands_separator formatter(cout);
    cout << "\n"
            "Here is a list of matching cities:\n"
            "[Name ; Province ; Province-ID ; Latitude ; Longitude ; Population ; "
            "Population-Density]"
            "\n";
    int count = 1;
    for (const City& city : records) {
        cout << count++ << ") [" << city.name << "];\n"
             << "[" << city.province << "];[" << city.province_id << "];[" << city.latitude
             << "];[" << city.longitude << "];[" << city.population << "];["
             << city.population_density << "]\n";
    }
    cout << "\n"
         << "Total = " << records.size() << " records found.\n"
         << "\n";
}

void Menu::show_main_menu() const {
    cout << "\n";
    show_loading_bar(33);
    cout << "| Welcome to the City Database! |\n";
    show_loading_bar(33);
    cout << "\n"
            "(1) Add a city.\n"
            "(2) Find a city.\n"
            "(3) Delete a city.\n"
            "(4) List cities.\n"
            "(5) Quit\n"
            "\n";
}

Menu_Option Menu::get_input_option(int max_options) const {
    cout << "Enter the option number of your choice: ";
    string input;
    getline(cin, input);
    Menu_Option option = util::parse::convert_to_menu_option(input, max_options);
    while (option == Menu_Option::invalid_option) {
        cout << "You entered an invalid menu option. Please try again: ";
        getline(cin, input);
        option = util::parse::convert_to_menu_option(input, max_options);
    }
    return option;
}

void Menu::Add_records::show_guides() const {
    cout << "\n";
    show_loading_bar(14);
    cout << "| Add a City |\n";
    show_loading_bar(14);
    cout << "\n"
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
            "     a population density of 5,492.6 people per km^2\n";
}

// Request new string as needed until it doesn't contain ";".
// Works just like std::getline with added feature to request correct input.
istream& getline_no_semicolon_and_trim(istream& is, string& str) {
    std::getline(is, str);
    while (str.find(';') != string::npos) {
        cout << "Semicolons are reserved for file formatting.\n"
             << "Please try again with no \";\" added: ";
        std::getline(is, str);
    }
    util::parse::trim(str);
    return is;
}

void get_input_for_province_id(City& city) {
    getline_no_semicolon_and_trim(cin, city.province_id);
    while (city.province_id.size() > city.province.size()) {
        cout << "Hmm... That's actually longer than: " << city.province << "\n"
             << "Try entering a shorter one: ";
        getline_no_semicolon_and_trim(cin, city.province_id);
    }
}

void get_input_for_latitude(City& city) {
    string input;
    getline(cin, input);
    while (!util::parse::is_valid_DD_latitude(input)) {
        cout << "You entered an invalid latitude.\n"
                "Please use only decimal degrees from -90.0 to 90.0.\n"
                "Please try again: ";
        getline(cin, input);
    }
    city.latitude = stod(input);
}

void get_input_for_longitude(City& city) {
    string input;
    getline(cin, input);
    while (!util::parse::is_valid_DD_longitude(input)) {
        cout << "You entered an invalid longitude.\n"
                "Please use only decimal degrees from -180.0 to 180.0.\n"
                "Please try again: ";
        getline(cin, input);
    }
    city.longitude = stod(input);
}

void get_input_for_population(City& city) {
    string input;
    getline(cin, input);
    while (!util::parse::is_valid_num<int>(input) || stoi(input) < 0) {
        cout << "You entered an invalid population.\n"
                "It should be a non-negative integer. Please try again: ";
        getline(cin, input);
    }
    city.population = stoi(input);
}

void get_input_for_population_density(City& city) {
    string input;
    getline(cin, input);
    while (!util::parse::is_valid_num<double>(input) || stod(input) < 0.0) {
        cout << "You entered an invalid population density.\n"
                "It should be a non-negative number. Please try again: ";
        getline(cin, input);
    }
    city.population_density = stod(input);
}

// Only to provide consistent naming.
void get_input_and_add_to(City& city, const Field& field) {
    switch (field) {
    case Field::city_name:
        getline_no_semicolon_and_trim(cin, city.name);
        break;
    case Field::province:
        getline_no_semicolon_and_trim(cin, city.province);
        break;
    case Field::province_id:
        get_input_for_province_id(city);
        break;
    case Field::latitude:
        get_input_for_latitude(city);
        break;
    case Field::longitude:
        get_input_for_longitude(city);
        break;
    case Field::population:
        get_input_for_population(city);
        break;
    case Field::population_density:
        get_input_for_population_density(city);
        break;
    default:
        cmpt::error("Unknown Field in: " + string(__func__) + "(). File: " + string(__FILE__));
    }
}

City Menu::Add_records::get_input() const {
    City city;
    cout << "\n"
            "Enter the characteristics of your new city to be added:\n";
    cout << "- City name: ";
    get_input_and_add_to(city, Field::city_name);
    cout << "- Its province: ";
    get_input_and_add_to(city, Field::province);
    cout << "- That province's shorter name: ";
    get_input_and_add_to(city, Field::province_id);
    cout << "- City's latitude: ";
    get_input_and_add_to(city, Field::latitude);
    cout << "- Its longitude: ";
    get_input_and_add_to(city, Field::longitude);
    cout << "- City's population: ";
    get_input_and_add_to(city, Field::population);
    cout << "- Its population density: ";
    get_input_and_add_to(city, Field::population_density);
    return city;
}

YesNo_Option get_yesno_option() {
    cout << "Enter 'y' for Yes, 'n' for No: ";
    string input;
    getline(cin, input);
    YesNo_Option option = util::parse::convert_to_yesno_option(input);
    while (option == YesNo_Option::invalid_option) {
        cout << "Interesting choice.. Please try again: ";
        getline(cin, input);
        option = util::parse::convert_to_yesno_option(input);
    }
    return option;
}

bool Menu::ask_if_user_wants_to_try_again() const {
    cout << "Would you like to try again?\n";
    return (get_yesno_option() == YesNo_Option::yes);
}

void print_single_record(const City& city) {
    // Put commas in numbers.
    const util::format::Commas_thousands_separator formatter(cout);
    cout << "City:\n"
         << "+ Name: " << city.name << "\n"
         << "+ Province: " << city.province << "\n"
         << "+ Province Code: " << city.province_id << "\n"
         << "+ Latitude: " << city.latitude << " North\n"
         << "+ Longitude: " << city.longitude << " West\n"
         << "+ Population: " << city.population << " people\n"
         << "+ Population Density: " << city.population_density << " people per km^2\n"
         << "\n";
}

void Menu::Add_records::say_record_exists(const City& city) const {
    cout << "\n"
         << "This record already exists in the database!\n\a";
    print_single_record(city);
}

void Menu::Add_records::say_record_added(const City& city) const {
    cout << "\n"
         << "This record has been successfully added to the database.\n";
    print_single_record(city);
}

void show_menu_options_for_possible_fields() {
    cout << "\n"
            "(1) City name\n"
            "(2) Province it's in\n"
            "(3) Province code\n"
            "(4) Latitude\n"
            "(5) Longitude\n"
            "(6) Population size\n"
            "(7) Population density\n"
            "\n"
            "(8) Return to main menu\n"
            "\n";
}

void Menu::Find_records::show_guides() const {
    cout << "\n";
    show_loading_bar(15);
    cout << "| Find a City |\n";
    show_loading_bar(15);
    cout << "\n"
            "You can find cities by:\n";
    show_menu_options_for_possible_fields();
}

void Menu::By_string::show_guides() const {
    cout << "\n";
    show_loading_bar(24, '~');
    cout << "| Searching by strings |\n";
    show_loading_bar(24, '~');
    cout << "\n"
            "You can search for exact or partial matches to your input.\n"
            "NOTE: queries are case-sensitive, i.e., Van != van\n"
            "\n"
            "(1) Exact matches\n"
            "(2) Partial/substring matches\n"
            "\n"
            "(3) Return to previous menu\n"
            "\n";
}

string Menu::By_string::get_input_string(bool substr_mode) const {
    cout << "Enter a " << (substr_mode ? "sub" : "") << "string to search for: ";
    string input_str;
    getline(cin, input_str);
    return util::parse::trim(input_str);
}

void Menu::By_number::show_guides() const {
    cout << "\n";
    show_loading_bar(24, '~');
    cout << "| Searching by numbers |\n";
    show_loading_bar(24, '~');
    cout << "\n"
            "You can search for exact matches or matches in a range of numbers.\n"
            "\n"
            "(1) Exact number matches\n"
            "(2) Matches in a range of numbers\n"
            "\n"
            "(3) Return to previous menu\n"
            "\n";
}

Range_t Menu::By_number::get_input_numbers(bool range_mode) const {
    cout << "Enter a " << (!range_mode ? "number" : "range of numbers, one by one,")
         << " to search for: ";
    string input_str;
    // Get first number.
    getline(cin, input_str);
    while (!util::parse::is_valid_num(input_str)) {
        cout << "Not a single number. Please try again: ";
        getline(cin, input_str);
    }
    const double range_low = stod(input_str);
    // If only one number is desired.
    if (!range_mode) {
        return make_pair(range_low, range_low);
    }
    // Else get range.
    cout << "End range: ";
    getline(cin, input_str);
    while (!util::parse::is_valid_num(input_str)) {
        cout << "Not a single number. Please try again: ";
        getline(cin, input_str);
    }
    const double range_high = stod(input_str);
    if (range_low > range_high) {
        return make_pair(range_high, range_low);
    }
    return make_pair(range_low, range_high);
}

void Menu::Delete_records::show_guides() const {
    cout << "\n";
    show_loading_bar(17);
    cout << "| Delete a City |\n";
    show_loading_bar(17);
    cout << "\n"
            "You can search and delete cities by:\n";
    show_menu_options_for_possible_fields();
}

bool Menu::Delete_records::confirm_user_wants_to_delete() const {
    cout << "Are you sure you want to delete the record(s) above?\n";
    return (get_yesno_option() == YesNo_Option::yes);
}

void Menu::Delete_records::say_records_deleted(int how_many) const {
    cout << "\n"
         << how_many << " matching records deleted successfully.\n"
         << "\n";
}

void Menu::List_records::show_guides() const {
    cout << "\n";
    show_loading_bar(15);
    cout << "| List Cities |\n";
    show_loading_bar(15);
    cout << "\n"
            "Cities can be listed in sorted order by:\n";
    show_menu_options_for_possible_fields();
}

void Menu::List_records::show_options_for_strings() const {
    cout << "\n";
    show_loading_bar(22, '~');
    cout << "| Listing by strings |\n";
    show_loading_bar(22, '~');
    cout << "\n"
            "Categorical fields in records can be listed in:\n"
            "\n"
            "(1) Alphabetical order\n"
            "(2) Reverse alphabetical order\n"
            "\n"
            "(3) Return to previous menu\n"
            "\n";
}

void Menu::List_records::show_options_for_numbers() const {
    cout << "\n";
    show_loading_bar(22, '~');
    cout << "| Listing by numbers |\n";
    show_loading_bar(22, '~');
    cout << "\n"
            "Numerical fields in records can be listed in:\n"
            "\n"
            "(1) Ascending order\n"
            "(2) Descending order\n"
            "\n"
            "(3) Return to previous menu\n"
            "\n";
}

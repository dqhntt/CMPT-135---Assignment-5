#include "Menu.h"
#include "cmpt_error.h"
#include "util.parse.h"

#include <ctime>
#include <iostream>
using namespace std;

Menu::Menu()
    : _start_time(time(nullptr))
{ }

Menu::~Menu() {
    cout << "Saving data to file before exiting...\n"
         << "Thanks for spending " << (time(nullptr) - _start_time) / 60.0 << " minutes with us!\n";
}

void Menu::show_main_menu() const {
    cout << "\n"
            "Welcome to the City Database!\n"
            "-----------------------------\n"
            "\n"
            "(1) Add a city.\n"
            "(2) Find a city.\n"
            "(3) Delete a city.\n"
            "(4) List cities.\n"
            "(5) Quit\n"
            "\n";
}

Menu_Options Menu::get_input_option() const {
    cout << "Enter the option number of your choice: ";
    string input;
    getline(cin, input);
    Menu_Options option = util::parse::convert_to_menu_option(input);
    while (option == Menu_Options::invalid_option) {
        cout << "You entered an invalid option. Please try again: ";
        getline(cin, input);
        option = util::parse::convert_to_menu_option(input);
    }
    return option;
}

void Menu::Add_records::show_guides() const {
    cout << "\n"
            "Add a city\n"
            "----------\n"
            "\n"
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
            "     located at coordinate (N, W): 49.25, -123.1 (DD)\n"
            "     once with a population of 2,264,823 people and\n"
            "     a population density of 5,492.6 people per km^2\n"
            "\n";
}

// Request new string as needed until it doesn't contain ";".
// Works just like std::getline with added abibility to request correct input.
istream& getline_no_semicolon(istream& is, string& str) {
    std::getline(is, str);
    while (str.find(';') != string::npos) {
        cout << "Semicolons are reserved for file formatting.\n"
             << "Please try again with no \";\" added: ";
        std::getline(is, str);
    }
    return is;
}

void get_input_for_province_id(City& city) {
    getline_no_semicolon(cin, city.province_id);
    while (city.province_id.size() > city.province.size()) {
        cout << "Hmm... That's actually longer than: " << city.province << ".\n"
             << "Try entering a shorter one: ";
        getline_no_semicolon(cin, city.province_id);
        city.province_id = util::parse::trimmed(city.province_id);
    }
    city.province_id = util::parse::trimmed(city.province_id);
}

void get_input_for_latitude(City& city) {
    string input;
    getline(cin, input);
    while (!util::parse::is_valid_DD_latitude(input)) {
        cout << "You entered an invalid latitude.\n"
                "Only decimal degrees, e.g. 49.25, -123.10, should be used.\n"
                "And latitude only goes from -90 to 90 degrees.\n"
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
                "Only decimal degrees, e.g. 49.25, -123.10, should be used.\n"
                "And longitude only goes from -180 to 180 degrees.\n"
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
    while (!util::parse::is_valid_num<double>(input) || stod(input) > city.population
        || stod(input) < 0.0) {
        cout << "You entered an invalid population density.\n"
                "It should be non-negative and less than the population. Please try again: ";
        getline(cin, input);
    }
    city.population_density = stod(input);
}

// Only to provide consistent naming.
void get_input_and_add_to(City& city, const Field& field) {
    switch (field) {
    case Field::city_name:
        getline_no_semicolon(cin, city.name);
        city.name = util::parse::trimmed(city.name);
        break;
    case Field::province:
        getline_no_semicolon(cin, city.province);
        city.province = util::parse::trimmed(city.province);
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
    cout << "Enter the characteristics of your new city to be added:\n";
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

YesNo_Options get_yesno_option() {
    cout << "Enter 'y' for Yes, 'n' for No: ";
    string input;
    getline(cin, input);
    YesNo_Options option = util::parse::convert_to_yesno_option(input);
    while (option == YesNo_Options::invalid_option) {
        cout << "Interesting choice.. Please try again: ";
        getline(cin, input);
        option = util::parse::convert_to_yesno_option(input);
    }
    return option;
}

bool Menu::Add_records::ask_if_user_wants_to_try_again() const {
    cout << "Would you like to try again?\n";
    return (get_yesno_option() == YesNo_Options::yes);
}

void print_record(const City& city) {
    cout << "City:\n"
         << "+ Name: " << city.name << "\n"
         << "+ Province: " << city.province << "\n"
         << "+ Province Code: " << city.province_id << "\n"
         << "+ Latitude: " << city.latitude << " degrees North\n"
         << "+ Longitude: " << city.longitude << " degrees West\n"
         << "+ Population: " << city.population << " people\n"
         << "+ Population Density: " << city.population_density << " people per km^2\n";
}

void Menu::Add_records::say_record_exists(const City& city) const {
    cout << "This record already exists in the database.\n";
    print_record(city);
}

void Menu::Add_records::say_record_added(const City& city) const {
    cout << "This record has been successfully added to the database.\n";
    print_record(city);
}

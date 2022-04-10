#ifndef MENU_H
#define MENU_H

#include "City.h"
#include <utility>
#include <vector>

enum class Menu_Option { one, two, three, four, five, six, seven, eight, invalid_option };
enum class YesNo_Option { yes, no, invalid_option };
using Range_t = std::pair<double, double>;

// All methods deal with std::cout.
// Methods returning non-void also deal with std::cin.
class Menu {
private:
    const time_t _start_time;
    // Common sub-sub-menus.
    class By_string {
    public:
        void show_guides() const;
        std::string get_input_string(bool substr_mode) const;
    };
    class By_number {
    public:
        void show_guides() const;
        Range_t get_input_numbers(bool range_mode) const;
    };

public:
    Menu();
    ~Menu();
    // Returns any possible Menu_Options up to max_options, except for invalid_option.
    // Currently support only up to 8 options.
    Menu_Option get_input_option(int max_options) const;
    bool ask_if_user_wants_to_try_again() const;
    void show_main_menu() const;
    void print_matching_records(const std::vector<City>& records) const;

    // Sub-menus:
    class Add_records {
    public:
        void show_guides() const;
        City get_input() const;
        void say_record_exists(const City& city) const;
        void say_record_added(const City& city) const;
    } add_records;
    class Find_records {
    public:
        void show_guides() const;
        By_string by_string;
        By_number by_number;
    } find_records;
    class Delete_records {
    public:
        void show_guides() const;
        void say_records_deleted(int how_many) const;
        bool confirm_user_wants_to_delete() const;
        By_string by_string;
        By_number by_number;
    } delete_records;
    class List_records {
    public:
        void show_guides() const;
        void show_options_for_strings() const;
        void show_options_for_numbers() const;
    } list_records;
}; // class Menu

#endif // MENU_H
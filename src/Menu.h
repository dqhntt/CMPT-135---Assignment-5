#ifndef MENU_H
#define MENU_H

#include "City.h"
#include <vector>

enum class Menu_Option { one, two, three, four, five, six, seven, eight, invalid_option };
enum class YesNo_Option { yes, no, invalid_option };

struct Num_range_t {
    double low {}, high {};
};

class Menu {
public:
    Menu();
    ~Menu();

    // Returns any possible Menu_Options up to max_options.
    // All other menu options result in invalid_option.
    Menu_Option get_input_option(int max_options) const;

    void show_main_menu() const;
    void print_records(const std::vector<City>& records) const;
    bool ask_if_user_wants_to_try_again() const;

    // Common sub-sub-menus.
    class By_string {
    public:
        void        show_guides() const;
        std::string get_input_string(const Menu_Option& option) const;
    };
    class By_number {
    public:
        void        show_guides() const;
        Num_range_t get_input_numbers(const Menu_Option& option) const;
    };

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
        void      show_guides() const;
        By_string by_string;
        By_number by_number;
    } find_records;
    class Delete_records {
    public:
    } delete_records;
    class List_records {
    public:
        void list() const;
    } list_records;

private:
    const time_t _start_time;
}; // class Menu

#endif // MENU_H